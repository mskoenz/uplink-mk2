// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 22:35:55 CEST
// File:    menu_key_class.hpp

#ifndef __MENU_KEY_CLASS_HEADER
#define __MENU_KEY_CLASS_HEADER
#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class menu_key_class: public menu_element_class
{
public:
	menu_key_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        selectedKey = cnst::not_set;
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::menuKey));
        #endif
	}
    void leave_action()
	{
        data->change_tier(0);
        #ifdef SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    //------------------- use left as cancel -------------------
    menu_element_class * left_action()
    {
        #ifdef CORE_ATMEGA
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
        #endif
        enter_action();
        return this;
    }
    //------------------- use right as setter -------------------
    menu_element_class * right_action()
    {
        //------------------- get key -------------------
        #ifdef CORE_ATMEGA
            selectedKey = get_key();
            data->com->send(selectedKey);
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
            data->lcd->print(text::get(text::tarKey));
            selectedKey = data->com->receive();
        #endif
        
        data->menu_key = selectedKey;
        
        //------------------- print selected -------------------
        #ifdef CORE_ATMEGA
            delayMs(cnst::watch_time);
            data->disk->write(eeprom::menu_key_adr, data->menu_key);
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
            data->lcd->print(text::get(text::selKey));
            data->lcd->setCursor(6, 1);
            data->lcd->print(selectedKey);
            delay(cnst::watch_time);
            data->lcd->clear();
        #endif
        
        enter_action();
        
        return this;
    }
    //------------------- get_key -------------------
    #ifdef CORE_ATMEGA
        byte get_key()
        {
            byte pos = 0;
            while(true)
            {
                data->button->update();
                if(data->button->diff())
                {
                    pos = data->button->extract_lowest();
                    if((*data->button)[pos] == 1)
                    {
                        return pos;
                    }
                }
                else
                {
                    data->buffer->remove(pos);       //important in order to kick out the
                                                     //key that triggered the incr_1_action
                                                     //from the buffer
                }
            }
            return 0;
        }
    #endif
    
    private:
        byte selectedKey;
};

#endif //__MENU_KEY_CLASS_HEADER
