#ifndef _ESP8266CONTROLLER_H_
#define _ESP8266CONTROLLER_H_

#include <SoftwareSerial.h>
#include "WiFiController.h"

typedef uint8_t byte;

class ESP8266Controller : public WiFiController
{
public:
    String wait_for_esp_response(int timeout, String term);
    void setup();
    void deal_with_input_http_request(String input);
    void turn_on_led1();
    void turn_off_led1();
    void loop();
    void serve_homepage(int ch_id, String input_content);
    void setupWiFi();
    void show_ip();
private:
    int get_channel(String input);
};

#endif //_ESP8266CONTROLLER_H_
