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
  return false; //Will never run but keep it in case of any weird behaviours
}


int Lock::BoxLockPin(const char* boxId){
  if (boxId) {
    // Convert the box ID to an integer
    int boxNumber = atoi(boxId);
  	switch (boxNumber) {
      case 1:
      return PE_A0;
      case 2:
      return PE_A0;
      case 3:
      return PE_A0;
      case 4:
      return PE_A0;
      case 5:
      return PE_A0;
      case 6:
      return PE_A0;
      case 7:
      return PE_A0;
      case 8:
      return PE_A0;
      default:
      Serial.println("Invalid Box ID!");
      return -1; // Indicate failure
    }
  }
  else{
    Serial.println("Box Id is empty!");
    return false;
  }   
}