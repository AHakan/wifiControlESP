/*
 * 
 * @author = ahmethakan@pm.me
 * 
*/
//---------------------- Includes ----------------------//
#include "NeoBlink.h"
#include "Arduino.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


//---------------------- Defines ----------------------//
#define PIN           2
#define NUMPIXELS     16
#define DELAYVAL      25

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



neoclass::neoclass(){
 
}


//---------------------- Setup ----------------------//
void neoclass::SETUP(){
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pixels.begin();
}


//---------------------- Off ----------------------//
void neoclass::OFF(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();  
    delay(DELAYVAL); 
  }
}


//---------------------- Green ----------------------// rapid awakening
void neoclass::GREEN(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();  
    delay(DELAYVAL); 
  }
}


//---------------------- Blue ----------------------// rapid awakening
void neoclass::BLUE(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Red ----------------------// rapid awakening
void neoclass::RED(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- White ----------------------// rapid awakening
void neoclass::WHITE(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Yellow ----------------------// rapid awakening
void neoclass::YELLOW(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Orange ----------------------// rapid awakening
void neoclass::ORANGE(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 128, 0));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Purple ----------------------// rapid awakening
void neoclass::PURPLE(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(127, 0, 255));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Pink ----------------------// rapid awakening
void neoclass::PINK(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 255));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Lightblue ----------------------// rapid awakening
void neoclass::LIGHTBLUE(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 128, 255));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Lightgreen ----------------------// rapid awakening
void neoclass::LIGHTGREEN(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 128));
    pixels.show();  
    delay(DELAYVAL);
  }
}


//---------------------- Lightred ----------------------// rapid awakening
void neoclass::LIGHTRED(){
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 64, 64));
    pixels.show();  
    delay(DELAYVAL);
  }
}
  

neoclass NeoBlink = neoclass();
