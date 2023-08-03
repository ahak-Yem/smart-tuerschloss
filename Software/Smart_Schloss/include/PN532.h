#ifndef PN532_H
#define PN532_H

#include <Adafruit_PN532.h>

class PN532 {
public:
  PN532(uint8_t sdaPin, uint8_t sclPin);
  void begin();
  bool isCardPresent();
  String readCard();
  String getCurrentUID();
  Adafruit_PN532 nfc; // Move nfc here to be accessible outside the class

private:
  uint8_t sdaPin;
  uint8_t sclPin;
  TwoWire i2c;
  String currentUID;
};

#endif
