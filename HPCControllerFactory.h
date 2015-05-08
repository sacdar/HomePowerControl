#ifndef _HPCCONTROLLERFACTORY_H_
#define _HPCCONTROLLERFACTORY_H_

#include "ControllerFactory.h"

// ConcreteFactoryA
class HPCControllerFactory : public ControllerFactory
{
public:
    WiFiController* createWiFiController();
    BluetoothController* createBTController(int rx, int tx);
    EEPROMController* createEEPROMController();
};

#endif //_HPCCONTROLLERFACTORY_H_
