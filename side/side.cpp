// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 17:51:19 CEST
// File:    side.cpp

#define SIDE_ATMEGA

#include "../data_struct.hpp"
#include "../sync_data.hpp"

#include "../menu_class.hpp"

#include <Arduino.h>

data_struct data;
menu_class * menu;

void setup()
{
    data.lcd->write(text::get(text::init));
    data.lcd->setCursor(0, 1);
    data.lcd->write(text::get(text::version));

    sync_data(data);
    menu = new menu_class(data);
    data.com->receive();
    data.lcd->clear();
    menu->init_disp();
}
void loop()
{
    data.com->write(cnst::ready); //tell core that side is ready
    while(data.com->peek() == -1)
    {
        menu->idle();
    }
    menu->send(data.com->read());
}
#include "main.cpp"
