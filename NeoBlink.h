/*
 * 
 * @author = ahmethakan@pm.me
 * 
*/
#ifndef NeoBlink_h
#define NeoBlink_h


//---------------------- Includes ----------------------//
#include "Arduino.h"


//----------------------- Class -----------------------//
class neoclass
{
  public:
    neoclass();
    void SETUP();
    void OFF();
    void GREEN();
    void BLUE();
    void RED();
    void WHITE();
    void YELLOW();
    void ORANGE();
    void PURPLE();
    void PINK();
    void LIGHTBLUE();
    void LIGHTGREEN();
    void LIGHTRED();
};

extern neoclass NeoBlink;

#endif
