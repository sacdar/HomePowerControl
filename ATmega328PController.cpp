#include "ATmega328PController.h"

void ATmega328PController::readObject(void *dst, int eepromOffset, size_t size)
{
    eeprom_read_block((void*)dst, (void*)eepromOffset, size);
}

void ATmega328PController::writeObject(void *src, int eepromOffset, size_t size)
{
    for (int i = 0; i < 255; i++)
        EEPROM.write(i, 0x00);
    eeprom_write_block((const void*)src, (void*)eepromOffset, size);
}
