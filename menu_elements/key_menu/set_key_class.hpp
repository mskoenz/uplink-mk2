// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 19:16:03 CEST
// File:    set_key_class.hpp

#ifndef __SET_KEY_CLASS_HEADER
#define __SET_KEY_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class set_key_class: public menu_element_class
{
public:
	set_key_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        data->change_tier(0);
        selectedKey = cnst::not_set;
        newKey = 0;
        newMod = 0;
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text::setKey));
        #endif
	}
    void leave_action()
	{
        data->change_tier(0);
        #ifdef SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    //------------------- incr/decr -------------------
    void incr1_action() 
    {
        if(selectedKey != cnst::not_set)
        {
            if(newKey != usb::base + cnst::n_tier)
            {
                ++newKey;
                if(newKey > usb::base)
                {
                    newMod = 0;
                    #ifdef SIDE_ATMEGA
                        data->lcd->setCursor(2, 1);
                        data->lcd->print(mods::get(newMod));
                    #endif
                }
            }
                
            if(newKey == 49)
                ++newKey;
                
            #ifdef SIDE_ATMEGA
                data->lcd->setCursor(9, 1);
                if(newKey > usb::base)
                    data->lcd->print(data->tier_name[data->map[data->small_prof()*cnst::n_tier + (newKey - usb::tier0)]]);
                else
                    data->lcd->print(keys::get(newKey));
            #endif
        }
    }
    
    void decr1_action() 
    {
        if(selectedKey != cnst::not_set)
        {
            if(newKey != 3)
                --newKey;
            if(newKey == 49)
                --newKey;
                
            #ifdef SIDE_ATMEGA
                data->lcd->setCursor(9, 1);
                if(newKey > usb::base)
                    data->lcd->print(data->tier_name[data->map[data->small_prof()*cnst::n_tier + (newKey - usb::tier0)]]);
                else
                    data->lcd->print(keys::get(newKey));
            #endif
        }
    }
    //------------------- mod incr/decr -------------------
    void incr10_action() 
    {
        if(selectedKey != cnst::not_set)
        {
            if(newMod != 15 and newKey < usb::tier0)
                ++newMod;
            
            #ifdef SIDE_ATMEGA    
                data->lcd->setCursor(2, 1);
                data->lcd->print(mods::get(newMod));
            #endif
        }
    }
    void decr10_action() 
    {
        if(selectedKey != cnst::not_set)
        {
            if(newMod != 0)
                --newMod;
            #ifdef SIDE_ATMEGA
                data->lcd->setCursor(2, 1);
                data->lcd->print(mods::get(newMod));
            #endif
        }
    }
    //------------------- use up/down as tier rotator -------------------
    menu_element_class * up_action()
    {
        if(selectedKey != cnst::not_set)
        {
            data->change_tier((data->profil + 1)%cnst::n_tier);
            newKey = data->get_key(selectedKey);
            newMod = data->get_mod(selectedKey);
            #ifdef SIDE_ATMEGA
                print();
            #endif
            return this;
        }
        else 
            return menu_element_class::up_action();
    }
    
    menu_element_class * down_action()
    {
        if(selectedKey != cnst::not_set)
        {
            data->change_tier((data->profil + 2)%cnst::n_tier);
            newKey = data->get_key(selectedKey);
            newMod = data->get_mod(selectedKey);
            #ifdef SIDE_ATMEGA
                print();
            #endif
            return this;
        }
        else
            return menu_element_class::down_action();
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
        if(selectedKey == cnst::not_set)
        {
            #ifdef CORE_ATMEGA
                selectedKey = get_key();
                data->com->send(selectedKey);
            #elif defined SIDE_ATMEGA
                data->lcd->clear();
                data->lcd->print(text::get(text::tarKey));
                selectedKey = data->com->receive();
            #endif
            
            newKey = data->get_key(selectedKey);
            newMod = data->get_mod(selectedKey);
            
            if(newKey == 0)
                newKey = 3;
            
            #ifdef CORE_ATMEGA
                delayMs(cnst::watch_time);
            #elif defined SIDE_ATMEGA
                data->lcd->clear();
                data->lcd->print(text::get(text::selKey));
                data->lcd->setCursor(6, 1);
                data->lcd->print(selectedKey);
                delay(cnst::watch_time);
                data->lcd->clear();
                data->lcd->print(text::get(text::chooseFunc));
                print();
            #endif

            
        }
        else
        {
            if(newKey == 3)
                newKey = 0;
            #ifdef CORE_ATMEGA
                data->write_key(selectedKey, newKey);
                data->write_mod(selectedKey, newMod);
                if(newKey > usb::base)
                {
                    byte tier = data->profil % cnst::n_tier;
                    byte level = usb::tier0 + tier;
                    byte home = usb::tier0;
                    if(tier == 0)
                    {
                        level = newKey;
                        tier = level -usb::tier0;
                    }
                    if(level != home)
                    {
                        for(byte i = 0; i < cnst::n_tier; ++i)
                        {
                            data->change_tier(i);
                            if(i == tier)
                            {
                                data->write_key(selectedKey, home);
                                data->write_mod(selectedKey, newMod);
                            }
                            else
                            {
                                data->write_key(selectedKey, level);
                                data->write_mod(selectedKey, newMod);
                            }
                        }
                        data->change_tier(tier);
                    }
                }
                else
                {
                    byte tier = data->profil % cnst::n_tier;
                    for(byte i = 0; i < cnst::n_tier; ++i)
                    {
                        data->change_tier(i);
                        if(data->get_key(selectedKey) > usb::base)
                            data->write_key(selectedKey, 4);
                    }
                    data->change_tier(tier);
                }
                delayMs(cnst::watch_time);
            #elif defined SIDE_ATMEGA
                data->lcd->clear();
                data->lcd->print(text::get(text::setKeyDone));
                print();
                delay(cnst::watch_time);
                data->lcd->clear();
                data->lcd->print(text::get(text::chooseFunc));
                print();
            #endif
                
            data->set_key(selectedKey, newKey);
            data->set_mod(selectedKey, newMod);
            if(newKey > usb::base)
            {
                byte tier = data->profil % cnst::n_tier;
                byte level = usb::tier0 + tier;
                byte home = usb::tier0;
                if(tier == 0)
                {
                    level = newKey;
                    tier = level -usb::tier0;
                }
                if(level != home)
                {
                    for(byte i = 0; i < cnst::n_tier; ++i)
                    {
                        data->change_tier(i);
                        if(i == tier)
                        {
                            data->set_key(selectedKey, home);
                            data->set_mod(selectedKey, newMod);
                        }
                        else
                        {
                            data->set_key(selectedKey, level);
                            data->set_mod(selectedKey, newMod);
                        }
                    }
                    data->change_tier(tier);
                }
            }
            else
            {
                byte tier = data->profil % cnst::n_tier;
                for(byte i = 0; i < cnst::n_tier; ++i)
                {
                    data->change_tier(i);
                    if(data->get_key(selectedKey) > usb::base)
                        data->set_key(selectedKey, 4);
                }
                data->change_tier(tier);
            }
            //~ enter_action();
            
        }
        return this;
    }
    //------------------- print -------------------
    #ifdef SIDE_ATMEGA
        inline void print()
        {
            data->lcd->setCursor(10, 0);
            data->lcd->print(data->tier_name[data->map[data->profil]]);
            data->lcd->setCursor(2, 1);
            data->lcd->print(mods::get(newMod));
            data->lcd->setCursor(9, 1);
            if(newKey > usb::base)
                data->lcd->print(data->tier_name[data->map[data->small_prof() * cnst::n_tier + (newKey - usb::tier0)]]);
            else
                data->lcd->print(keys::get(newKey));
        }
    #endif
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
        byte newKey;
        byte newMod;
};

#endif //__SET_KEY_CLASS_HEADER
