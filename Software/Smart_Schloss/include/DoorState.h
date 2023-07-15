#include <Arduino.h>
#include <string.h>
class DoorState
{
private:
  int state;
  const int GreenLED =13;
  const int Sensor= 15;

public:
    void checkState();
    void setup();
};
