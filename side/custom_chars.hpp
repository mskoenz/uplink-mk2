// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 18:22:36 CEST
// File:    custom_chars.hpp

#ifndef __CUSTOM_CHARS_HEADER
#define __CUSTOM_CHARS_HEADER

#ifdef CORE_ATMEGA
    fail   //make sure that this file isn't included by core.cpp
#endif

#include <Arduino.h>

namespace custom
{
    byte up[8] = {
      0b00000
    , 0b00100
    , 0b01110
    , 0b10101
    , 0b00100
    , 0b00100
    , 0b00100
    , 0b00000
    };
    byte down[8] = {
      0b00000
    , 0b00100
    , 0b00100
    , 0b00100
    , 0b10101
    , 0b01110
    , 0b00100
    , 0b00000
    };
    byte on[8] = {
      0b00000
    , 0b00100
    , 0b00100
    , 0b10101
    , 0b10101
    , 0b10001
    , 0b01110
    , 0b00000
    };

    byte shift[8] = {
      0b00100
    , 0b01010
    , 0b10001
    , 0b11011
    , 0b01010
    , 0b01010
    , 0b01110
    , 0b00000
    };

    byte gui[8] = {
      0b00000
    , 0b00000
    , 0b10001
    , 0b01110
    , 0b01010
    , 0b01110
    , 0b10001
    , 0b00000
    };
    byte alt_custom[8] = {
      0b00000
    , 0b00000
    , 0b00000
    , 0b11011
    , 0b00100
    , 0b00011
    , 0b00000
    , 0b00000
    };
    byte ctrl[8] = {
      0b00000
    , 0b00000
    , 0b00100
    , 0b01010
    , 0b10001
    , 0b00000
    , 0b00000
    , 0b00000
    };
}
#endif //__CUSTOM_CHARS_HEADER
