#include<Lock.h>

void Lock::setup()
{
 // pinMode(IN1_PIN, OUTPUT);
}
bool Lock::OpenLock(int lock_pin){
  // Lock the magnetic lock
  digitalWrite(lock_pin, HIGH);  // Set IN1 to HIGH
  delay(3000);  // Unlock for 20 seconds
  
  // Unlock the magnetic lock
  digitalWrite(lock_pin, LOW);   // Set IN1 to LOW
  delay(300);
  return true;  
}