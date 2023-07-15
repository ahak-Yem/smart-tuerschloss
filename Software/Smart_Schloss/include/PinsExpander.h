#ifndef PINSEXPANDER_H
#define PINSEXPANDER_H

#include <Adafruit_MCP23X17.h>
#include <Wire.h>

class PinsExpander{
    private:
    uint8_t _addr;
    int SDA_PIN;
    int SCL_PIN;
    Adafruit_MCP23X17 mcp; //MCP23017 instance
    public:
    void setup();
    PinsExpander(uint8_t address,int sda_pin, int scl_pin);
    void setPinModeOutput(const int *pins, int numberOfPins);
    void setPinModeInput(const int *pins, int numberOfPins);
    void TurnHigh(const int *pins, int numberOfPins);
    void TurnLow(const int *pins, int numberOfPins);
};
#endif