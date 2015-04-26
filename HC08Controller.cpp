#include "Arduino.h"
#include "HC08Controller.h"

#define BT_SERIAL_READ_BUFFER_SIZE  32

SoftwareSerial* HC08Controller::btSerial = NULL;

HC08Controller::HC08Controller(int rx, int tx)
{
    btSerial = new SoftwareSerial(rx, tx);
}

bool HC08Controller::setbaudRate(int baudRate)
{
    if (btSerial == NULL)
        return false;
    btSerial->begin(baudRate);

    return true;
}

bool HC08Controller::enterAtCommandMode(int pin)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);

    return true;
}

bool HC08Controller::available()
{
    if (btSerial)
        return btSerial->available();

    return false;
}

char* HC08Controller::readLine()
{
    int index = 0;
    char serialString[BT_SERIAL_READ_BUFFER_SIZE];

    if (!btSerial)
        return NULL;
    if (!btSerial->available())
        return NULL;

    memset(serialString, 0x00, BT_SERIAL_READ_BUFFER_SIZE);

    while (true) {
        if (btSerial->available()) {
            serialString[index++] = btSerial->read();
        } else
            break;
        delay(1);
    }
    serialString[index] = 0x00;

    return serialString;
}
