#include <Arduino.h>
#include <string>
#include <WiFi.h>

//Classes written by me
#include "Lock.h"
#include "DoorState.h"
#include "PN532.h"
#include "ManagingWifi.h"
#include "PinsExpander.h"

//Pins-Expander section 
//Use this variables to turn the wished MCP23017 pin(s) on/off.
  #define SDA_MCP 32
  #define SCL_MCP 33
  #define A0 0    
  #define A1 1     
  #define A2 2     
  #define A3 3
  #define A4 4
  #define A5 5
  #define A6 6
  #define A7 7
  #define B0 8
  #define B1 9
  #define B2 10
  #define B3 11
  #define B4 12
  #define B5 13
  #define B6 14
  #define B7 15
  PinsExpander pinsExpander(0x20,SDA_MCP,SCL_MCP);
  const int outputPins[] = {B1,B3,A5};
  int numberOfOutputPins = sizeof(outputPins) / sizeof(outputPins[0]);
//........................ -> // Uncomment the wished line when using the MCP23017

//RFID section
//I2C pins for PN532 RFID Reader
#define PN532_SDA   13   
#define PN532_SCL   14   
String content="";

//Wifi section
const char* ssid = "Yemen";
const char* password = "123456789"; //TODO: Change wifi data to the wished one
//Use after bug is repaired
//ManagingWifi wifiManager(ssid, password); //Creating an object of this class does all the configuration needed


int lockState=-1;
//PN532 pn532(PN532_SDA, PN532_SCL);
//Lock lock1;
//DoorState doorstate;

void setup() {
  Serial.begin(115200);
  //Setup PN532-----------------------------------------------------------------------------------
  /*pn532.begin();
  uint32_t versiondata = pn532.nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Didn't find PN53x board");
    while (1);
  }
  pn532.nfc.SAMConfig();*/
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

  //Pins Expander---------------------------------------------------------------------------------
  pinsExpander.setup();
  Wire.begin(SDA_MCP,SCL_MCP);
  pinsExpander.setPinModeOutput(outputPins,numberOfOutputPins);
  //End Pins Expander-----------------------------------------------------------------------------//
  
  //lock1.setup();
  //doorstate.setup();
}

void loop() {
  //Reads the RFID card here-----------------------------------
    /*if (pn532.isCardPresent()) {
    Serial.println("Found an RFID card or tag!");
    uint8_t uid[7];
    uint8_t uidLength;
    pn532.readCard(uid, &uidLength);
    Serial.print("UID Value: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(uid[i], HEX);
      if (uid[i] < 0x10) {
        content += "0"; // Add leading zero for single-digit hex values
      }
      content += String(uid[i], HEX); // Convert byte to hexadecimal and concatenate
    }
    Serial.println();
    delay(2000);
  }*/
  //---------------------------------------------------------------//

  //Open lock or turn LED on using PE----------------------------------------
  pinsExpander.TurnHigh(outputPins,numberOfOutputPins);
  delay(1000);
  pinsExpander.TurnLow(outputPins,numberOfOutputPins);
  delay(1000);
  //--------------------------------------------------------------//
  
  /*doorstate.checkState();
  lockState=lock1.OpenLock("content");
  if(lockState==1){
    content="";
    }*/
}
