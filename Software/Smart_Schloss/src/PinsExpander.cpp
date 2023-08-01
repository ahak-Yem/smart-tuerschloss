#include "PinsExpander.h"

TwoWire mcp_I2C(0); // Custom TwoWire instance using bus number 1

PinsExpander::PinsExpander(uint8_t address, int sda_pin, int scl_pin) 
: _addr(address), SDA_PIN(sda_pin), SCL_PIN(scl_pin) {}


void PinsExpander::setup(){ 
    mcp_I2C.begin(SDA_PIN,SCL_PIN); // Init I2C instance with pins 15(SDA) & 2(SCL)
    if (!mcp.begin_I2C(_addr,&mcp_I2C)) //Start mcp with custom I2C "mcp_I2C"
    {
        while (1);
    }
}

void PinsExpander::setPinModeOutput(const int *pins, int numberOfPins){
    for(int i=0; i<numberOfPins;i=i+1){
        mcp.pinMode(pins[i],OUTPUT);
    }
}

void PinsExpander::setPinModeInput(const int *pins, int numberOfPins){
    for(int i=0; i<numberOfPins;i=i+1){
        mcp.pinMode(pins[i],INPUT);
    }
}

void PinsExpander::TurnHigh(const int *pins, int numberOfPins) {
  for (int i = 0; i < numberOfPins; i++) {
    mcp.digitalWrite(pins[i], HIGH);
  }
}

void PinsExpander::TurnLow(const int *pins, int numberOfPins) {
  for (int i = 0; i < numberOfPins; i++) {
    mcp.digitalWrite(pins[i], LOW);
  }
}
    
