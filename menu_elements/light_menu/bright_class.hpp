// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    01.06.2012 17:04:48 CEST
// File:    bright_class.hpp

#ifndef __BRIGHT_CLASS_HEADER
#define __BRIGHT_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class bright_class: public menu_element_class
{
public:
	bright_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::lcdBright));
            display();
        #endif
	}
    void leave_action()
	{
        #ifdef CORE_ATMEGA
            data->disk->write(eeprom::lcd_pwm_adr, data->lcd_pwm);
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    void incr1_action() 
    {
        if(data->lcd_pwm != 200)
            ++data->lcd_pwm;
        #ifdef CORE_ATMEGA

        #elif defined SIDE_ATMEGA
            data->lcd->set_brightness(data->lcd_pwm);
            display();
        #endif
    }
	void decr1_action()
    {
        if(data->lcd_pwm != 0)
            --data->lcd_pwm;
        #ifdef CORE_ATMEGA

        #elif defined SIDE_ATMEGA
            data->lcd->set_brightness(data->lcd_pwm);
            display();
        #endif
    }
	void incr10_action()
    {
        if(data->lcd_pwm <= 190)
            data->lcd_pwm += 10;
        else
            data->lcd_pwm = 200;
        
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->set_brightness(data->lcd_pwm);
            display();
        #endif
    }
	void decr10_action()
    {
        if(data->lcd_pwm >= 10)
            data->lcd_pwm -= 10;
        else
            data->lcd_pwm = 0;
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->set_brightness(data->lcd_pwm);
            display();
        #endif
    }
    
    #ifdef SIDE_ATMEGA
        void display()
        {
            data->lcd->setCursor(6, 1);
            data->lcd->print(data->lcd->get_brightness());
            data->lcd->print("  ");
        }
    #endif
    
};

#endif //__BRIGHT_CLASS_HEADER
