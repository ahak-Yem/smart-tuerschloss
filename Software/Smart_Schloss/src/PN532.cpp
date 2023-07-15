#include "PN532.h"

PN532::PN532(uint8_t sdaPin, uint8_t sclPin) : sdaPin(sdaPin), sclPin(sclPin), i2c(1), nfc(sdaPin, sclPin, &i2c) {}

void PN532::begin() {
  i2c.begin(sdaPin, sclPin);
  nfc.begin();
}

bool PN532::isCardPresent() {
  uint8_t success;
  uint8_t uid[7];
  uint8_t uidLength;
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  return success;
}

void PN532::readCard(uint8_t* uid, uint8_t* uidLength) {
  nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, uidLength);
}