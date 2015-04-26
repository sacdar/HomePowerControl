#ifndef _BLUETOOTHCONTROLLER_H_
#define _BLUETOOTHCONTROLLER_H_

// AbstractProductB
class BluetoothController
{
public:
    virtual bool setbaudRate(int baudRate) = 0;
    virtual bool enterAtCommandMode(int pin) = 0;
    virtual bool available() = 0;
    virtual char* readLine() = 0;
};

#endif /* _BLUETOOTHCONTROLLER_H_ */
