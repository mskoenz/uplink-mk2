// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.06.2012 16:38:12 CEST
// File:    apm_class.hpp

#ifndef __APM_CLASS_HEADER
#define __APM_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"
#include <bit_vector_class.hpp>

class apm_class: public menu_element_class
{
public:
	apm_class(data_struct & data): menu_element_class(data) 
    {
        #ifdef SIDE_ATMEGA
        for(byte i = 0; i < cnst::t_steps_1; ++i)
        {
            hit_1[i] = 0;
        }
        for(byte i = 0; i < cnst::t_steps_2; ++i)
        {
            hit_2[i] = 0;
        }
        #endif
    }
	//------------------- enter -------------------
	void enter_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::dispAPM));
            for(byte i = 0; i < cnst::t_steps_1; ++i)
            {
                hit_1[i] = 0;
            }
            for(byte i = 0; i < cnst::t_steps_2; ++i)
            {
                hit_2[i] = 0;
            }
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
            data->disk->write(eeprom::disp_pos_adr, disp::apm);
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::dispAPMrun));
            
            data->lcd->setCursor(9, 0);
            data->lcd->print(short(cnst::t_steps_1));
            data->lcd->print("s/");
            data->lcd->print(short(cnst::t_steps_2));
            data->lcd->print("s");
        #endif
        
        
        return this;
    }
    void key_action()
    {
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            hit_1[position_1] += 1;
            hit_2[position_2] += 1;
        #endif
    }
    #ifdef SIDE_ATMEGA
        void idle_action()
        {
            position_1 = short(millis()/1000)%cnst::t_steps_1;
            position_2 = short(millis()/1000)%cnst::t_steps_2;
            
            if(position_1 != old)
            {
                old = position_1;
                hit_1[(position_1)%cnst::t_steps_1] = 0;
                hit_2[(position_2)%cnst::t_steps_2] = 0;
            }
            
            
            byte range_1 = cnst::t_steps_1;
            byte range_2 = cnst::t_steps_2;
            
            data->lcd->setCursor(2, 1);
            short count = 0;
            
            for(byte i = 0; i < cnst::t_steps_1; ++i)
            {
                count += hit_1[i];
            }
            data->lcd->print(int(count * 1.0 / range_1 * 60 / 2));
            data->lcd->print("  ");
            
            data->lcd->setCursor(9, 1);
            count = 0;
            
            for(byte i = 0; i < cnst::t_steps_2; ++i)
            {
                count += hit_2[i];
            }
            data->lcd->print(int(count * 1.0 / range_2 * 60 / 2));
            data->lcd->print("    ");
        }
    #endif
    private:
        #ifdef SIDE_ATMEGA
            byte hit_1[cnst::t_steps_1];
            byte hit_2[cnst::t_steps_2];
            byte position_1;
            byte old;
            byte position_2;
        #endif
};

#endif //__APM_CLASS_HEADER
