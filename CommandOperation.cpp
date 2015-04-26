#include "CommandOperation.h"
#include "GPIOController.h"

extern GPIOController *gpioController;

bool setLedOn()
{
    gpioController->setPinHigh();
    return true;
}

bool setLedOff()
{
    gpioController->setPinLow();
    return true;
}
