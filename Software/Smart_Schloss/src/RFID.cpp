#include "RFID.h"

String RFID::get_UID()
{
  return this->UID;
}

RFID::RFID(int sda_pin, int scl_pin) : SDA_PIN(sda_pin), SCL_PIN(scl_pin), nfc(sda_pin, scl_pin)
{
  //setup for RFID reader
  this->nfc.begin();
  uint32_t versiondata = this->nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");//TODO:Remove this after debuging
    while (1);
  }
  this->nfc.SAMConfig();
}

void RFID::set_UID_NULL()
{
  this->UID="";
}

void RFID::set_UID()
{
  uint8_t success;
  uint8_t* uid = new uint8_t[7];
  uint8_t uidLength;

  success = this->nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success) {
    for (uint8_t i = 0; i < uidLength; i++) {
      //std::string str = std::to_string(static_cast<int>(value));
      this->UID = (static_cast<String>(uid[i]))+this->UID;
    }
    delete[] uid;
    delay(5000);
  }
}