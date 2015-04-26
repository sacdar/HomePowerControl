#ifndef _HC08CONTROLLER_H_
#define _HC08CONTROLLER_H_

#include "SoftwareSerial.h"
#include "BluetoothController.h"

class HC08Controller : public BluetoothController
{
private:
    static SoftwareSerial *btSerial;

public:
    HC08Controller(int rx, int tx);

    bool setbaudRate(int baudRate);
    bool enterAtCommandMode(int pin);
    bool available();
    char* readLine();
};

#endif //_HC08CONTROLLER_H_
