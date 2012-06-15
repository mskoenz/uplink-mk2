// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.06.2012 00:20:42 CEST
// File:    swap_tier_class.hpp

#ifndef __SWAP_TIER_CLASS_HEADER
#define __SWAP_TIER_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class swap_tier_class: public menu_element_class
{
public:
	swap_tier_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        tier1 = data->profil;
        tier2 = data->next_tier();
        
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::swapTier));
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
    
    //------------------- change tier1 -------------------
    void incr1_action()
    {
        tier1 = data->next_tier(tier1);
        if(tier1 == tier2)
            tier1 = data->next_tier(tier1);
        
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    void decr1_action()
    {
        tier1 = data->prev_tier(tier1);
        if(tier1 == tier2)
            tier1 = data->prev_tier(tier1);
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    //------------------- change tier2 -------------------
    void incr10_action()
    {
        tier2 = data->next_tier(tier2);
        if(tier1 == tier2)
            tier2 = data->next_tier(tier2);
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    void decr10_action()
    {
        tier2 = data->prev_tier(tier2);
        if(tier1 == tier2)
            tier2 = data->prev_tier(tier2);
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    //------------------- save -------------------
    menu_element_class * right_action()
    {
        byte temp = data->map[tier1];
        data->map[tier1] = data->map[tier2];
        data->map[tier2] = temp;
            
        #ifdef CORE_ATMEGA
            data->disk->write(eeprom::map_start_adr + tier1, data->map[tier1]);
            data->disk->write(eeprom::map_start_adr + tier2, data->map[tier2]);
            delayMs(cnst::watch_time);
        #elif defined SIDE_ATMEGA
            data->lcd->clear();
            data->lcd->print(text::get(text::swapDone));
            data->lcd->setCursor(0, 1);
            data->lcd->print(text::get(text::swapDone2nd));
            delay(cnst::watch_time);
            data->lcd->clear();
        #endif
        
        enter_action();
        
        return this;
    }
    
    
    #ifdef SIDE_ATMEGA
        inline void print()
        {
            data->lcd->setCursor(0, 1);
            data->lcd->print(data->tier_name[data->map[tier2]]);
            data->lcd->print("<-->");
            data->lcd->setCursor(10, 1);
            data->lcd->print(data->tier_name[data->map[tier1]]);
        }
    #endif
    private:
        byte tier1;
        byte tier2;
};

#endif //__SWAP_TIER_CLASS_HEADER
