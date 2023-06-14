#include <Arduino.h>
#include <string.h>
class DoorState
{
private:
  String state;
  const int GreenLED =13;
  const int Sensor= 33;

public:
    void checkState();
    void setup();
};
