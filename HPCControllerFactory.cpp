#include "HPCControllerFactory.h"
#include "ESP8266Controller.h"
#include "HC08Controller.h"

WiFiController* HPCControllerFactory::createWiFiController()
{
    return new ESP8266Controller;
}

BluetoothController* HPCControllerFactory::createBTController(int rx, int tx)
{
    return new HC08Controller(rx, tx);
}
