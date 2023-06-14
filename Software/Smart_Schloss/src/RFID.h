#include <SPI.h>
#include<MFRC522.h>
class RFID{
    private:
        const int SDA_PIN= 21;
        const int RST_PIN =22;
        String UID="";
        MFRC522 readerX;
    public:
    void setup();
    String get_UID(){
        return UID;
    }
    void set_UID();
    void set_UID_NULL();
};