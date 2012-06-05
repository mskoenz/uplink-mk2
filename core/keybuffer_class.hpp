// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    11.05.2012 00:25:42 CEST
// File:    keyToBuffer.hpp

#ifndef __KEYTOBUFFER_HEADER
#define __KEYTOBUFFER_HEADER

#include <../global_const.hpp>
#include <list_class.hpp>
#include <bit_vector_class.hpp>

struct data_struct;

#include <../data_struct.hpp>
#include <keybuffer_class_fwd.hpp>


keybuffer_class::keybuffer_class(data_struct * data): ptr(0), data(data), pure_mod(0) 
{
    for(byte i = 0; i < BUFFER_SIZE; ++i)
    {
        buffer[i] = 0;
    }
}

void inline keybuffer_class::insert(byte pos)
{
    if(data->get_key(pos) == 0) //pure modifier case
        pure_mod |= data->get_mod(pos);
    else
    {
        if(data->get_key(pos) > usb::base) // if it is a tier-changer
        {
            if(data->in_menu == false) // and we are not in the menu
            {
                //change tier
                byte sub = data->get_key(pos) - usb::tier0;
                data->change_tier(sub);
                data->com->send(navi::tier);
                data->com->send(data->profil);
            }
        }
        else //its a normal key
            key_list.push_back(pos);
    }
        
    key_list_all.push_back(pos);
    
    ptr[pos] = 1;
    
    
    //------------------- if list too long -------------------
    if(key_list.size() > cnst::LIST_SIZE - 1) //-1 bc modifiers
    {
        byte rem = key_list_all.front();
        remove(rem);
    }
    update();
}
    
void inline keybuffer_class::remove(byte pos)
{
    if(ptr[pos] != 0)
    {
        ptr[pos] = 0;
        
        if(data->get_key(pos) == 0) //remove pure modifier
            pure_mod &= ~(data->get_mod(pos));
        else
        {
            if(data->get_key(pos) > usb::base)  //remove tier-changer
            {
                if(data->in_menu == false) //if in menu
                {
                    byte sub = data->get_key(pos) - usb::tier0; // change back
                    bool send = false; // if a covered tier-changer is released, do nothing
                    
                    for(int i = key_list_all.size() - 1; i >= 0; --i)  //check it other tier-changers are active
                        if(data->get_key(key_list_all[i]) > usb::base)  //tier-changers
                        {
                            if(key_list_all[i] == pos) //if pos is the one on top, change needs to be sent
                            {
                                send = true;
                            }
                            else //found a other tier-changer -> break
                            {
                                sub = data->get_key(key_list_all[i]) - usb::tier0;
                                break;
                            }
                        }
                    if(send)
                    {
                        data->change_tier(sub);
                        data->com->send(navi::tier);
                        data->com->send(data->profil);
                    }
                }
            }
            else
                key_list.remove(pos);
        }
        
        key_list_all.remove(pos);
        update();
    }
    pure_mod = 0;
}
inline void keybuffer_class::update()
{
    
    buffer[0] = pure_mod;
    for(byte i = 1; i < BUFFER_SIZE; ++i) //delete Buffer
    {
        buffer[i] = 0;
    }
    
    if(key_list.size() > 0)
    {
        buffer[0] |= data->get_mod(key_list.back());
        buffer[1] = data->get_key(key_list.back());
    }
}
inline byte * keybuffer_class::get()
{
    return buffer;
}
inline keybuffer_class::operator byte * ()
{
    return buffer;
}

inline byte keybuffer_class::top()
{
    if(key_list_all.size() > 0)
        return key_list_all.top();
    else
        return cnst::empty;
}


#endif //__KEYTOBUFFER_HEADER
