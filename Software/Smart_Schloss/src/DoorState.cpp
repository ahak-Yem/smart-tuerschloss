#include <Arduino.h>
#include "DoorState.h"


DoorState::DoorState(int* doorSensorsPins, int numberOfPins) {
  DoorSensorsPin.reserve(numberOfPins);

  for (int i = 0; i < numberOfPins; i++) {
    DoorSensorsPin.push_back(doorSensorsPins[i]);
    pinMode(doorSensorsPins[i], INPUT);
  }
}

uint8_t DoorState::ReadPin(uint8_t pin) {
  return digitalRead(pin);
}

std::vector<uint8_t> DoorState::ReadAllPins(int* allPins) {
  std::vector<uint8_t> readings;

  for (int i = 0; i < DoorSensorsPin.size(); i++) {
    readings.push_back(digitalRead(DoorSensorsPin[i]));
  }

  return readings;
}
