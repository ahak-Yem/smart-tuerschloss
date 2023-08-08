#include <string.h>
#include <Arduino.h> 
#include "RealTimeManager.h"
#include "DB.h"
  #define PE_A0 0    
  #define PE_A1 1     
  #define PE_A2 2     
  #define PE_A3 3
  #define PE_A4 4
  #define PE_A5 5
  #define PE_A6 6
  #define PE_A7 7
class Lock{
    private:
    public:
    Lock(); 
    bool validateBooking(BookingData booking,RealTimeManager &timeManager);
    int MapBoxLockPin(const char* boxId);
};