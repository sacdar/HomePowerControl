#define WIFI 1

#include "SoftwareSerial.h"
#include "HPCControllerFactory.h"
#if WIFI
#else
#include "GPIOController.h"
#include "CommandOperation.h"
#endif

ControllerFactory *controllerFactory = new HPCControllerFactory();
EEPROMController *eepromController = controllerFactory->createEEPROMController();
#if WIFI
WiFiController *wifiController = controllerFactory->createWiFiController();
#else
BluetoothController *bluetoothController = controllerFactory->createBTController(10, 11);
GPIOController *gpioController = new GPIOController(13, OUTPUT);
#endif

void wifiConfig()
{
    strcpy(wifiController->wifiSettings.ssid, "aaaa");
    strcpy(wifiController->wifiSettings.password, "00000000");
    eepromController->writeObject(&wifiController->wifiSettings, 0, sizeof(struct WiFiSettings));
    eepromController->readObject(&wifiController->wifiSettings, 0, sizeof(struct WiFiSettings));
    for (int i = 0; i < strlen(wifiController->wifiSettings.ssid); i++)
        Serial.print(wifiController->wifiSettings.ssid[i]);
    Serial.println();
    for (int i = 0; i < strlen(wifiController->wifiSettings.password); i++)
        Serial.print(wifiController->wifiSettings.password[i]);
}

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
