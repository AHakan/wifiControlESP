


//---------------------- Includes ----------------------//
#include "NeoBlink.h"
#include <ESP8266WiFi.h>


//---------------------- Defines ----------------------//
#ifndef STASSID
#define STASSID "ASUS"
#define STAPSK  "*****"
#endif


//---------------------- Variables ----------------------//
const char* ssid = STASSID;
const char* password = STAPSK;


// The certificate is stored in PMEM
static const uint8_t x509[] PROGMEM = {
  0x30, 0x82, 0x01, 0x3d, 0x30, 0x81, 0xe8, 0x02, 0x09, 0x00, 0xfe, 0x56,
  0x46, 0xf2, 0x78, 0xc6, 0x51, 0x17, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86,
  0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x30, 0x26, 0x31,
  0x10, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c, 0x07, 0x45, 0x53,
  0x50, 0x38, 0x32, 0x36, 0x36, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55,
  0x04, 0x03, 0x0c, 0x09, 0x31, 0x32, 0x37, 0x2e, 0x30, 0x2e, 0x30, 0x2e,
  0x31, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x37, 0x30, 0x33, 0x31, 0x38, 0x31,
  0x34, 0x34, 0x39, 0x31, 0x38, 0x5a, 0x17, 0x0d, 0x33, 0x30, 0x31, 0x31,
  0x32, 0x35, 0x31, 0x34, 0x34, 0x39, 0x31, 0x38, 0x5a, 0x30, 0x26, 0x31,
  0x10, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c, 0x07, 0x45, 0x53,
  0x50, 0x38, 0x32, 0x36, 0x36, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55,
  0x04, 0x03, 0x0c, 0x09, 0x31, 0x32, 0x37, 0x2e, 0x30, 0x2e, 0x30, 0x2e,
  0x31, 0x30, 0x5c, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
  0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x4b, 0x00, 0x30, 0x48, 0x02,
  0x41, 0x00, 0xc6, 0x72, 0x6c, 0x12, 0xe1, 0x20, 0x4d, 0x10, 0x0c, 0xf7,
  0x3a, 0x2a, 0x5a, 0x49, 0xe2, 0x2d, 0xc9, 0x7a, 0x63, 0x1d, 0xef, 0xc6,
  0xbb, 0xa3, 0xd6, 0x6f, 0x59, 0xcb, 0xd5, 0xf6, 0xbe, 0x34, 0x83, 0x33,
  0x50, 0x80, 0xec, 0x49, 0x63, 0xbf, 0xee, 0x59, 0x94, 0x67, 0x8b, 0x8d,
  0x81, 0x85, 0x23, 0x24, 0x06, 0x52, 0x76, 0x55, 0x9d, 0x18, 0x09, 0xb3,
  0x3c, 0x10, 0x40, 0x05, 0x01, 0xf3, 0x02, 0x03, 0x01, 0x00, 0x01, 0x30,
  0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b,
  0x05, 0x00, 0x03, 0x41, 0x00, 0x69, 0xdc, 0x6c, 0x9b, 0xa7, 0x62, 0x57,
  0x7e, 0x03, 0x01, 0x45, 0xad, 0x9a, 0x83, 0x90, 0x3a, 0xe7, 0xdf, 0xe8,
  0x8f, 0x46, 0x00, 0xd3, 0x5f, 0x2b, 0x0a, 0xde, 0x92, 0x1b, 0xc5, 0x04,
  0xc5, 0xc0, 0x76, 0xf4, 0xf6, 0x08, 0x36, 0x97, 0x27, 0x82, 0xf1, 0x60,
  0x76, 0xc2, 0xcd, 0x67, 0x6c, 0x4b, 0x6c, 0xca, 0xfd, 0x97, 0xfd, 0x33,
  0x9e, 0x12, 0x67, 0x6b, 0x98, 0x7e, 0xd5, 0x80, 0x8f
};

