#ifndef _WIFICONTROLLER_H_
#define _WIFICONTROLLER_H_

struct WiFiSettings {
    char ssid[32];
    char password[64];
} wifiSettings;

// AbstractProductA
class WiFiController
{
public:
    virtual void loop() = 0;
    virtual void setup() = 0;
};

#endif /* _WIFICONTROLLER_H_ */
