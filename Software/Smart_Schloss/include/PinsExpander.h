#ifndef PINSEXPANDER_H
#define PINSEXPANDER_H

#include <Adafruit_MCP23X17.h>
#include <Wire.h>

class PinsExpander{
    private:
    uint8_t _addr;  //This value is needed when more than one pins expander is used.Default address 0x20.
    
    int SDA_PIN;
    int SCL_PIN;    //I2C pins
    
    Adafruit_MCP23X17 mcp; //MCP23017 instance
    public:
    void setup();   //Init the pins expander
    PinsExpander(uint8_t address,int sda_pin, int scl_pin); //Constructor that defines I2C pins and address
    void setPinModeOutput(const int *pins, int numberOfPins); //Sets all outputPins array as output
    void setPinModeInput(const int *pins, int numberOfPins); //Sets all inputPins array as input
    void TurnHigh(const int pin, int numberOfPins); //Turn passed pins HIGH
    void TurnLow(const int pin, int numberOfPins); //Turn passed pins LOW
};
#endif