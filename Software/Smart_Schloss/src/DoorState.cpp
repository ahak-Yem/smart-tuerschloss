#include <Arduino.h>
#include <DoorState.h>

void DoorState::setup(){
    pinMode(Sensor,INPUT);
    pinMode(GreenLED,OUTPUT);
}

void DoorState::checkState(){
    state = digitalRead(Sensor);
    if(state == LOW){
        digitalWrite(GreenLED,HIGH);
        delay(10);
    }
    else{
        digitalWrite(GreenLED,LOW);
        delay(10);
    }
}