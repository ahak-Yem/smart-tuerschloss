#include <Arduino.h>
#include <vector>
#ifndef DOORSTATE_H
#define DOORSTATE_H

class DoorState {
private:
  std::vector<int> DoorSensorsPin;

public:
  DoorState(int* doorSensorsPins, int numberOfPins);

  uint8_t ReadPin(uint8_t pin);
  std::vector<uint8_t> ReadAllPins(int* allPins);
  std::vector<uint8_t> getSensorPins();
};
#endif 