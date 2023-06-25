#include "RFID.h" 
#include <SPI.h>
#include<MFRC522.h>

void RFID::setup()
{
    Serial.begin(9600);
    SPI.begin();
    MFRC522 reader(SDA_PIN,RST_PIN);
    readerX=reader;
    readerX.PCD_Init();
}

void RFID::set_UID(){
    if ( ! readerX.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! readerX.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < readerX.uid.size; i++) 
  {
     //gibt UID zurück (wichtig !!).
     Serial.println(readerX.uid.uidByte[i], HEX);
     content.concat(String(readerX.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  //Serial.println("Authorized access !");
  //Serial.println();
  UID=content;
  readerX.PICC_HaltA(); // Halt the tag
}

void RFID::set_UID_NULL()
{
  UID="";
  }
 