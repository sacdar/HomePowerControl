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

void ESP8266Controller::loop()
{
    int ch_id, packet_len;
    char *pb;

    if (esp.available()){
        
        String rsp = esp.readString();
        dbg.println("<<===esp===");
        dbg.print(rsp);
        dbg.println("======>>");
        
        if(rsp.indexOf("+IPD")>=0){
            deal_with_input_http_request(rsp);
        }
    }
}


//Todo: modify to get_ip() to decouple with dbg.print()
void ESP8266Controller::show_ip(){
    // print device IP address
    dbg.print("device ip addr:");
    esp.println("AT+CIFSR");
    
    String rsp = wait_for_esp_response(1000,TERM_OK);
}

String ESP8266Controller::wait_for_esp_response(int timeout, String term = TERM_OK){
    
    unsigned long due_time = millis()+timeout;
    
    String rsp = "";
    while(!rsp.endsWith(term) && millis() < due_time ){
        rsp = rsp + esp.readString();
    }
    dbg.println(rsp);
    return rsp;
}

void ESP8266Controller::deal_with_input_http_request(String input)
{
    if (input.indexOf("/led1/on") > 0) {
        turn_on_led1();
    } else if (input.indexOf("/led1/off") > 0) {
        turn_off_led1();
    }
    
    int channel = get_channel(input);
    serve_homepage(channel);
}


int ESP8266Controller::get_channel(String input){

    //It should looks like this:
    //+IPD,1,432:GET /led1/on HTTP/1.1
    String x = input.substring(input.indexOf("+IPD,")+5,input.indexOf("GET"));
    // now x should be "1,432:"
    x = x.substring(0,x.indexOf(","));
    // now x should be "1"
    
    int channel=x.toInt();
    dbg.print("channel is ");
    dbg.println(channel);
    return channel;
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
    if (wait_for_esp_response(2000, "> ").endsWith("> ")) {
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
    esp.println("AT+CWMODE=3");
    String rsp = wait_for_esp_response(1000);
    
    //reset if cw mode is change
    if(rsp.indexOf("no change")<0){
        // reset WiFi module
        esp.print("AT+RST\r\n");
        wait_for_esp_response(1500);
        delay(3000);
    }
    
    esp.println("AT+CWSAP=\"AAA\",\"00000000\",5,0");
    wait_for_esp_response(1000);
    
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

