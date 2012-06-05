// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 10:02:01 CEST
// File:    eeprom_class.hpp

#ifndef __EEPROM_CLASS_HEADER
#define __EEPROM_CLASS_HEADER

#include "EEPROM.h"
#include <Arduino.h>

#ifdef SIDE_ATMEGA
    fail   //make sure that this file isn't included by side.cpp
#endif

namespace eeprom
{
    enum loc
    {
          profil_adr = 0
        , disp_pos_adr
        , led_high_adr
        , led_low_adr
        , lcd_pwm_adr
        , lcd_pot_adr
        , menu_key_adr
        , map_start_adr = 10
        , name_start_adr = 20
        , prof_start_adr = 200
    };
}

class eeprom_class
{
public:
    //------------------- normal read/write -------------------
    inline void write(unsigned short adr, byte data)
    {
        if(EEPROM.read(adr) != data)
            EEPROM.write(adr, data);
    }
    inline byte read(unsigned short adr)
    {
        return EEPROM.read(adr);
    }
    //------------------- prof/key read/write -------------------
    inline void write_key(byte prof, byte pos, byte data)
    {
        write(eeprom::prof_start_adr + 50 * prof + pos, data);
    }
    inline void write_mod(byte prof, byte pos, byte data)
    {
        write(eeprom::prof_start_adr + 50 * prof + cnst::end_key + pos, data);
    }
    
    inline byte read_key(byte prof, byte pos)
    {
        return EEPROM.read(eeprom::prof_start_adr + 50 * prof + pos);
    }
    inline byte read_mod(byte prof, byte pos)
    {
        return EEPROM.read(eeprom::prof_start_adr + 50 * prof + cnst::end_key + pos);
    }
    //------------------- erase -------------------
    inline void erase()
    {
        for(int i = 0; i < 1024; ++i)
        {
            write(i, 0);
        }        
    }
};


#endif //__EEPROM_CLASS_HEADER