// And so is the key.  These could also be in DRAM
static const uint8_t rsakey[] PROGMEM = {
  0x30, 0x82, 0x01, 0x3a, 0x02, 0x01, 0x00, 0x02, 0x41, 0x00, 0xc6, 0x72,
  0x6c, 0x12, 0xe1, 0x20, 0x4d, 0x10, 0x0c, 0xf7, 0x3a, 0x2a, 0x5a, 0x49,
  0xe2, 0x2d, 0xc9, 0x7a, 0x63, 0x1d, 0xef, 0xc6, 0xbb, 0xa3, 0xd6, 0x6f,
  0x59, 0xcb, 0xd5, 0xf6, 0xbe, 0x34, 0x83, 0x33, 0x50, 0x80, 0xec, 0x49,
  0x63, 0xbf, 0xee, 0x59, 0x94, 0x67, 0x8b, 0x8d, 0x81, 0x85, 0x23, 0x24,
  0x06, 0x52, 0x76, 0x55, 0x9d, 0x18, 0x09, 0xb3, 0x3c, 0x10, 0x40, 0x05,
  0x01, 0xf3, 0x02, 0x03, 0x01, 0x00, 0x01, 0x02, 0x40, 0x35, 0x0b, 0x74,
  0xd3, 0xff, 0x15, 0x51, 0x44, 0x0f, 0x13, 0x2e, 0x9b, 0x0f, 0x93, 0x5c,
  0x3f, 0xfc, 0xf1, 0x17, 0xf9, 0x72, 0x94, 0x5e, 0xa7, 0xc6, 0xb3, 0xf0,
  0xfe, 0xc9, 0x6c, 0xb1, 0x1e, 0x83, 0xb3, 0xc6, 0x45, 0x3a, 0x25, 0x60,
  0x7c, 0x3d, 0x92, 0x7d, 0x53, 0xec, 0x49, 0x8d, 0xb5, 0x45, 0x10, 0x99,
  0x9b, 0xc6, 0x22, 0x3a, 0x68, 0xc7, 0x13, 0x4e, 0xb6, 0x04, 0x61, 0x21,
  0x01, 0x02, 0x21, 0x00, 0xea, 0x8c, 0x21, 0xd4, 0x7f, 0x3f, 0xb6, 0x91,
  0xfa, 0xf8, 0xb9, 0x2d, 0xcb, 0x36, 0x36, 0x02, 0x5f, 0xf0, 0x0c, 0x6e,
  0x87, 0xaa, 0x5c, 0x14, 0xf6, 0x56, 0x8e, 0x12, 0x92, 0x25, 0xde, 0xb3,
  0x02, 0x21, 0x00, 0xd8, 0x99, 0x01, 0xf1, 0x04, 0x0b, 0x98, 0xa3, 0x71,
  0x56, 0x1d, 0xea, 0x6f, 0x45, 0xd1, 0x36, 0x70, 0x76, 0x8b, 0xab, 0x69,
  0x30, 0x58, 0x9c, 0xe0, 0x45, 0x97, 0xe7, 0xb6, 0xb5, 0xef, 0xc1, 0x02,
  0x21, 0x00, 0xa2, 0x01, 0x06, 0xc0, 0xf2, 0xdf, 0xbc, 0x28, 0x1a, 0xb4,
  0xbf, 0x9b, 0x5c, 0xd8, 0x65, 0xf7, 0xbf, 0xf2, 0x5b, 0x73, 0xe0, 0xeb,
  0x0f, 0xcd, 0x3e, 0xd5, 0x4c, 0x2e, 0x91, 0x99, 0xec, 0xb7, 0x02, 0x20,
  0x4b, 0x9d, 0x46, 0xd7, 0x3c, 0x01, 0x4c, 0x5d, 0x2a, 0xb0, 0xd4, 0xaa,
  0xc6, 0x03, 0xca, 0xa0, 0xc5, 0xac, 0x2c, 0xe0, 0x3f, 0x4d, 0x98, 0x71,
  0xd3, 0xbd, 0x97, 0xe5, 0x55, 0x9c, 0xb8, 0x41, 0x02, 0x20, 0x02, 0x42,
  0x9f, 0xd1, 0x06, 0x35, 0x3b, 0x42, 0xf5, 0x64, 0xaf, 0x6d, 0xbf, 0xcd,
  0x2c, 0x3a, 0xcd, 0x0a, 0x9a, 0x4d, 0x7c, 0xad, 0x29, 0xd6, 0x36, 0x57,
  0xd5, 0xdf, 0x34, 0xeb, 0x26, 0x03
};

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServerSecure server(443);

IPAddress staticIP(192, 168, 1, 90); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask


//---------------------- Setup ----------------------//
void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println(ssid);
  WiFi.config(staticIP, subnet, gateway);
  WiFi.begin(ssid, password);

  // Set the certificates from PMEM (if using DRAM remove the _P from the call)
  server.setServerKeyAndCert_P(rsakey, sizeof(rsakey), x509, sizeof(x509));

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  //NeoBlink Setup
  NeoBlink.SETUP();
}


