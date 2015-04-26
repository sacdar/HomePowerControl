#include "Arduino.h"
#include "GPIOController.h"

GPIOController::GPIOController(int pin, int direction) : pin(pin), direction(direction)
{
    pinMode(this->pin, this->direction);
}

bool GPIOController::setPinDirection(int direction)
{
    this->direction = direction;
    pinMode(this->pin, direction);

    return true;
}

bool GPIOController::setPinHigh()
{
    digitalWrite(this->pin, HIGH);
}

bool GPIOController::setPinLow()
{
    digitalWrite(this->pin, LOW);
}
