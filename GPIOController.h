#ifndef _GPIOCONTROLLER_H_
#define _GPIOCONTROLLER_H_

class GPIOController
{
private:
    int pin;
    int direction;

public:
    GPIOController(int pin, int direction);

    bool setPinDirection(int direction);
    bool setPinHigh();
    bool setPinLow();
};

#endif //_GPIOCONTROLLER_H_
