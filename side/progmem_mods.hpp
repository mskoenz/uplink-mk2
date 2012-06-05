// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 22:45:32 CEST
// File:    progmem_mods.hpp

#ifndef __PROGMEM_MODS_HEADER
#define __PROGMEM_MODS_HEADER

#ifdef CORE_ATMEGA
    fail   //make sure that this file isn't included by core.cpp
#endif

//all the string are stored in programm memory in order not to consume the 2kB SRAM

#include "../global_const.hpp"

#include <avr/pgmspace.h>

namespace mods
{
    //~ char m0[]  = "      ";
    //~ char m1[]  = "      ";
    //~ char m2[]  = "      ";
    //~ char m3[]  = "      ";
    //~ char m4[]  = "      ";
    //~ char m5[]  = "      ";
    //~ char m6[]  = "      ";
    //~ char m7[]  = "      ";
    //~ char m8[]  = "      ";
    //~ char m9[]  = "      ";
    //~ char m10[]  = "      ";
    //~ char m11[]  = "      ";
    //~ char m12[]  = "      ";
    //~ char m13[]  = "      ";
    //~ char m14[]  = "      ";
    //~ char m15[]  = "      ";

    prog_char m00[] PROGMEM = {' ', ' ', ' ', ' ', ' ', ' ', 0};
    prog_char m01[] PROGMEM = {' ', ' ', mods::ctrl, ' ', ' ', ' ', 0};
    prog_char m02[] PROGMEM = {' ', ' ', mods::shift, ' ', ' ', ' ', 0};
    prog_char m03[] PROGMEM = {' ', mods::shift, ' ', mods::ctrl, ' ', ' ', 0};
    prog_char m04[] PROGMEM = {' ', ' ', mods::alt, ' ', ' ', ' ', 0};
    prog_char m05[] PROGMEM = {' ', mods::alt, ' ', mods::ctrl, ' ', ' ', 0};
    prog_char m06[] PROGMEM = {' ', mods::alt, ' ', mods::shift, ' ', ' ', 0};
    prog_char m07[] PROGMEM = {mods::alt, ' ', mods::shift, ' ', mods::ctrl, ' ', 0};
    prog_char m08[] PROGMEM = {' ', ' ', mods::gui, ' ', ' ', ' ', 0};
    prog_char m09[] PROGMEM = {' ', mods::gui, ' ', mods::ctrl, ' ', ' ', 0};
    prog_char m10[] PROGMEM = {' ', mods::gui, ' ', mods::shift, ' ', ' ', 0};
    prog_char m11[] PROGMEM = {mods::gui, ' ', mods::shift, ' ', mods::ctrl, ' ', 0};
    prog_char m12[] PROGMEM = {' ', mods::gui, ' ', mods::alt, ' ', ' ', 0};
    prog_char m13[] PROGMEM = {mods::gui, ' ', mods::alt, ' ', mods::ctrl, ' ', 0};
    prog_char m14[] PROGMEM = {mods::gui, ' ', mods::alt, ' ', mods::shift, ' ', 0};
    prog_char m15[] PROGMEM = {' ', mods::gui, mods::alt, mods::shift, mods::ctrl, ' ', 0};
    
    const char *strTb[] PROGMEM = {
          m00, m01, m02, m03, m04, m05, m06, m07, m08, m09
        , m10, m11, m12, m13, m14, m15
        };
     
    char buffer[16];
    char * get(byte i)
    {
        strcpy_P(buffer, (char*)pgm_read_word(&strTb[i]));
        return buffer;
    }
}

#endif //__PROGMEM_MODS_HEADER
