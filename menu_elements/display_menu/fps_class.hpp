// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 13:25:36 CEST
// File:    fps_class.hpp

#ifndef __FPS_CLASS_HEADER
#define __FPS_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class fps_class: public menu_element_class
{
public:
	fps_class(data_struct & data): menu_element_class(data) , start(0), end(0), count(0) {}
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::dispFps));
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
            data->disk->write(eeprom::disp_pos_adr, disp::fps);
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::dispFps_2));
        #endif
        return this;
    }
    
    
    #ifdef SIDE_ATMEGA
        void idle_action()
        {
            if(count > 2)
            {
                data->lcd->setCursor(5, 1);
                end = millis();
                data->lcd->print(20000/(end - start));
                data->lcd->print("    ");
                start = end;
                count = 0;
            }
            else
                ++count;
        }
    #endif
    private:
        luint start;
        luint end;
        int count;
};

#endif //__FPS_CLASS_HEADER
