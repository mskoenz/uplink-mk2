// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 17:50:47 CEST
// File:    read_eeprom.hpp

#ifndef __READ_EEPROM_HEADER
#define __READ_EEPROM_HEADER

#ifdef SIDE_ATMEGA
    fail   //make sure that this file isn't included by core.cpp
#endif

#include "../data_struct.hpp"
#include "eeprom_class.hpp"
#include "../global_const.hpp"

namespace eeprom
{
    void read(data_struct & data)
    {
        //------------------- init led -------------------
        pinMode(6, OUTPUT);
        pinMode(9, OUTPUT);
        pinMode(10, OUTPUT);
        //------------------- profil & display pos -------------------
        data.profil = data.disk->read(profil_adr);
        
        data.profil_pin = data.pin_to_profil();
        
        data.disp_pos = data.disk->read(disp_pos_adr);
        
        //------------------- lights -------------------
        data.lcd_pwm = data.disk->read(lcd_pwm_adr);
        data.lcd_pot = data.disk->read(lcd_pot_adr);
        data.led_high = data.disk->read(led_high_adr);
        data.led_low = data.disk->read(led_low_adr);
        
        //------------------- mapping -------------------
        for(byte i = 0; i < cnst::n_prof; ++i)
        {
            data.map[i] = data.disk->read(map_start_adr + i);
        }
        //------------------- keys -------------------
        data.menu_key = data.disk->read(menu_key_adr);
        for(byte prof = 0; prof < cnst::n_prof; ++prof)
        {
            for(byte i = 0; i < cnst::end_key; ++i)
            {
                data.key[prof][i] = data.disk->read_key(prof, i);
                data.mod[prof][i] = data.disk->read_mod(prof, i);
            }
        }
        //------------------- names -------------------
       for(byte pos = 0; pos < cnst::n_prof; ++pos)
        {
             for(byte i = 0; i < cnst::name_length; ++i)
                    data.tier_name[pos][i] = data.disk->read(eeprom::name_start_adr + pos * cnst::name_length + i);
        }
        
    }
}

#endif //__READ_EEPROM_HEADER
