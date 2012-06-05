// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 14:26:58 CEST
// File:    sync_data.hpp

#ifndef __SYNC_DATA_HEADER
#define __SYNC_DATA_HEADER

#include "data_struct.hpp"


inline void sync(data_struct & data, byte & msg)
{
#ifdef CORE_ATMEGA
    data.com->send(msg);
#elif defined SIDE_ATMEGA
    msg = data.com->receive();
#endif
}
inline void tier_sync(data_struct & data, byte pos, byte i)
{
#ifdef CORE_ATMEGA
    data.com->send(data.tier_name[pos][i]);
#elif defined SIDE_ATMEGA
    data.tier_name[pos][i] = data.com->receive();
#endif
}

void sync_data(data_struct & data)
{
     //------------------- profil & display pos -------------------
    sync(data, data.profil);
    sync(data, data.disp_pos);
    
    //------------------- lights -------------------
    sync(data, data.lcd_pwm);
    sync(data, data.lcd_pot);
    sync(data, data.led_high);
    sync(data, data.led_low);
    
    #ifdef CORE_ATMEGA
        data.set_led_low();
    #elif defined SIDE_ATMEGA
        data.lcd->set_brightness(data.lcd_pwm);
        data.lcd->set_shutter(data.lcd_pot);        
    #endif
    //------------------- mapping -------------------
    for(byte i = 0; i < cnst::n_prof; ++i)
    {
        sync(data, data.map[i]);
    }
    //------------------- keys -------------------
    sync(data, data.menu_key);
    
    for(byte prof = 0; prof < cnst::n_prof; ++prof)
    {
        for(byte i = 0; i < cnst::end_key; ++i)
        {
            sync(data, data.key[prof][i]);
            sync(data, data.mod[prof][i]);
        }
    }
     //------------------- names -------------------
    for(byte pos = 0; pos < cnst::n_prof; ++pos)
    {
         for(byte i = 0; i < cnst::name_length; ++i)
                tier_sync(data, pos, i);
    }
}

#endif //__SYNC_DATA_HEADER
