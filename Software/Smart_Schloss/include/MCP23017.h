#include <Adafruit_MCP23X17.h>

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