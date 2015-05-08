#ifndef _EEPROMCONTROLLER_H_
#define _EEPROMCONTROLLER_H_

#include <avr/eeprom.h>
#include <EEPROM.h>

// AbstractProductC
class EEPROMController
{
public:
    virtual void readObject(void *dst, int eepromOffset, size_t size) = 0;
    virtual void writeObject(void *src, int eepromOffset, size_t size) = 0;
};

#endif /* _EEPROMCONTROLLER_H_ */
