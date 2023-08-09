#include <Arduino.h>
#include <string.h>
  #define PE_B0 8
  #define PE_B1 9
  #define PE_B2 10
  #define PE_B3 11
  #define PE_B4 12
  #define PE_B5 13
  #define PE_B6 14
  #define PE_B7 15
class DoorState
{
private:

public:
    String MapBoxSensorPin(const int pin);
};
