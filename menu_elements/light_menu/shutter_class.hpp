// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.06.2012 23:55:44 CEST
// File:    shutter_class.hpp

#ifndef __SHUTTER_CLASS_HEADER
#define __SHUTTER_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

const byte treshold_up = 135;
const byte treshold_down = 105;

class shutter_class: public menu_element_class
{
public:
	shutter_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::lcdShutter));
            display();
        #endif
	}
    void leave_action()
	{
        #ifdef CORE_ATMEGA
            data->disk->write(eeprom::lcd_pot_adr, data->lcd_pot);
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    void incr1_action() 
    {
        if(data->lcd_pot != treshold_up)
            ++data->lcd_pot;
        
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->set_shutter(data->lcd_pot);
            display();
        #endif
    }
	void decr1_action()
    {
        if(data->lcd_pot != treshold_down)
            --data->lcd_pot;

        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->set_shutter(data->lcd_pot);
            display();
        #endif
    }
	void incr10_action()
    {
        if(data->lcd_pot <= treshold_up - 10)
            data->lcd_pot += 10;
        else
            data->lcd_pot = treshold_up;
            
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->set_shutter(data->lcd_pot);
            display();
        #endif
    }
	void decr10_action()
    {
        if(data->lcd_pot >= treshold_down + 10)
            data->lcd_pot -= 10;
        else
            data->lcd_pot = treshold_down;
            
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->set_shutter(data->lcd_pot);
            display();
        #endif
    }
    
    #ifdef SIDE_ATMEGA
        void display()
        {
            data->lcd->setCursor(6, 1);
            data->lcd->print(data->lcd->get_shutter());
            data->lcd->print("  ");
        }
    #endif
    
};

#endif //__SHUTTER_CLASS_HEADER
