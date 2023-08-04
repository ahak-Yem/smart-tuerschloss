#include "Lock.h"


Lock::Lock(){}

String Lock::getCurrentTime(RealTimeManager timeManager)
{
  timeManager.update();
  String currentDateTime = timeManager.getCurrentDateTime();
  Serial.print("Current date and time: ");
  Serial.println(currentDateTime);
  return currentDateTime;
}

bool Lock::validateBooking(BookingData booking, RealTimeManager timeManager)
{
  String currentTime = this->getCurrentTime(timeManager);
  time_t currentDateTime = timeManager.convertStringToTime(currentTime);
  time_t reservationDateTime = timeManager.convertStringToTime(booking.reservierungsdatum);
  time_t returnDateTime = timeManager.convertStringToTime(booking.rueckgabedatum);

  String bookedCondition=DB::bookingZustandToString(BuchungZustandEnum::gebucht);
  String collectedCondition=DB::bookingZustandToString(BuchungZustandEnum::abgeholt);
  String lateCondition=DB::bookingZustandToString(BuchungZustandEnum::spaet);

  // Compare if reservationDateTime is equal or after currentDateTime
  // and before or equal to returnDateTime.
  if (reservationDateTime >= currentDateTime && reservationDateTime <= returnDateTime) {
    Serial.println("The booking is in the valid time range!");
    //Check if booking state is valid
    if(String(booking.zustandBuchung)==bookedCondition or 
    String(booking.zustandBuchung)==collectedCondition or 
    String(booking.zustandBuchung)==lateCondition){
      Serial.println("The booking has a valid state!");
      return true;
    }
    else{
      Serial.println("The booking state is not valid!");
      return false;
    }
  } else {
    Serial.println("The booking time range is not valid!");
    return false;
  }
  return false; //Will never run but keep it for weird behaviours
}

//TODO: Repair this to be dynamic
String Lock::OpenLock(String UID){
    if(UID == "45B249ADE5680"){
      return UID;
    }
  else if(UID == "AD268838"){
    return UID;
  }
  else if (UID == "E61CED30"){
        return UID;
  }
  else 
  return "";
}   

