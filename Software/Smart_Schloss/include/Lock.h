#include <string.h>
#include <Arduino.h> 

class Lock{
    private:
    public: 
    void setup();
    bool OpenLock(int lock_pin);
};