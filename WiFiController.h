#ifndef _WIFICONTROLLER_H_
#define _WIFICONTROLLER_H_

// AbstractProductA
class WiFiController
{
public:
    virtual void loop() = 0;
    virtual void setup() = 0;
};

#endif /* _WIFICONTROLLER_H_ */
