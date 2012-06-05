// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 01:05:16 CEST
// File:    dark_class.hpp

#ifndef __DARK_CLASS_HEADER
#define __DARK_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class dark_class: public menu_element_class
{
public:
	dark_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::dispDark));
        #endif
	}
    void leave_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    void enter_here()
    {
        #ifdef SIDE_ATMEGA
            data->lcd->set_brightness(data->lcd_pwm);
        #endif
    }
    
    menu_element_class * leave_here()
    {
        #ifdef CORE_ATMEGA
            data->disk->write(eeprom::disp_pos_adr, disp::dark);
        #elif defined SIDE_ATMEGA
            data->lcd->set_brightness(0);
            data->lcd->print(text::get(text::dispDarkText));
        #endif
        
        return this;
    }
};

#endif //__DARK_CLASS_HEADER
