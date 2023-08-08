#include <Arduino.h>
#include <string>
#include <WiFi.h>

//Classes written by me
#include "Lock.h"
#include "DoorState.h"
#include "PN532.h"
#include "ManagingWifi.h"
#include "PinsExpander.h"
#include "DB.h"
#include "RealTimeManager.h"

//Declare functions
void rfidReaderTrigger(String content);

//Pins-Expander section 
//I2C pins for pins expander
  #define SDA_MCP 32
  #define SCL_MCP 33

  //Use this variables to turn the wished MCP23017 pin(s) on/off.
  #define PE_A0 0    
  #define PE_A1 1     
  #define PE_A2 2     
  #define PE_A3 3
  #define PE_A4 4
  #define PE_A5 5
  #define PE_A6 6
  #define PE_A7 7
  #define PE_B0 8
  #define PE_B1 9
  #define PE_B2 10
  #define PE_B3 11
  #define PE_B4 12
  #define PE_B5 13
  #define PE_B6 14
  #define PE_B7 15

  PinsExpander pinsExpander(0x20,SDA_MCP,SCL_MCP);

  //A0 - A7 als output pins - Hinweis: Nutze am Anfang A0 und dann nach und nach bis A7
  const int outputPins[] = {PE_A0,PE_A1,PE_A2,PE_A3,PE_A4,PE_A5,PE_A6,PE_A7};//Wenn nicht alle belegt sind=löschen
  int numberOfOutputPins = sizeof(outputPins) / sizeof(outputPins[0]); 

  //B0 - B7 als input pins - Hinweis: Nutze am Anfang B0 und dann nach und nach bis B7
  const int inputPins[] = {PE_B0,PE_B1,PE_B2,PE_B3,PE_B4,PE_B5,PE_B6,PE_B7};
  int numberOfInputPins = sizeof(inputPins) / sizeof(inputPins[0]);


//RFID section
//I2C pins for PN532 RFID Reader
#define PN532_SDA   13   
#define PN532_SCL   14

String content=""; // Variable for UID von Benutzer
PN532 pn532(PN532_SDA, PN532_SCL);

//Wifi section
const char* ssid = "Yemen";
const char* password = "123456789"; //TODO: Change wifi data as wished.

//Use after bug is repaired
//ManagingWifi wifiManager(ssid, password); //Creating an object of this class does all the configuration needed


//DoorState doorstate;

//DB section
const char* serverURL = "http://64.226.76.247:8080/key-management/";

//Init DB instance with target server. 
std::vector<BookingData> currentUserBookings;

//All possible queries
FetchBookingDataQuery fetchQuery; //Fetch booking data using RFID.
InsertBoxAccessQuery insertQuery; //Insert log for box access
UpdateKeyStateQuery updateKeyQuery; //Update key state when it changes.
UpdateBookingStateQuery updateBookingQuery; //Update booking data.
UpdateBoxDoorState updateBoxDoorQuery; //Update door state of box door
UpdateKastenZugangState updateKastenzugangQuery; //Update the door state of a specific box access.

//Realtime section
const char* ntpServer = "pool.ntp.org";
const int timeZoneOffset = 2; // Germany is UTC+2
RealTimeManager timeManager(ntpServer, timeZoneOffset);

//Lock section
Lock lock;

void setup() {
  Serial.begin(115200);

  //Pins Expander---------------------------------------------------------------------------------
  pinsExpander.setup();
  pinsExpander.setPinModeOutput(outputPins,numberOfOutputPins);
  pinsExpander.setPinModeInput(inputPins,numberOfInputPins);
  //End Pins Expander-----------------------------------------------------------------------------//
  
  //Setup PN532-----------------------------------------------------------------------------------
  pn532.begin();
  uint32_t versiondata = pn532.nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Didn't find PN53x board");
    while (1);
  }
  pn532.nfc.SAMConfig();
  //End PN532 setup-------------------------------------------------------------------------------//

  //WiFi------------------------------------------------------------------------------------------
  WiFi.begin(ssid,password);
  Serial.println(String("Connecting to ")+ssid);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  //End WiFi--------------------------------------------------------------------------------------//
  
  //TimeManager-----------------------------------------------------------------------------------
  timeManager.begin();
  
  //doorstate.setup();
}

