#define BUFFER_SIZE 512

#define SSID  "HomePowerControl"      // change this to match your WiFi SSID
#define PASS  "00000000"  // change this to match your WiFi password
#define PORT  "80"           // using port 8080 by default
#define TERM_OK "OK\r\n"

char buffer[BUFFER_SIZE];

#include "ESP8266Controller.h"
#include "Arduino.h"

#define dbg Serial    // use Serial for debug
SoftwareSerial esp(10, 11); // RX, TX

#define LED1 13



void ESP8266Controller::read_serial_until_new_line(char* rsp){
    
    bool is_end = false;
    int index = 0;
    while(true){
       char x = esp.read();
       delay(1);
       if(x == '\n')
           is_end = true;
       rsp[index]=x;
       index++;
       if(is_end)
           break;
       if(index>40)
           break;
    }
    rsp[index]='\0';
    return;
}

void ESP8266Controller::copy_to_buffer(char* buffer, char* rsp){
    int len = strlen(rsp);
    int i;
    int k=0;
    for(i = strlen(buffer); i< strlen(buffer)+strlen(rsp);i++){
        buffer[i] = rsp[k];
        k++;
    }
}

bool ESP8266Controller::is_equal(char* a, char* b){
    return strncmp(a,b,strlen(b))==0;
}

bool ESP8266Controller::wait_for_esp_response(int timeout, char* term = TERM_OK){
    unsigned long due_time = millis()+timeout;
    bool found = false;
    int i = 0;
    int len = strlen(term);
    //clear the buffer
    buffer[0]='\0';
    
    // wait for at most timeout milliseconds
    // or if OK\r\n is found
    while (millis() < due_time ) {
        if (esp.available()) {
            char new_input[50];
            read_serial_until_new_line(new_input);
            if (is_equal(new_input,term)){
                found = true;
            }
            copy_to_buffer(buffer,new_input);

            if(found)
                break;
        }
    }
    dbg.println(buffer);
    return found;
}

//Todo: modify to get_ip() to decouple with dbg.print()
void ESP8266Controller::show_ip(){
    // print device IP address
    dbg.print("device ip addr:");
    esp.println("AT+CIFSR");
    wait_for_esp_response(1000);
}

void ESP8266Controller::setup()
{

    pinMode(LED1, OUTPUT);

    // assume esp8266 operates at 115200 baud rate
    // change if necessary to match your modules' baud rate
    esp.begin(9600);

    dbg.begin(9600);
    dbg.println("begin.");
    while(!dbg){
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    setupWiFi();

    show_ip();
}

void ESP8266Controller::deal_with_input_http_request(char *input)
{
    input = input + 4;
    if (strncmp(input, "/led1/on", 8) == 0) {
        turn_on_led1();
    } else if (strncmp(input, "/led1/off", 9) == 0) {
        turn_off_led1();
    }
}

void ESP8266Controller::turn_on_led1()
{
    dbg.print("la la la ~ turn on led 1 !\n");
    digitalWrite(LED1, HIGH);
}

void ESP8266Controller::turn_off_led1()
{
    dbg.print("la la la ~ turn off led 1 !\n");
    digitalWrite(LED1, LOW);
}

void ESP8266Controller::loop()
{
    int ch_id, packet_len;
    char *pb;

    if (esp.available()){
        read_serial_until_new_line(buffer);
        dbg.print(buffer);
        
        if (strncmp(buffer, "+IPD,", 5) == 0) {
            // request: +IPD,ch,len:data
            sscanf(buffer + 5, "%d,%d", &ch_id, &packet_len);
            if (packet_len > 0) {
                // read serial until packet_len character received
                // start from :
                pb = buffer + 5;
                while (*pb != ':') pb++;
                pb++;
                if (strncmp(pb, "GET /", 5) == 0) {
                    deal_with_input_http_request(pb);
                    wait_for_esp_response(1000);
                    dbg.println("-> serve homepage");
                    serve_homepage(ch_id);
                }
            }
        }
    }
}

void ESP8266Controller::serve_homepage(int ch_id)
{
    String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n";
    String content = "";
    // output the value of each analog input pin
    for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
        int sensorReading = analogRead(analogChannel);
        content += "analog input ";
        content += analogChannel;
        content += " is ";
        content += sensorReading;
        content += "<br />\n";
    }

    header += "Content-Length:";
    header += (int)(content.length());
    header += "\r\n\r\n";
    esp.print("AT+CIPSEND=");
    esp.print(ch_id);
    esp.print(",");
    esp.println(header.length() + content.length());
    if (wait_for_esp_response(2000, "> ")) {
        esp.print(header);
        esp.print(content);
    } else {
        esp.print("AT+CIPCLOSE=");
        esp.println(ch_id);
    }
}


void ESP8266Controller::setupWiFi()
{
    // try empty AT command
    esp.println("AT");
    wait_for_esp_response(1000);

    // set mode 1 (client)
    esp.println("AT+CWMODE=1");
    wait_for_esp_response(1000);

    // reset WiFi module
    esp.print("AT+RST\r\n");
    wait_for_esp_response(1500);
    delay(3000);

    // join AP
    esp.print("AT+CWJAP=\"");
    esp.print(SSID);
    esp.print("\",\"");
    esp.print(PASS);
    esp.println("\"");
    // this may take a while, so wait for 5 seconds
    wait_for_esp_response(5000);

    esp.println("AT+CIPSTO=30");
    wait_for_esp_response(1000);

    // start server
    esp.println("AT+CIPMUX=1");
    wait_for_esp_response(1000);

    esp.print("AT+CIPSERVER=1,"); // turn on TCP service
    esp.println(PORT);
    wait_for_esp_response(1000);


}

