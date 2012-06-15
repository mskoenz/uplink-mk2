// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.06.2012 00:33:46 CEST
// File:    rename_tier_class.hpp

#ifndef __RENAME_TIER_CLASS_HEADER
#define __RENAME_TIER_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class rename_tier_class: public menu_element_class
{
public:
	rename_tier_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        target = data->profil;
        locked = false;
        pos = 0;
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::renameTier));
            print();
        #endif
	}
    void leave_action()
	{
        #ifdef CORE_ATMEGA
        
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    
    //------------------- change -------------------
    void incr1_action()
    {
        if(locked)
        {
            if(pos != 5)
                ++pos;

            #ifdef SIDE_ATMEGA
                print();
            #endif
        }
        else
        {
            target = data->next_tier(target);

            #ifdef SIDE_ATMEGA
                print();
            #endif
        }
        
    }
    void decr1_action()
    {
        if(locked)
        {
            if(pos != 0)
                --pos;

            #ifdef SIDE_ATMEGA
                print();
            #endif
        }
        else
        {
            target = data->prev_tier(target);

            #ifdef SIDE_ATMEGA
                print();
            #endif
        }
    }
    //------------------- change -------------------
    void incr10_action()
    {
        if(locked)
        {
            byte chr = data->tier_name[data->map[target]][pos];
            
            if(chr != 122)
                ++chr;
            if(chr == 33)
                chr = 48;
            if(chr == 58)
                chr = 65;
            if(chr == 91)
                chr = 97;
            
            
            data->tier_name[data->map[target]][pos] = chr;    
            #ifdef SIDE_ATMEGA
                    print();
            #endif
        }
        else
        {
            target = data->next_tier(target);

            #ifdef SIDE_ATMEGA
                print();
            #endif
        }
    }
    void decr10_action()
    {
        if(locked)
        {
            byte chr = data->tier_name[data->map[target]][pos];
            
            if(chr != 32)
                --chr;
            if(chr == 47)
                chr = 32;
            if(chr == 64)
                chr = 57;
            if(chr == 96)
                chr = 90;
            
            
            data->tier_name[data->map[target]][pos] = chr;
            #ifdef SIDE_ATMEGA
                print();
            #endif
        }
        else
        {
            target = data->prev_tier(target);

            #ifdef SIDE_ATMEGA
                print();
            #endif
        }
    }
    //------------------- undo -------------------
    menu_element_class * left_action()
    {
        if(locked)
        {
            locked = false;
            for(byte i = 0; i < cnst::name_length - 1; ++i)
            {
                data->tier_name[data->map[target]][i] = backup[i];
            }
        }
        #ifdef SIDE_ATMEGA
            data->lcd->clear();
        #endif
        enter_action();
        return this;
    }
    //------------------- save -------------------
    menu_element_class * right_action()
    {
        if(locked)
        {
            #ifdef CORE_ATMEGA
                for(byte i = 0; i < cnst::name_length - 1; ++i)
                {
                    data->disk->write(eeprom::name_start_adr + data->map[target] * cnst::name_length + i
                                    , data->tier_name[data->map[target]][i]);
                }
                
                delayMs(cnst::watch_time);
            #elif defined SIDE_ATMEGA
                data->lcd->clear();
                data->lcd->print(text::get(text::renameDone));
                print();
                delay(cnst::watch_time);
                data->lcd->clear();
            #endif
            
            locked = false;
            enter_action();
        }
        else
        {
            locked = true;
            for(byte i = 0; i < cnst::name_length - 1; ++i)
            {
                backup[i] = data->tier_name[data->map[target]][i];
            }
            
            
            #ifdef CORE_ATMEGA
            #elif defined SIDE_ATMEGA
                data->lcd->clear();
                data->lcd->print(text::get(text::editName));
                print();
            #endif
        }
        
        return this;
    }
    
    
    #ifdef SIDE_ATMEGA
        inline void print()
        {
            if(locked)
            {
                data->lcd->setCursor(4, 1);
                for(byte i = 0; i < cnst::name_length - 1; ++i)
                {
                    if(i == pos)
                    {
                        data->lcd->print("<");
                        data->lcd->write(data->tier_name[data->map[target]][i]);
                        data->lcd->print(">");
                    }
                    else
                        data->lcd->write(data->tier_name[data->map[target]][i]);
                }
            }
            else
            {
                data->lcd->setCursor(5, 1);
                data->lcd->print(data->tier_name[data->map[target]]);
            }
            data->lcd->print("      ");
        }
    #endif
    private:
        byte target;
        byte pos;
        bool locked;
        byte backup[cnst::name_length - 1];
};

#endif //__RENAME_TIER_CLASS_HEADER
