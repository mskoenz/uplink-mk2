// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 00:29:24 CEST
// File:    time_class.hpp

#ifndef __TIME_CLASS_HEADER
#define __TIME_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class time_class: public menu_element_class
{
public:
	time_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::dispTime));
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
            data->disk->write(eeprom::disp_pos_adr, disp::time);
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::timeRun));
        #endif
        return this;
    }
    
    
    #ifdef SIDE_ATMEGA
        void idle_action()
        {
            long int time = millis()/1000;
            short sec = time % 60;
            short min = (time / 60) % 60;
            short h = time / 3600;
            
            data->lcd->setCursor(4, 1);

            if(h != 0)
            {
                data->lcd->print(h);
                data->lcd->print(":");
            }
            else
                data->lcd->print(" ");
            
            if(min >= 0 and min < 10)
            {
                if(h > 0)
                    data->lcd->print("0");
                else
                    data->lcd->print(" ");
            }
            if(min != 0)
            {
                data->lcd->print(min);
                data->lcd->print(":");
            }
            else
                data->lcd->print(" ");
            
            if(sec >= 0 and sec < 10)
            {
                if(min > 0 or h > 0)
                    data->lcd->print("0");
                else
                    data->lcd->print(" ");
            }
            data->lcd->print(sec);
        }
    #endif
};

#endif //__TIME_CLASS_HEADER
