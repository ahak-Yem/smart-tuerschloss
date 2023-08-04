#include <string.h>
#include <Arduino.h> 
#include "RealTimeManager.h"
#include "DB.h"

class Lock{
    private:
    String getCurrentTime(RealTimeManager timeManager);
    public:
    Lock(); 
    bool validateBooking(BookingData booking,RealTimeManager timeManager);
    String OpenLock(String UID);
};