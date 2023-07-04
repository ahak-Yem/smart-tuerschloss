#include <Arduino.h>
#include <RFID.h>
#include<Lock.h>
#include<DoorState.h>
#include<PinsExpander.h>
#include<ManagingWifi.h>

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

const char* ssid_Router = "Yemen";
const char* password_Router = "123456789"; // TODO: Make it suitable to the wifi network used at the end

int doorSensorsPins[] = {13}; //Write the pin(s) where the sensor(s) is connected to.

int lockState=-1;

//Objects of our hard coded classes.
RFID rfid(13,14);
Lock lock1;
DoorState doorSensor(doorSensorsPins, sizeof(doorSensorsPins) / sizeof(doorSensorsPins[0]));
PinsExpander pinsExpander(0x20,15,0);
ManagingWifi wifiManager(ssid_Router,password_Router);

//For DoorState & Wifi there are no setup methods, because they are built with constructor.
void setup() {
  lock1.setup();
  pinsExpander.setup();
  //Wire.begin(SDA,SCL);  // Initialize the custom I2C interface

}

void loop() {
  std::vector<uint8_t> readDoorState = doorSensor.ReadAllPins(doorSensorsPins);

  for (size_t i = 0; i < readDoorState.size(); i++) {
    if (readDoorState[i] == HIGH) {
      //do something if door is open
    } else if (readDoorState[i] == LOW) {
      //do something if door is closed
    }
  }

  rfid.set_UID();
  String content=rfid.get_UID();
  lockState=lock1.OpenLock(content);
  if(lockState==1){
    rfid.set_UID_NULL();
    }
}
