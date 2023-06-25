#include <Arduino.h>
#include <string>
#include <RFID.h>
#include<Lock.h>
#include<DoorState.h>

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

int lockState=-1;
RFID rfid;
Lock lock1;
DoorState doorstate;

void setup() {
  rfid.setup();
  lock1.setup();
  doorstate.setup();
}

void loop() {
  doorstate.checkState();
  rfid.set_UID();
  String content=rfid.get_UID();
  lockState=lock1.OpenLock(content);
  if(lockState==1){
    rfid.set_UID_NULL();
    }
}
