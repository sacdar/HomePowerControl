#ifndef _ESP8266CONTROLLER_H_
#define _ESP8266CONTROLLER_H_

#include <SoftwareSerial.h>
#include "WiFiController.h"

typedef uint8_t byte;

class ESP8266Controller : public WiFiController
{
public:
    bool wait_for_esp_response(int timeout, char *term);
    void setup();
    void deal_with_input_http_request(char *input);
    void turn_on_led1();
    void turn_off_led1();
    void loop();
    void serve_homepage(int ch_id);
    void setupWiFi();
    void show_ip();
private:
    void read_serial_until_new_line(char* rsp);
    void copy_to_buffer(char* buffer, char* rsp);
    bool is_equal(char* a, char* b);
};

#endif //_ESP8266CONTROLLER_H_
