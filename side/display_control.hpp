// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 18:22:21 CEST
// File:    display_control.hpp

#ifndef __DISPLAY_CONTROL_HEADER
#define __DISPLAY_CONTROL_HEADER

#ifdef CORE_ATMEGA
    fail   //make sure that this file isn't included by core.cpp
#endif

#include "../global_const.hpp"
#include "custom_chars.hpp"
#include "progmem_mods.hpp"

#include <Arduino.h>

#include <LiquidCrystal.h>
#include <SPI.h>

/*
 *  Pins of the display
 o 	GND
 o 	VCC
 o 	Potentionmeter for "shutter" regulation (don't use PWM)
 o 	Pin12 in orgiginal LCD lib
 o 	GND
 o 	Pin11
 o 	-
 o 	-
 o 	-
 o 	-
 o 	Pin5
 o 	Pin4
 o 	Pin3
 o 	Pin2
 o 	VCC for backlight (potentiometer for dimming)
 o 	GND
 */


class display_class:public LiquidCrystal
{
public:
	display_class(  byte Pin12
			, byte Pin11
			, byte Pin5
			, byte Pin4
			, byte Pin3
			, byte Pin2
			, byte brPin):    LiquidCrystal(Pin12, Pin11, Pin5, Pin4, Pin3, Pin2)
							, bright_(120)
							, brPin_(brPin)
							, shutter_(115)
							, spiPin_(10)
	{
		pinMode(brPin_, OUTPUT);
		pinMode(spiPin_, OUTPUT);
		set_brightness(bright_);
		SPI.begin();
		set_shutter(shutter_);
        
        //------------------- adding custom chars -------------------
        createChar(mods::alt, custom::alt_custom);
        createChar(mods::down, custom::down);
        createChar(mods::up, custom::up);
        createChar(mods::on, custom::on);
        createChar(mods::gui, custom::gui);
        createChar(mods::shift, custom::shift);
        createChar(mods::ctrl, custom::ctrl);
        
        //------------------- init -------------------
        begin(16, 2);
        noCursor();
        noBlink();
        
        //------------------- custom chars -------------------
        
	}
	void set_brightness(byte const brightness)
	{
        analogWrite(brPin_, brightness);
        bright_ = brightness;
	}
	byte get_brightness()
	{
		return bright_;
	}
	
	void set_shutter(byte const shutter)
	{
        digitalWrite(spiPin_, LOW);
        SPI.transfer(0); //channel
        SPI.transfer(shutter); //value
        shutter_ = shutter;
	}
	byte get_shutter()
	{
		return shutter_;
	}
private:
	byte bright_;
	byte brPin_; //brightness Pin (must be PWM)
	byte shutter_;
	byte spiPin_;	//pin for SPI w/ digital potentiometer
};


#endif //__DISPLAY_CONTROL_HEADER
