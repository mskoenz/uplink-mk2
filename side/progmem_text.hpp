// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 22:19:25 CEST
// File:    progmem_text.hpp

#ifndef __PROGMEM_TEXT_HEADER
#define __PROGMEM_TEXT_HEADER

#ifdef CORE_ATMEGA
    fail   //make sure that this file isn't included by core.cpp
#endif

//all the string are stored in programm memory in order not to consume the 2kB SRAM

#include <avr/pgmspace.h>

namespace text
{
    char buffer[16];

    prog_char n01[] PROGMEM = "  U P L I N K   ";
    prog_char n02[] PROGMEM = "   M K   I V    ";
    prog_char n03[] PROGMEM = " switch profil  ";
    prog_char n04[] PROGMEM = "   swap done    ";
    prog_char n05[] PROGMEM = "  <-- <--> -->  ";
    prog_char n06[] PROGMEM = "  swap profil   ";
    prog_char n07[] PROGMEM = " red           ";
    prog_char n08[] PROGMEM = "blue            ";
    prog_char n09[] PROGMEM = "green           ";
    prog_char n10[] PROGMEM = "   swap keys    ";
    prog_char n11[] PROGMEM = "   first key    ";
    prog_char n12[] PROGMEM = "   second key   ";
    prog_char n13[] PROGMEM = " choose         ";
    prog_char n14[] PROGMEM = "  key selected  ";
    prog_char n15[] PROGMEM = "   target key   ";
    prog_char n16[] PROGMEM = "    set keys    ";
    prog_char n17[] PROGMEM = "  lcd shutter   ";
    prog_char n18[] PROGMEM = "    led high    ";
    prog_char n19[] PROGMEM = "    led low     ";
    prog_char n20[] PROGMEM = "  display time  ";
    prog_char n21[] PROGMEM = "  time running  ";
    prog_char n22[] PROGMEM = "  display key   ";
    prog_char n23[] PROGMEM = " keystate       ";
    prog_char n24[] PROGMEM = "  display dark  ";
    prog_char n25[] PROGMEM = "  can't see me  ";
    prog_char n26[] PROGMEM = " lcd brightness ";
    prog_char n27[] PROGMEM = "   light menu   ";
    prog_char n28[] PROGMEM = "  display menu  ";
    prog_char n29[] PROGMEM = "    main menu   ";
    prog_char n30[] PROGMEM = "   profil menu  ";
    prog_char n31[] PROGMEM = "    key menu    ";
    prog_char n32[] PROGMEM = "  set to        ";
    prog_char n33[] PROGMEM = "                ";
    prog_char n34[] PROGMEM = "  set menu key  ";
    prog_char n35[] PROGMEM = "   swap tiers   ";
    prog_char n36[] PROGMEM = "  rename tiers  ";
    prog_char n37[] PROGMEM = "   edit name    ";
    prog_char n38[] PROGMEM = "   rename to    ";
    prog_char n39[] PROGMEM = "  display APM   ";
    prog_char n40[] PROGMEM = " APM per        ";

    PROGMEM const char *strTb[] = {
          n01
        , n02
        , n03
        , n04
        , n05
        , n06
        , n07
        , n08
        , n09
        , n10
        , n11
        , n12
        , n13
        , n14
        , n15
        , n16
        , n17
        , n18
        , n19
        , n20
        , n21
        , n22
        , n23
        , n24
        , n25
        , n26
        , n27
        , n28
        , n29
        , n30
        , n31
        , n32
        , n33
        , n34
        , n35
        , n36
        , n37
        , n38
        , n39
        , n40
    };

    char * get(byte i)
    {
    strcpy_P(buffer, (char*)pgm_read_word(&strTb[i]));
    
    if(i == red or i == blue or i == green)
        buffer[5] = 0;
    
    return buffer;
    }
}

#endif //__PROGMEM_TEXT_HEADER
