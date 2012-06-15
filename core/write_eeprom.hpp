// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 14:39:42 CEST
// File:    write_eeprom.hpp

#ifndef __WRITE_EEPROM_HEADER
#define __WRITE_EEPROM_HEADER

#ifdef SIDE_ATMEGA
    fail   //make sure that this file isn't included by core.cpp
#endif

#include "../data_struct.hpp"
#include "eeprom_class.hpp"
#include "../global_const.hpp"

namespace eeprom
{
    void write(data_struct & data)
    {
        //------------------- profil & display pos -------------------
        //~ data.disk->write(profil_adr, 0);
        //~ data.disk->write(disp_pos_adr, 0);
        //~ 
        //~ //------------------- lights -------------------
        //~ data.disk->write(lcd_pwm_adr, 120);
        //~ data.disk->write(lcd_pot_adr, 115);
        //~ data.disk->write(led_high_adr, 30);
        //~ data.disk->write(led_low_adr, 1);
        //~ 
        //~ //------------------- mapping -------------------
        //~ for(byte i = 0; i < cnst::n_prof; ++i)
        //~ {
            //~ data.disk->write(map_start_adr + i, i);
        //~ }
        //~ //------------------- keys -------------------
        //~ data.disk->write(menu_key_adr, 19);
        //~ for(byte prof = 0; prof < cnst::n_prof; ++prof)
        //~ {
            //~ for(byte i = 0; i < cnst::end_key; ++i)
            //~ {
                //~ data.disk->write_key(prof, i, prof + 4);
                //~ data.disk->write_mod(prof, i, 0);
            //~ }
        //~ }
        //------------------- names -------------------
        byte name[] = "tier a";
        for(byte pos = 0; pos < cnst::n_prof; ++pos)
        {
             for(byte i = 0; i < cnst::name_length; ++i)
                    data.disk->write(eeprom::name_start_adr + pos * cnst::name_length + i, name[i]);
            ++name[5];
        }
        
    }
}

#endif //__WRITE_EEPROM_HEADER
