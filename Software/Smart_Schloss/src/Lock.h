#include <string.h>
#include <Arduino.h> 

class Lock{
    private:
    int IN1_PIN = 32;
    public: 
    void setup();
    int OpenLock(String UID);
};