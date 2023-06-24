#include "MCP23017.h"
#include <Adafruit_MCP23X17.h>

//MCP23017 instance
Adafruit_MCP23X17 mcp;

void MCP23017::setup(){ 
    //Start mcp with I2C
    if (!mcp.begin_I2C()) 
    {
        while (1);
    }
}

void MCP23017::setPinModeOutput(int *pins, int numberOfPins){
    for(int i=0; i<numberOfPins;i=i+1){
        mcp.pinMode(pins[i],OUTPUT);
    }
}

void MCP23017::setPinModeInput(int *pins, int numberOfPins){
    for(int i=0; i<numberOfPins;i=i+1){
        mcp.pinMode(pins[i],INPUT);
    }
}

void MCP23017::changeAddress(uint8_t address){
    if (!mcp.begin_I2C(address)) 
    {
        while (1);
    }
}

void MCP23017::TurnHigh(const int pin){
    mcp.digitalWrite(pin, HIGH);
}

void MCP23017::TurnLow(const int pin){
        mcp.digitalWrite(pin, LOW);
}
    
