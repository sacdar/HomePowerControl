#ifndef _ESP8266CONTROLLER_H_
#define _ESP8266CONTROLLER_H_

#include <SoftwareSerial.h>
#include "WiFiController.h"

typedef uint8_t byte;

class ESP8266Controller : public WiFiController
{
public:
    byte wait_for_esp_response(int timeout, char *term);
    void setup();
    bool read_till_eol();
    void deal_with_input_http_request(char *input);
    void turn_on_led1();
    void turn_off_led1();
    void loop();
    void serve_homepage(int ch_id);
    void setupWiFi();
    void show_ip();
};

#endif //_ESP8266CONTROLLER_H_
