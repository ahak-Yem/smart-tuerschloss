#include "PN532.h"

PN532::PN532(uint8_t sdaPin, uint8_t sclPin) : sdaPin(sdaPin), sclPin(sclPin), i2c(1), nfc(sdaPin, sclPin, &i2c) {}

void PN532::begin() {
  i2c.begin(sdaPin, sclPin);
  nfc.begin();
  Serial.println("RFID reader is initialized!");
}

// bool PN532::isCardPresent() {
//   uint8_t success;
//   uint8_t uid[7];
//   uint8_t uidLength;
  
//   success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
//   if(success){
    
//   }
//   return success;
// }

String PN532::readCard() {
    uint8_t success;
    String content;
    uint8_t uid[7];
    uint8_t uidLength;
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    if(success){
      Serial.println("Found an RFID card or tag!");
      for (uint8_t i = 0; i < uidLength; i++) {
        // Convert byte to hexadecimal and concatenate
        char hexString[3];
        sprintf(hexString, "%02X", uid[i]);
        content += hexString;
      }
      Serial.print("UID Value: ");
      Serial.println(content);
      currentUID=content;
      return content; 
    }
    else{
      return "";
    }
}

String PN532::getCurrentUID()
{
    return this->currentUID;
}

void PN532::resetCurrentUID()
{
  this->currentUID="";
}