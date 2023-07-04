#include <Wire.h>
#include <Adafruit_PN532.h>

class RFID{
private:
    const int SDA_PIN;
    const int SCL_PIN;
    String UID="";
    Adafruit_PN532 nfc;
public:
    RFID(int sda_pin,int scl_pin);
    String get_UID();
    void set_UID();
    void set_UID_NULL();
};