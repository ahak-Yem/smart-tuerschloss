#include "PinsExpander.h"
#include <Adafruit_MCP23X17.h>
#include <Wire.h>

Adafruit_MCP23X17 mcp; //MCP23017 instance

#define SDA_Pin 15
#define SCL_Pin 2 // Custom SDA & SCL pins


TwoWire mcp_I2C(1); // Custom TwoWire instance using bus number 1

void PinsExpander::setup(){ 
    mcp_I2C.begin(SDA_Pin,SCL_Pin); // Init I2C instance with pins 15(SDA) & 2(SCL)
    if (!mcp.begin_I2C(0x20,&mcp_I2C)) //Start mcp with custom I2C "mcp_I2C"
    {
        while (1);
    }
}

void PinsExpander::setPinModeOutput(int *pins, int numberOfPins){
    for(int i=0; i<numberOfPins;i=i+1){
        mcp.pinMode(pins[i],OUTPUT);
    }
}

void PinsExpander::setPinModeInput(int *pins, int numberOfPins){
    for(int i=0; i<numberOfPins;i=i+1){
        mcp.pinMode(pins[i],INPUT);
    }
}

void PinsExpander::changeAddress(uint8_t address){
    if (!mcp.begin_I2C(address)) 
    {
        while (1);
    }
}

void PinsExpander::TurnHigh(const int pin){
    mcp.digitalWrite(pin, HIGH);
}

void PinsExpander::TurnLow(const int pin){
        mcp.digitalWrite(pin, LOW);
}
    
