#include <Arduino.h>
#include <string>
#include<Lock.h>
#include<DoorState.h>
#include "PN532.h"

//Use this variables to turn the wished MCP23017 pin(s) on/off.
//  #define A0 0    
//  #define A1 1     
//  #define A2 2     
//  #define A3 3
//  #define A4 4
//  #define A5 5
//  #define A6 6
//  #define A7 7
//  #define B1 8
//  #define B2 9
//  #define B3 10
//  #define B4 11
//  #define B5 12
//  #define B6 13
//  #define B7 14
//........................ -> // Uncomment the wished line when using the MCP23017

//I2C pins for PN532 RFID Reader
#define PN532_SDA   13   
#define PN532_SCL   14   

int lockState=-1;
PN532 pn532(PN532_SDA, PN532_SCL);
Lock lock1;
DoorState doorstate;

void setup() {
    Serial.begin(115200);

  //Setup PN532-----------------------------------------------------------------------------------
  pn532.begin();
  uint32_t versiondata = pn532.nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Didn't find PN53x board");
    while (1);
  }
  pn532.nfc.SAMConfig();
  //End PN532 setup-------------------------------------------------------------------------------
  
  lock1.setup();
  doorstate.setup();
}

void loop() {
  //Reads the RFID card here-----------------------------------
  String content="";
    if (pn532.isCardPresent()) {
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
    
    // Do something with the UID here.
    
    delay(2000);
  }
  //---------------------------------------------------------------

  doorstate.checkState();
  //String content=rfid.get_UID();
  lockState=lock1.OpenLock("content");
  if(lockState==1){
    //rfid.set_UID_NULL();
    }
}