void loop() {
  //Trigger 1: RFID is scanned
  //Step1: Reads the RFID card here-----------------------------------
  content = pn532.readCard();
  if(content!=""){
    rfidReaderTrigger(content);
    //Clean this to be reused for another scan.
    fetchQuery=FetchBookingDataQuery(); 
    insertQuery=InsertBoxAccessQuery();
    updateKeyQuery=UpdateKeyStateQuery();
    updateBookingQuery=UpdateBookingStateQuery();
    updateBoxDoorQuery=UpdateBoxDoorState();
    updateKastenzugangQuery=UpdateKastenZugangState(); 
    content="";
    pn532.resetCurrentUID(); 
    
    currentUserBookings.empty();
  }
  else{
    Serial.println("No RFID_UID");
  }
}

void rfidReaderTrigger(String content) {
  DB db(serverURL);
  //Step2: Fetch for bookings data in DB
  Serial.print("RFID_UID: ");
  fetchQuery.uid=content.c_str();
  db.runQuery(FETCH_BOOKING_DATA,fetchQuery);
  currentUserBookings=db.getCurrentBookings();
  //Step3: Process the bookings data
  if(currentUserBookings.size() != 0){
    Serial.println("Number of bookings: " + String(currentUserBookings.size()));
    for (BookingData booking : currentUserBookings) {
      Serial.print("Current booking: ");
      Serial.println(booking.buchungID);

      //Step4: Check if the booking valid
      bool isBookingValid= lock.validateBooking(booking,timeManager);
      if(isBookingValid==true)
      {
        //Step5: Open lock
        int boxPin=lock.MapBoxLockPin(booking.kastenID);
        pinsExpander.TurnHigh(outputPins[boxPin],1);

        //Step6: Register box access in DB
        insertQuery.isClosed=true; 
        insertQuery.userId=booking.userID;
        db.runQuery(INSERT_BOX_ACCESS,insertQuery);
        delay(50);

        //Step7: Update Key state in DB
        updateKeyQuery.schluesselID=booking.schluesselID;
        if(String(booking.zustandSchluessel) == db.keyStateToString(KeyStateEnum::reserviert) or 
        String(booking.zustandSchluessel) == db.keyStateToString(KeyStateEnum::verfuegbar)){
          updateKeyQuery.schluesselZustand=KeyStateEnum::abgeholt;
          db.runQuery(UPDATE_KEY_STATE,updateKeyQuery);
        }
        else if(String(booking.zustandSchluessel) == db.keyStateToString(KeyStateEnum::abgeholt)){
          updateKeyQuery.schluesselZustand=KeyStateEnum::verfuegbar;
          db.runQuery(UPDATE_KEY_STATE,updateKeyQuery);
        }
        else{
         Serial.println("Der Schluessel is verloren");
        }
        delay(50);

        //Step8: Update booking state
        updateBookingQuery.buchungID=booking.buchungID;
        if(String(booking.zustandBuchung)==db.bookingZustandToString(BuchungZustandEnum::gebucht)){
          String currentTimestamp= timeManager.getCurrentDateTime();
          updateBookingQuery.abholungszeit=currentTimestamp.c_str();
          updateBookingQuery.zustand=BuchungZustandEnum::abgeholt;
          db.runQuery(UPDATE_BOOKING_STATE,updateBookingQuery);
        }
        else if(String(booking.zustandBuchung)==db.bookingZustandToString(BuchungZustandEnum::abgeholt) or
        String(booking.zustandBuchung)==db.bookingZustandToString(BuchungZustandEnum::spaet)){
          Serial.println("The booking was abgeholt or spaet");
          String currentTimestamp= timeManager.getCurrentDateTime();
          updateBookingQuery.abgabezeit=currentTimestamp.c_str();
          updateBookingQuery.zustand=BuchungZustandEnum::zurueckgegeben;
          db.runQuery(UPDATE_BOOKING_STATE,updateBookingQuery);
        }

        // Step9: Close lock
        // TODO:Uncomment this after debug
        //delay(10000);
        pinsExpander.TurnLow(outputPins[boxPin],1);
      }
      else
      {
        Serial.println("Booking is  not valid");
      }
    }       
  }
  else{
    Serial.println("The user with the rfid_uid: "+ content +" has no bookings");      
  } 
}