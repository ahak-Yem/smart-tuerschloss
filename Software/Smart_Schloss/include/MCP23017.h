#include <Adafruit_MCP23X17.h>

//Use this variables to turn the wished MCP23017 pin(s) on/off.
// #define A0 0    
// #define A1 1     
// #define A2 2     
// #define A3 3
// #define A4 4
// #define A5 5
// #define A6 6
// #define A7 7
// #define B1 8
// #define B2 9
// #define B3 10
// #define B4 11
// #define B5 12
// #define B6 13
// #define B7 14


class MCP23017{
    private:
    public:
    void setup();
    void setPinModeOutput(int *pins, int numberOfPins);
    void setPinModeInput(int *pins, int numberOfPins);
    void TurnHigh(const int pin);
    void TurnLow(const int pin);
    void changeAddress(uint8_t address);
    
};