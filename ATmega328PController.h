#ifndef _ATMEGA328PCONTROLLER_H_
#define _ATMEGA328PCONTROLLER_H_

#include "EEPROMController.h"

class ATmega328PController : public EEPROMController
{
public:
    void readObject(void *dst, int eepromOffset, size_t size);
    void writeObject(void *src, int eepromOffset, size_t size);
};

#endif /* _ATMEGA328PCONTROLLER_H_ */
