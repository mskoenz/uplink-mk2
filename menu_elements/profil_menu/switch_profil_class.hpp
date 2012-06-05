// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 14:07:53 CEST
// File:    switch_profil_class.hpp

#ifndef __SWITCH_PROFIL_CLASS_HEADER
#define __SWITCH_PROFIL_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class switch_prof_class: public menu_element_class
{
public:
	switch_prof_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        data->change_tier(0);
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::switchProf));
            print();
        #endif
	}
    void leave_action()
	{
        data->change_tier(0);
        #ifdef CORE_ATMEGA
            data->disk->write(eeprom::profil_adr, data->profil);
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    
    void incr1_action()
    {
        #ifdef CORE_ATMEGA
            data->set_led_zero();
        #endif
        
        data->profil = data->next_profil();
        
        #ifdef CORE_ATMEGA
            data->profil_pin = data->pin_to_profil();
            data->set_led_low();
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    
    void decr1_action()
    {
        #ifdef CORE_ATMEGA
            data->set_led_zero();
        #endif
        
        data->profil = data->prev_profil();
        
        #ifdef CORE_ATMEGA
            data->profil_pin = data->pin_to_profil();
            data->set_led_low();
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    
    #ifdef SIDE_ATMEGA
        inline void print()
        {
            data->lcd->setCursor(5, 1);
            data->lcd->print(text::get(text::red + data->small_prof()));
        }
    #endif
};



#endif //__SWITCH_PROFIL_CLASS_HEADER
