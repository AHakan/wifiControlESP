#include "website.h"

extern const char html[];

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        4
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 25

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "ASUS"
#define STAPSK  "busenihicilgilendirmez."
#endif

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

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(staticIP, subnet, gateway);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Set the certificates from PMEM (if using DRAM remove the _P from the call)
  server.setServerKeyAndCert_P(rsakey, sizeof(rsakey), x509, sizeof(x509));

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());


  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
}

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
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }
  } else if (req.indexOf("/gpio/1") != -1) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }
  } else if (req.indexOf("/gpio/2") != -1) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }
  } else if (req.indexOf("/gpio/3") != -1) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }
  } else if (req.indexOf("/gpio/4") != -1) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }
  } else if (req.indexOf("/gpio/5") != -1) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 0, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }

  } else if (req.indexOf("/gpio/6") != -1) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 193, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }

  } else {
    
    /*String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
    s += "<html><head>";
    s += "<title>Home Automation</title>";
    s += "<style>";
    s += ".button {background-color: #4CAF50; border: none;color: white;padding: 16px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;transition-duration: 0.4s;cursor: pointer;}";
    s += ".button1:hover {background-color: white; color: black; border: 2px solid #4CAF50; }.button1 {background-color: #4CAF50;color: white;border: 2px solid #4CAF50;padding-left: 80px; padding-right: 80px;}";
    s += ".button2:hover {background-color: white; color: black; border: 2px solid #008CBA;}.button2{background-color: #008CBA;color: white;border: 2px solid #008CBA; padding-left: 86px; padding-right: 86px; }";
    s += ".button3:hover {background-color: white; color: black; border: 2px solid #f44336;}.button3 {background-color: #f44336;color: white;border: 2px solid #f44336;padding-left: 88px; padding-right: 87px;}";
    s += ".button4:hover {background-color: white;color: black;border: 2px solid #e7e7e7;}.button4 {background-color: #e7e7e7; color: black; border: 2px solid #e7e7e7;padding-left: 81px; padding-right: 81px;}";
    s += ".button5:hover {background-color: white;color: black;border: 2px solid #555555;}.button5 {background-color: #555555;color: white;border: 2px solid #555555;padding-left: 90px; padding-right: 90px;}";
    s += ".button6:hover {background-color: white;color: black;border: 2px solid #cc66ff;}.button6 {background-color: #cc66ff; color: white; border: 2px solid #cc66ff;padding-left: 79px; padding-right: 79px;}";
    s += ".button7:hover {background-color: white;color: black;border: 2px solid #ffc100;}.button7 {background-color: #ffc100; color: white; border: 2px solid #ffc100;padding-left: 79px; padding-right: 79px;}";
    s += "</style>";
    s += "</head><body><center>";
    s += "<p><a href=\"/gpio/1\"><button class=\"button button1\">Green</button></a></p>";
    s += "<p><a href=\"/gpio/2\"><button class=\"button button2\">Blue</button></a></p>";
    s += "<p><a href=\"/gpio/3\"><button class=\"button button3\">Red</button></a></p>";
    s += "<p><a href=\"/gpio/4\"><button class=\"button button4\">White</button></a></p>";
    s += "<p><a href=\"/gpio/5\"><button class=\"button button6\">Purple</button></a></p>";
    s += "<p><a href=\"/gpio/6\"><button class=\"button button7\">Yellow</button></a></p>";
    s += "<p><a href=\"/gpio/0\"><button class=\"button button5\">Off</button></a></p>";
    s += "</center></body></html>\n"; */
    client.print(html);
    
    return;
  }

  client.flush();
  
  /*String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  s += "<html><head>";
  s += "<title>Home Automation</title>";
  s += "<style>";
  s += ".button {background-color: #4CAF50; border: none;color: white;padding: 16px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;transition-duration: 0.4s;cursor: pointer;}";
  s += ".button1:hover {background-color: white; color: black; border: 2px solid #4CAF50; }.button1 {background-color: #4CAF50;color: white;border: 2px solid #4CAF50;padding-left: 80px; padding-right: 80px;}";
  s += ".button2:hover {background-color: white; color: black; border: 2px solid #008CBA;}.button2{background-color: #008CBA;color: white;border: 2px solid #008CBA; padding-left: 86px; padding-right: 86px; }";
  s += ".button3:hover {background-color: white; color: black; border: 2px solid #f44336;}.button3 {background-color: #f44336;color: white;border: 2px solid #f44336;padding-left: 88px; padding-right: 87px;}";
  s += ".button4:hover {background-color: white;color: black;border: 2px solid #e7e7e7;}.button4 {background-color: #e7e7e7; color: black; border: 2px solid #e7e7e7;padding-left: 81px; padding-right: 81px;}";
  s += ".button5:hover {background-color: white;color: black;border: 2px solid #555555;}.button5 {background-color: #555555;color: white;border: 2px solid #555555;padding-left: 90px; padding-right: 90px;}";
  s += ".button6:hover {background-color: white;color: black;border: 2px solid #cc66ff;}.button6 {background-color: #cc66ff; color: white; border: 2px solid #cc66ff;padding-left: 79px; padding-right: 79px;}";
  s += ".button7:hover {background-color: white;color: black;border: 2px solid #ffc100;}.button7 {background-color: #ffc100; color: white; border: 2px solid #ffc100;padding-left: 79px; padding-right: 79px;}";
  s += "</style>";
  s += "</head><body><center>";
  s += "<p><a href=\"/gpio/1\"><button class=\"button button1\">Green</button></a></p>";
  s += "<p><a href=\"/gpio/2\"><button class=\"button button2\">Blue</button></a></p>";
  s += "<p><a href=\"/gpio/3\"><button class=\"button button3\">Red</button></a></p>";
  s += "<p><a href=\"/gpio/4\"><button class=\"button button4\">White</button></a></p>";
  s += "<p><a href=\"/gpio/5\"><button class=\"button button6\">Purple</button></a></p>";
  s += "<p><a href=\"/gpio/6\"><button class=\"button button7\">Yellow</button></a></p>";
  s += "<p><a href=\"/gpio/0\"><button class=\"button button5\">Off</button></a></p>";
  s += "</center></body></html>\n";*/
  // Send the response to the client
  client.print(html);
  delay(1);

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
