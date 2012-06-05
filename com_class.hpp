// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 23:23:06 CEST
// File:    com_class.hpp

#ifndef __COM_CLASS_HEADER
#define __COM_CLASS_HEADER


#include "global_const.hpp"

#include "SoftwareSerial.h"
#include <Arduino.h>


/// +---------------------------------------------------+
/// |                   constants                       |
/// +---------------------------------------------------+
const byte send_delay = 10;

class com_class: public SoftwareSerial
{
public:
    com_class(byte Tx, byte Rx): SoftwareSerial(Tx, Rx) 
    {
        begin(57600);
    }
    inline void wait()
    {
        while(peek() == -1){}
    }
    #ifdef CORE_ATMEGA
    inline void send(byte data)
    {
        wait(); //wait until side is ready to receive
        read(); //delete the ready signal
        write(data); //send data
    }
    #elif defined SIDE_ATMEGA
    inline byte receive()
    {
        write(cnst::ready); //tell core that side is ready
        wait(); //wait for data
        return read();
    }
       
    #endif
private:
};


#endif //__COM_CLASS_HEADER
