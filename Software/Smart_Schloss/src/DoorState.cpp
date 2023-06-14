#include <Arduino.h>
#include <DoorState.h>

void DoorState::setup(){
    pinMode(Sensor,INPUT);
    pinMode(GreenLED,OUTPUT);
}

void DoorState::checkState(){
    if(Sensor == LOW){
        digitalWrite(GreenLED,HIGH);
        delay(1000);
        state = "auf";
    }
}