#ifndef _CONTROLLERFACTORY_H_
#define _CONTROLLERFACTORY_H_

#include "WiFiController.h"
#include "BluetoothController.h"

// AbstractFactory
class ControllerFactory
{
public:
    virtual WiFiController* createWiFiController() = 0;
    virtual BluetoothController* createBTController(int rx, int tx) = 0;
};

#endif /* _CONTROLLERFACTORY_H_ */
