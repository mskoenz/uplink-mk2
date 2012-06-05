// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 01:05:16 CEST
// File:    Key_class.hpp

#ifndef __KEY_CLASS_HEADER
#define __KEY_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class key_class: public menu_element_class
{
public:
	key_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::dispKey));
        #endif
	}
    void leave_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    
    menu_element_class * leave_here()
    {
        #ifdef CORE_ATMEGA
            data->disk->write(eeprom::disp_pos_adr, disp::key);
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::keyPressed));
            data->lcd->setCursor(10, 0);
            data->lcd->print(data->tier_name[data->profil]);
        #endif
        
        
        return this;
    }
    void key_action()
    {
        #ifdef CORE_ATMEGA
            data->com->send((*data->buffer)[1]);
            data->com->send((*data->buffer)[0]);
        #elif defined SIDE_ATMEGA
            byte key = data->com->receive();
            byte mod = data->com->receive();
            
            if(!data->in_menu)
            {
                data->lcd->setCursor(10, 0);
                data->lcd->print(data->tier_name[data->profil]);                
            }
            
            data->lcd->setCursor(2, 1);
            data->lcd->print(mods::get(mod));
            data->lcd->setCursor(9, 1);
            data->lcd->print(keys::get(key));
        #endif
    }
};

#endif //__KEY_CLASS_HEADER
