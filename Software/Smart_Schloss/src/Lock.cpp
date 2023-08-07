#include "Lock.h"


Lock::Lock(){
  Serial.println("Lock is initialized");
}

bool Lock::validateBooking(BookingData booking, RealTimeManager &timeManager)
{
  timeManager.update();

  //This gets the current datetime in Germany from a Server as a String.
  String currentTime = timeManager.getCurrentDateTime();
  delay(50);

  //Converts the datetime string to time_t obj to be used in if.
  time_t currentDateTime = timeManager.convertStringToTime(currentTime);
  delay(50);

  //Converts the booking reserve date to time_t obj to be used in if.
  time_t reservationDateTime = timeManager.convertStringToTime(booking.reservierungsdatum);
  delay(50);

  //Converts the booking return date to time_t obj to be used in if.
  time_t returnDateTime = timeManager.convertStringToTime(booking.rueckgabedatum);
  delay(50);

  //Converts the enum values to strings to be used in if
  String bookedCondition=DB::bookingZustandToString(BuchungZustandEnum::gebucht);
  String collectedCondition=DB::bookingZustandToString(BuchungZustandEnum::abgeholt);
  String lateCondition=DB::bookingZustandToString(BuchungZustandEnum::spaet);
  delay(50);
 
  // Compare if reservationDateTime is equal or after currentDateTime
  // and before or equal to returnDateTime.
  if (reservationDateTime <= currentDateTime && currentDateTime <= returnDateTime) {
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
      return PE_A1;
      case 3:
      return PE_A2;
      case 4:
      return PE_A3;
      case 5:
      return PE_A4;
      case 6:
      return PE_A5;
      case 7:
      return PE_A6;
      case 8:
      return PE_A7;
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