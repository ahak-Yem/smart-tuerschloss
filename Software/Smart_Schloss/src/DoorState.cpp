#include <Arduino.h>
#include <DoorState.h>

String DoorState::MapBoxSensorPin(const int pin)
{
    //Kasten_Node_ID from our platform
    if (pin) {
  	switch (pin) {
      case PE_B0:
      return "12";
      case PE_B1:
      return "-1";
      case PE_B2:
      return "-1";
      case PE_B3:
      return "-1";
      case PE_B4:
      return "-1";
      case PE_B5:
      return "-1";
      case PE_B6:
      return "-1";
      case PE_B7:
      return "-1";//Indicate unused pin -> no box in drupal with this id.
      default:
      Serial.println("Invalid Box ID!");
      return "-2"; // Indicate failure: Invalid Box ID
    }
  }
  else{
    Serial.println("Box Id is empty!");
    return "-3";    // Indicate failure: Box Id is empty!
  }
}
