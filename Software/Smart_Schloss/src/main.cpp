//#include <SPI.h>
//#include<MFRC522.h>
//#define SDA_PIN 21
//#define RST_PIN 22

#include <Arduino.h>
#include <string>
#include <RFID.h>

int IN1_PIN = 32;
RFID rfid;

//MFRC522 reader(SDA_PIN,RST_PIN);

void setup() {
  pinMode(IN1_PIN, OUTPUT);
  rfid.setup();
}

void loop() {
rfid.set_UID();
String content=rfid.get_UID();
if(content!= ""){
  // Lock the magnetic lock
  digitalWrite(IN1_PIN, HIGH);  // Set IN1 to HIGH
  delay(2000);  // Unlock for 20 seconds
  
  // Unlock the magnetic lock
  digitalWrite(IN1_PIN, LOW);   // Set IN1 to LOW
  delay(500);
  content="";
  rfid.set_UID_NULL();
}  
}
