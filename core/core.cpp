// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 17:51:32 CEST
// File:    core.cpp

#define CORE_ATMEGA

#include <usbHelper.hpp>
#include "../data_struct.hpp"
#include "../menu_class.hpp"

#include "keybuffer_class.hpp"

#include "read_eeprom.hpp"
#include "write_eeprom.hpp"
#include "../sync_data.hpp"


#include <Arduino.h>

data_struct data;
menu_class * menu;

void (*mode)();

void keyboard_mode()
{    
    if((*data.buffer)[1] == 0)
        UsbKeyboard.sendBufferNoBreak((*data.buffer));
    else
        UsbKeyboard.sendBuffer((*data.buffer));
}

void menu_mode()
{
    if(data.buffer->top() != cnst::empty)
    {
        menu->send(data.buffer->top());
        delayMs(18);
    }
}
void setup()
{
    //~ data.disk->erase();
    //~ eeprom::write(data);
    //~ Serial.begin(57600);
    eeprom::read(data);
    
    sync_data(data);
    
    menu = new menu_class(data);
    mode = keyboard_mode;
    
    initKeyboard();
    data.com->write(cnst::ready);
}

long int clock = 1;
/// +---------------------------------------------------+
/// |                   main loop                       |
/// +---------------------------------------------------+
void loop()
{
    UsbKeyboard.update();
	data.button->update();
    
	if(data.button->diff())
	{
		byte pos = data.button->extract_lowest(); //only one change per loop
		
		if((*data.button)[pos]) //key went high
		{
			clock = 0; //only new key get small delay
			data.set_led_high();
            
			if(pos == data.menu_key)
			{
                if(mode == keyboard_mode)
                {
                    menu->send(navi::start);
                    mode = menu_mode;
                }
                else
                {
                    menu->send(navi::leave);
                    mode = keyboard_mode;
                }
			}
            else
            {
                data.buffer->insert(pos);
                if(pos != data.menu_key)
                    menu->send(navi::key_action);
            }
		}
		else //key went low
        {
			data.buffer->remove(pos);
            if(pos != data.menu_key)
                menu->send(navi::key_action); //send key event
        }
	}
	if(clock > cnst::delayLoops or clock == 0)
    {
        mode();
    }
    
	data.blink(clock, (*data.buffer)[1]);
	
    ++clock;
}
#include "main.cpp"
