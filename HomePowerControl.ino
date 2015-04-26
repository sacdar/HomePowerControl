#define WIFI 1

#include "SoftwareSerial.h"
#include "HPCControllerFactory.h"
#if WIFI
#include "WiFiController.h"
#else
#include "BluetoothController.h"
#include "GPIOController.h"
#include "CommandOperation.h"
#endif

ControllerFactory *controllerFactory = new HPCControllerFactory();
#if WIFI
WiFiController *wifiController = controllerFactory->createWiFiController();
#else
BluetoothController *bluetoothController = controllerFactory->createBTController(10, 11);
GPIOController *gpioController = new GPIOController(13, OUTPUT);
#endif


void setup()
{
#if WIFI
    wifiController->setup();
#else
    bluetoothController->setbaudRate(9600);
    gpioController->setPinLow();
    Serial.begin(9600);
    Serial.println("Enter AT commands:");
#endif
}

void loop()
{
#if WIFI
    wifiController->loop();
#else
    int i = 0;
    char *btCommand = bluetoothController->readLine();

    if (btCommand) {
        Serial.write(btCommand);
        Serial.write("\r\n");
        for (i = 0; i < sizeof(commandOperations) / sizeof(CommandOperation); i++) {
            if (strcmp(btCommand, commandOperations[i].command) == 0) {
                commandOperations[i].operation();
            }
        }
    }
#endif
}
