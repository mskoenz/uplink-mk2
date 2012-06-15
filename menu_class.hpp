// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    12.05.2012 14:52:33 CEST
// File:    menu.hpp

#ifndef __MENUCLASS_HEADER
#define __MENUCLASS_HEADER

#include "Arduino.h"
#include "data_struct.hpp"
#include "menu_elements.hpp"

class menu_class
{
public:
	menu_class(data_struct & data_in): data(&data_in)
	{
        //------------------- labels -------------------
        menu_element_class * main_menu = new label_class(data_in, text::mainMenu);
        menu_element_class * light_menu = new label_class(data_in, text::lightMenu);
        menu_element_class * disp_menu = new label_class(data_in, text::dispMenu);
        menu_element_class * profil_menu = new label_class(data_in, text::profMenu);
        menu_element_class * key_menu = new label_class(data_in, text::keyMenu);
        
        //------------------- lights -------------------
        menu_element_class * bright = new bright_class(data_in);
        menu_element_class * shutter = new shutter_class(data_in);
        menu_element_class * led_high = new led_high_class(data_in);
        menu_element_class * led_low = new led_low_class(data_in);
        
        //------------------- display -------------------
        menu_element_class * key = new key_class(data_in);
        menu_element_class * time = new time_class(data_in);
        menu_element_class * dark = new dark_class(data_in);
        menu_element_class * apm = new apm_class(data_in);
        
        //------------------- profil -------------------
        menu_element_class * switch_prof = new switch_prof_class(data_in);
        menu_element_class * swap_prof = new swap_prof_class(data_in);
        menu_element_class * swap_tier = new swap_tier_class(data_in);
        menu_element_class * rename_tier = new rename_tier_class(data_in);
        
        //------------------- key -------------------
        menu_element_class * set_key = new set_key_class(data_in);
        menu_element_class * set_menu_key = new menu_key_class(data_in);
        
        
        main_menu->set_neighbours(profil_menu, NULL);
        profil_menu->set_neighbours(disp_menu, switch_prof);
        disp_menu->set_neighbours(light_menu, key);
        light_menu->set_neighbours(key_menu, bright);
        key_menu->set_neighbours(main_menu, set_key);
        
        bright->set_neighbours(NULL, shutter);
        shutter->set_neighbours(NULL, led_high);
        led_high->set_neighbours(NULL, led_low);
        led_low->set_neighbours(NULL, NULL);
        
        key->set_neighbours(NULL, time);
        time->set_neighbours(NULL, dark);
        dark->set_neighbours(NULL, apm);
        apm->set_neighbours(NULL, NULL);
        
        switch_prof->set_neighbours(NULL, swap_prof);
        swap_prof->set_neighbours(NULL, swap_tier);
        swap_tier->set_neighbours(NULL, rename_tier);
        rename_tier->set_neighbours(NULL, NULL);
        
        set_key->set_neighbours(NULL, set_menu_key);
        set_menu_key->set_neighbours(NULL, NULL);
        
        
        menu_element_class * disp_pos[disp::n_disp];
        disp_pos[disp::time] = time;
        disp_pos[disp::dark] = dark;
        disp_pos[disp::key] = key;
        disp_pos[disp::apm] = apm;
        
        
        
        home_position = main_menu;
        position = disp_pos[data->disp_pos];
        
        
    }
    inline void init_disp()
    {
        position->leave_here();
    }
	void send(byte const key = 0)
	{
        menu_element_class * potential_disp_pos = NULL; //used in leave
        #ifdef CORE_ATMEGA
            data->com->send(key);
        #endif
        
        if(data->in_menu)
        {
            switch(key)
            {
                //=================== navigators ===================
                case(navi::right): //advance
                    position = position->right_action();
                    break;
                case(navi::left): //return
                    position = position->left_action();
                    break;
                case(navi::up):
                    position = position->up_action();
                    break;
                case(navi::down):
                    position = position->down_action();
                    break;
                //=================== modifiers ===================
                case(navi::incr_1):
                    position->incr1_action();
                    break;
                case(navi::decr_1):
                    position->decr1_action();
                    break;
                case(navi::incr_10):
                    position->incr10_action();
                    break;
                case(navi::decr_10):
                    position->decr10_action();
                    break;
                case(navi::leave): //leave

                    position->leave_action();
                    potential_disp_pos = position->leave_here();
                    if(potential_disp_pos != NULL)
                        position = potential_disp_pos;
                    else
                    {
                        position = display_position;
                        position->leave_here();
                    }
                    
                    data->in_menu = false;
                    
                    break;
                case(navi::key_action):
                    position->key_action();
                    break;
                case(navi::idle):
                    position->idle_action();
                    break;
            }
        }
        else
        {
            switch(key)
            {
                case(navi::start): //Start
                    #ifdef SIDE_ATMEGA
                        data->lcd->clear();
                    #endif
                    position->enter_here();
                    display_position = position;
                    
                    position = home_position;
                    position->enter_action();
                    
                    data->in_menu = true;
                    
                    break;
                case(navi::key_action):
                    position->key_action();
                    break;
                case(navi::idle):
                    position->idle_action();
                    break;
                #ifdef SIDE_ATMEGA
                case(navi::tier):
                    data->profil = data->com->receive();
                    break;
                #endif
            }
        }
	}
        #ifdef SIDE_ATMEGA
            inline void idle()
            {
                position->idle_action();
            }
        #endif
private:
	data_struct * data;
	menu_element_class * position;
	menu_element_class * home_position;
	menu_element_class * display_position;
};
#endif //__MENUCLASS_HEADER
