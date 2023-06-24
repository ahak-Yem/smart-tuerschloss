#include <Arduino.h>
#include <string>
#include <RFID.h>
#include<Lock.h>
#include<DoorState.h>

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