//---------------------- Main ----------------------//
void loop() {
  // Check if a client has connected
  WiFiClientSecure client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  unsigned long timeout = millis() + 3000;
  while (!client.available() && millis() < timeout) {
    delay(1);
  }
  if (millis() > timeout) {
    Serial.println("timeout");
    client.flush();
    client.stop();
    return;
  }
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1) {
    NeoBlink.OFF();
  } else if (req.indexOf("/color/99991a") != -1){
    NeoBlink.GREEN();
  } else if (req.indexOf("/color/99991b") != -1){
    NeoBlink.BLUE();
  } else if (req.indexOf("/color/99991c") != -1){
    NeoBlink.RED();
  } else if (req.indexOf("/color/99991d") != -1){
    NeoBlink.WHITE();
  } else if (req.indexOf("/color/99991e") != -1){
    NeoBlink.YELLOW();
  }  else if (req.indexOf("/color/99991f") != -1){
    NeoBlink.ORANGE();
  }  else if (req.indexOf("/color/99991g") != -1){
    NeoBlink.PURPLE();
  }  else if (req.indexOf("/color/99991h") != -1){
    NeoBlink.PINK();
  }  else if (req.indexOf("/color/99991i") != -1){
    NeoBlink.LIGHTBLUE();
  }  else if (req.indexOf("/color/99991k") != -1){
    NeoBlink.LIGHTGREEN();
  }  else if (req.indexOf("/color/99991m") != -1){
    NeoBlink.LIGHTRED();
  }   else {
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
    s += "<html><head>";
    s += "<title>Home Automation</title>";
    s += "<style>";
    s += ".button {border: none;color: white;padding: 45px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;transition-duration: 0.4s;cursor: pointer;}";
    s += ".button30:hover {background-color: white; border: 2px solid #555555;}.button30 {background-color: #555555; border: 2px solid #555555;}";  //OFF
    s += ".button1:hover {background-color: white; border: 2px solid #00ff00;}.button1 {background-color: #00ff00; border: 2px solid #00ff00;}";    //GREEN
    s += ".button2:hover {background-color: white; border: 2px solid #0000ff;}.button2 {background-color: #0000ff; border: 2px solid #0000ff;}";    //BLUE
    s += ".button3:hover {background-color: white; border: 2px solid #ff0000;}.button3 {background-color: #ff0000; border: 2px solid #ff0000;}";    //RED
    s += ".button4:hover {background-color: white; border: 2px solid #c0c0c0;}.button4 {background-color: #c0c0c0; border: 2px solid #c0c0c0;}";    //WHITE
    s += ".button5:hover {background-color: white; border: 2px solid #ffff00;}.button5 {background-color: #ffff00; border: 2px solid #ffff00;}";    //YELLOW
    s += ".button6:hover {background-color: white; border: 2px solid #ff8000;}.button6 {background-color: #ff8000; border: 2px solid #ff8000;}";    //ORANGE
    s += ".button7:hover {background-color: white; border: 2px solid #7f00ff;}.button7 {background-color: #7f00ff; border: 2px solid #7f00ff;}";    //PURPLE
    s += ".button8:hover {background-color: white; border: 2px solid #ff00ff;}.button8 {background-color: #ff00ff; border: 2px solid #ff00ff;}";    //PINK
    s += ".button9:hover {background-color: white; border: 2px solid #0080ff;}.button9 {background-color: #0080ff; border: 2px solid #0080ff;}";    //LIGHTBLUE
    s += ".button10:hover {background-color: white; border: 2px solid #00ff80;}.button10 {background-color: #00ff80; border: 2px solid #00ff80;}";    //LIGHTGREEN
    s += ".button11:hover {background-color: white; border: 2px solid #ff4040;}.button11 {background-color: #ff4040; border: 2px solid #ff4040;}";    //LIGHTRED
    s += "</style>";
    s += "</head><body><center>";
    
    s += "<a href=\"/color/99991e\"><button class=\"button button5\"></button></a>";        //YELLOW
    s += "<a href=\"/color/99991k\"><button class=\"button button10\"></button></a>";        //LIGHTGREEN
    s += "<a href=\"/color/99991a\"><button class=\"button button1\"></button></a><br>";        //GREEN

    s += "<a href=\"/color/99991g\"><button class=\"button button7\"></button></a>";        //PURPLE
    s += "<a href=\"/color/99991i\"><button class=\"button button9\"></button></a>";        //LIGHTBLUE
    s += "<a href=\"/color/99991b\"><button class=\"button button2\"></button></a><br>";        //BLUE

    s += "<a href=\"/color/99991f\"><button class=\"button button6\"></button></a>";        //ORANGE
    s += "<a href=\"/color/99991m\"><button class=\"button button11\"></button></a>";        //LIGHTRED
    s += "<a href=\"/color/99991c\"><button class=\"button button3\"></button></a><br>";    //RED

    s += "<a href=\"/color/99991h\"><button class=\"button button8\"></button></a>";        //PINK
    s += "<a href=\"/color/99991d\"><button class=\"button button4\"></button></a>";        //WHITE
    
    
    s += "<a href=\"/gpio/0\"><button class=\"button button30\"></button></a>";       //OFF
    s += "</center></body></html>\n"; 
    // Send the response to the client
    client.print(s);
    return;
  }

  client.flush();

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  s += "<html><head>";
  s += "<title>Home Automation</title>";
  s += "<style>";
  s += ".button {border: none;color: white;padding: 45px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;transition-duration: 0.4s;cursor: pointer;}";
  s += ".button30:hover {background-color: white; border: 2px solid #555555;}.button30 {background-color: #555555; border: 2px solid #555555;}";  //OFF
  s += ".button1:hover {background-color: white; border: 2px solid #00ff00;}.button1 {background-color: #00ff00; border: 2px solid #00ff00;}";    //GREEN
  s += ".button2:hover {background-color: white; border: 2px solid #0000ff;}.button2 {background-color: #0000ff; border: 2px solid #0000ff;}";    //BLUE
  s += ".button3:hover {background-color: white; border: 2px solid #ff0000;}.button3 {background-color: #ff0000; border: 2px solid #ff0000;}";    //RED
  s += ".button4:hover {background-color: white; border: 2px solid #c0c0c0;}.button4 {background-color: #c0c0c0; border: 2px solid #c0c0c0;}";    //WHITE
  s += ".button5:hover {background-color: white; border: 2px solid #ffff00;}.button5 {background-color: #ffff00; border: 2px solid #ffff00;}";    //YELLOW
  s += ".button6:hover {background-color: white; border: 2px solid #ff8000;}.button6 {background-color: #ff8000; border: 2px solid #ff8000;}";    //ORANGE
  s += ".button7:hover {background-color: white; border: 2px solid #7f00ff;}.button7 {background-color: #7f00ff; border: 2px solid #7f00ff;}";    //PURPLE
  s += ".button8:hover {background-color: white; border: 2px solid #ff00ff;}.button8 {background-color: #ff00ff; border: 2px solid #ff00ff;}";    //PINK
  s += ".button9:hover {background-color: white; border: 2px solid #0080ff;}.button9 {background-color: #0080ff; border: 2px solid #0080ff;}";    //LIGHTBLUE
  s += ".button10:hover {background-color: white; border: 2px solid #00ff80;}.button10 {background-color: #00ff80; border: 2px solid #00ff80;}";    //LIGHTGREEN
  s += ".button11:hover {background-color: white; border: 2px solid #ff4040;}.button11 {background-color: #ff4040; border: 2px solid #ff4040;}";    //LIGHTRED
  s += "</style>";
  s += "</head><body><center>";
  
  s += "<a href=\"/color/99991e\"><button class=\"button button5\"></button></a>";        //YELLOW
  s += "<a href=\"/color/99991k\"><button class=\"button button10\"></button></a>";        //LIGHTGREEN
  s += "<a href=\"/color/99991a\"><button class=\"button button1\"></button></a><br>";        //GREEN

  s += "<a href=\"/color/99991g\"><button class=\"button button7\"></button></a>";        //PURPLE
  s += "<a href=\"/color/99991i\"><button class=\"button button9\"></button></a>";        //LIGHTBLUE
  s += "<a href=\"/color/99991b\"><button class=\"button button2\"></button></a><br>";        //BLUE

  s += "<a href=\"/color/99991f\"><button class=\"button button6\"></button></a>";        //ORANGE
  s += "<a href=\"/color/99991m\"><button class=\"button button11\"></button></a>";        //LIGHTRED
  s += "<a href=\"/color/99991c\"><button class=\"button button3\"></button></a><br>";    //RED

  s += "<a href=\"/color/99991h\"><button class=\"button button8\"></button></a>";        //PINK
  s += "<a href=\"/color/99991d\"><button class=\"button button4\"></button></a>";        //WHITE
  
  
  s += "<a href=\"/gpio/0\"><button class=\"button button30\"></button></a>";       //OFF
  s += "</center></body></html>\n"; 
  // Send the response to the client
  client.print(s);

  delay(1);

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
