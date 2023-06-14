#include<Lock.h>
void Lock::setup()
{
  pinMode(IN1_PIN, OUTPUT);
}
int Lock::OpenLock(String UID){
    if(UID == "45B249ADE5680"){
  // Lock the magnetic lock
  digitalWrite(IN1_PIN, HIGH);  // Set IN1 to HIGH
  delay(2000);  // Unlock for 20 seconds
  
  // Unlock the magnetic lock
  digitalWrite(IN1_PIN, LOW);   // Set IN1 to LOW
  delay(500);
  UID="";
  return 1; 
}   
delay(1000);
return 0;
}