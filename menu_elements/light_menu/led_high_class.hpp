// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.06.2012 23:55:25 CEST
// File:    led_high_class.hpp

#ifndef __LED_HIGH_CLASS_HEADER
#define __LED_HIGH_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class led_high_class: public menu_element_class
{
public:
	led_high_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::ledHigh));
            display();
        #endif
	}
    void leave_action()
	{
        #ifdef CORE_ATMEGA
            data->disk->write(eeprom::led_high_adr, data->led_high);
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    void incr1_action() 
    {
        if(data->led_high != 200)
            ++data->led_high;
        #ifdef CORE_ATMEGA

        #elif defined SIDE_ATMEGA
            display();
        #endif
    }
	void decr1_action()
    {
        if(data->led_high != 0)
            --data->led_high;
        #ifdef CORE_ATMEGA

        #elif defined SIDE_ATMEGA
            display();
        #endif
    }
	void incr10_action()
    {
        if(data->led_high <= 190)
            data->led_high += 10;
        else
            data->led_high = 200;
        
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA

            display();
        #endif
    }
	void decr10_action()
    {
        if(data->led_high >= 10)
            data->led_high -= 10;
        else
            data->led_high = 0;
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA

            display();
        #endif
    }
    
    #ifdef SIDE_ATMEGA
        void display()
        {
            data->lcd->setCursor(6, 1);
            data->lcd->print(data->led_high);
            data->lcd->print("  ");
        }
    #endif
    
};

#endif //__LED_HIGH_CLASS_HEADER
