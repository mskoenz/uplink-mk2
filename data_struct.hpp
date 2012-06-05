// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 18:09:15 CEST
// File:    data_struct.hpp

#ifndef __DATA_STRUCT_HEADER
#define __DATA_STRUCT_HEADER

#include "com_class.hpp"
#include "menu_elements/menu_element_class.hpp"

#ifdef CORE_ATMEGA
    #include "core/key_reader_class.hpp"
    #include "core/keybuffer_class_fwd.hpp"
    #include "core/eeprom_class.hpp"
#elif defined SIDE_ATMEGA
    #include "side/display_control.hpp"
    #include "side/progmem_text.hpp"
    #include "side/progmem_keys.hpp"
    #include "side/progmem_mods.hpp"
#endif

#include "global_const.hpp"
#include <Arduino.h>

struct data_struct
{
    data_struct(): 
        #ifdef CORE_ATMEGA
                profil_pin(6)
              , in_menu(false)
              , com(new com_class(1, 3))
              , disk(new eeprom_class())
              , button(new key_reader_class())
              , buffer(new keybuffer_class(this))
        #elif defined SIDE_ATMEGA
                in_menu(false)
              , com(new com_class(9, 0))
              , lcd(new display_class(5,7,3,2,4,8,6))
        #endif
            {
                for(byte i = 0; i < cnst::n_prof; ++i)
                {
                    for(byte j = 0; j < cnst::name_length; ++j)
                    {
                        tier_name[i][j] = 0;
                    }
                    
                }
                
            }
    
    /// +---------------------------------------------------+
    /// |                   variables                       |
    /// +---------------------------------------------------+
    //------------------- profil -------------------
    byte profil;
    
    #ifdef CORE_ATMEGA
        byte profil_pin;
    #endif
    char tier_name[cnst::n_prof][cnst::name_length];
    
    byte disp_pos;
    
    //------------------- lights -------------------
    byte lcd_pwm;
    byte lcd_pot;
    byte led_high;
    byte led_low;
    
    //------------------- map colors to disk -------------------
    byte map[cnst::n_prof];
    inline byte small_prof(byte prof)
    {
        return prof/cnst::n_tier;
    }
    inline byte small_prof()
    {
        return small_prof(profil);
    }
    inline byte pin_to_profil(byte prof)
    {
        if(small_prof(prof) == 0)
            return 10;
        if(small_prof(prof) == 1)
            return 9;
        if(small_prof(prof) == 2)
            return 6;
        return 0;
    }
    inline byte pin_to_profil()
    {
        return pin_to_profil(profil);
    }
    //------------------- keys -------------------
    byte key[cnst::n_prof][cnst::end_key];
    byte mod[cnst::n_prof][cnst::end_key];
    byte menu_key;
    
    
    //------------------- menu -------------------
    bool in_menu;
    /// +---------------------------------------------------+
    /// |                   functions                       |
    /// +---------------------------------------------------+
    //------------------- profil -------------------
    inline void change_tier(byte sub_chg)
    {
        byte sub_now = profil%cnst::n_tier;
        if(sub_chg != sub_now)
            profil = profil - sub_now + sub_chg;
    }
    //------------------- prof changes -------------------
    inline byte next_profil(byte prof)
    {
        return (prof + cnst::n_tier) % cnst::n_prof;
    }
    inline byte prev_profil(byte prof)
    {
        return (prof + 2*cnst::n_tier) % cnst::n_prof;
    }
    inline byte next_profil()
    {
        return next_profil(profil);
    }
    inline byte prev_profil()
    {
        return prev_profil(profil);
    }
    //------------------- tier changes -------------------
    inline byte next_tier(byte tier)
    {
        return (tier + 1) % cnst::n_prof;
    }
    inline byte prev_tier(byte tier)
    {
        return (tier + cnst::n_prof - 1) % cnst::n_prof;
    }
    inline byte next_tier()
    {
        return next_tier(profil);
    }
    inline byte prev_tier()
    {
        return prev_tier(profil);
    }
    
    
    //------------------- lights -------------------
    #ifdef CORE_ATMEGA
        
    inline void set_led_high()
	{
		analogWrite(profil_pin, led_high);
	}
	inline void set_led_low()
	{
		analogWrite(profil_pin, led_low);
	}
	inline void set_led_zero()
	{
		digitalWrite(profil_pin, LOW);
	}
	
	inline void blink(long int const & clock, const byte buffer)
	{
		if(buffer == 0 and clock > cnst::delayLed)
			analogWrite(profil_pin, led_low);
		else
			if(clock & 2)
				analogWrite(profil_pin, led_low);
			else
				analogWrite(profil_pin, led_high);
		//it seems as if the led is high all the time during the keyDelay but it's just the loop
		//frequency that goes up enormous bc usbSendKeyStrokes isn't called during keyDelay
	}
    #endif
    
    //------------------- map colors to disk -------------------
    
    //------------------- keys -------------------
    inline byte get_key(byte pos) {return key[map[profil]][pos];}
    inline byte get_mod(byte pos) {return mod[map[profil]][pos];}
    
    inline void set_key(byte pos, byte key_in) {key[map[profil]][pos] = key_in;}
    inline void set_mod(byte pos, byte mod_in) {mod[map[profil]][pos] = mod_in;}
    
    #ifdef CORE_ATMEGA
        inline void write_key(byte pos, byte key_in) 
        {
            key[map[profil]][pos] = key_in;
            disk->write_key(map[profil], pos, key_in);
        }
        inline void write_mod(byte pos, byte mod_in) 
        {
            mod[map[profil]][pos] = mod_in;
            disk->write_mod(map[profil], pos, mod_in);
        }
    #endif
    
    
    com_class * com;

    #ifdef CORE_ATMEGA
        eeprom_class * disk;
        key_reader_class * button;
        keybuffer_class * buffer;
    #elif defined SIDE_ATMEGA
        display_class * lcd;
    #endif
};


#endif //__DATA_STRUCT_HEADER
