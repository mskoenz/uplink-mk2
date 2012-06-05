// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.06.2012 14:07:43 CEST
// File:    swap_profil_class.hpp

#ifndef __SWAP_PROFIL_CLASS_HEADER
#define __SWAP_PROFIL_CLASS_HEADER

#include "../menu_element_class.hpp"
#include "../../data_struct.hpp"

class swap_prof_class: public menu_element_class
{
public:
	swap_prof_class(data_struct & data): menu_element_class(data) {}
	//------------------- enter -------------------
	void enter_action()
	{
        prof1 = data->profil;
        prof2 = data->next_profil();
        
        #ifdef SIDE_ATMEGA
            data->lcd->print(text::get(text::swapProfil));
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
    
    //------------------- change prof1 -------------------
    void incr1_action()
    {
        prof1 = data->next_profil(prof1);
        if(prof1 == prof2)
            prof1 = data->next_profil(prof1);
        
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    void decr1_action()
    {
        prof1 = data->prev_profil(prof1);
        if(prof1 == prof2)
            prof1 = data->prev_profil(prof1);
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    //------------------- change prof2 -------------------
    void incr10_action()
    {
        prof2 = data->next_profil(prof2);
        if(prof1 == prof2)
            prof2 = data->next_profil(prof2);
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    void decr10_action()
    {
        prof2 = data->prev_profil(prof2);
        if(prof1 == prof2)
            prof2 = data->prev_profil(prof2);
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            print();
        #endif
    }
    //------------------- save -------------------
    menu_element_class * right_action()
    {
        byte tempA = data->map[prof1];
        byte tempB = data->map[prof1 + 1];
        byte tempC = data->map[prof1 + 2];
        data->map[prof1    ] = data->map[prof2];
        data->map[prof1 + 1] = data->map[prof2 + 1];
        data->map[prof1 + 2] = data->map[prof2 + 2];
        data->map[prof2    ] = tempA;
        data->map[prof2 + 1] = tempB;
        data->map[prof2 + 2] = tempC;
            
        #ifdef CORE_ATMEGA
            for(byte i = 0; i < cnst::n_prof; ++i)
            {
                data->disk->write(eeprom::map_start_adr + i, data->map[i]);
            }
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
            data->lcd->setCursor(1, 1);
            data->lcd->print(text::get(text::red + data->small_prof(prof2)));
            data->lcd->print("<-->");
            data->lcd->setCursor(10, 1);
            data->lcd->print(text::get(text::red + data->small_prof(prof1)));
        }
    #endif
    private:
        byte prof1;
        byte prof2;
};

#endif //__SWAP_PROFIL_CLASS_HEADER
