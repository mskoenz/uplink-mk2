// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 15:03:41 CEST
// File:    key_reader_class.hpp

#ifdef SIDE_ATMEGA
    fail   //make sure that this file isn't included by side.cpp
#endif

#ifndef __KEY_READER_CLASS_HEADER
#define __KEY_READER_CLASS_HEADER

#include <mux_template.hpp>
#include <bit_vector_class.hpp>

#include <Arduino.h>

class key_reader_class: public bit_vector_class
{
public:
	key_reader_class():   bit_vector_class(1lu<<cnst::end_key)
                        , mux(A0, 13, 12, 11, 7)
                        , old_(1lu<<cnst::end_key) 
                        , lowest(0)
    {
        mux.mux_read_setup();
		pinMode(8, INPUT);
    }
	inline void update()
	{
		byte a[16];
		mux.read_all_fast_4(a);
        
		set_bit(0, digitalRead(8));
        
		for(byte i = 8; i < 16; ++i)
		{
			set_bit(i - 7, a[23 - i]);
		}
		for(byte i = 0; i < 8; ++i)
		{
			set_bit(i + 9, a[i]);
		}
		set_bit(17, digitalRead(A1));
		set_bit(18, digitalRead(A2));
		set_bit(19, digitalRead(A3));
		
		set_bit(20, analogRead(A4) < cnst::y_down ? 1: 0);
		set_bit(21, analogRead(A4) > cnst::y_up ? 1: 0);
		set_bit(22, analogRead(A5) > cnst::x_up ? 1: 0);
		set_bit(23, analogRead(A5) < cnst::x_down ? 1: 0);
	}
	
	inline luint diff() const 
	{
		return old_ ^ (this->get());
	}
	
	inline byte lowest_change()
	{
		luint dif = diff();
		lowest = 0;
		while((dif & 1lu) == 0)
		{
			++lowest;
			dif>>=1;
		}
		return lowest;
	}
    inline void update_lowest()
    {
		luint r = (*this)[lowest];
		old_ &= ~(1lu << lowest); //delete bit
		old_ |= (r << lowest); //set it new
		
    }
    inline byte extract_lowest()
    {
        luint dif = diff();
		lowest = 0;
		while((dif & 1lu) == 0)
		{
			++lowest;
			dif>>=1;
		}
        
		luint r = (*this)[lowest];
		old_ &= ~(1lu << lowest); //delete bit
		old_ |= (r << lowest); //set it new
        
        return lowest;
    }
private:
	mux_read_class<4, true> mux;
	luint old_;
    byte lowest; //small optimization
};


#endif //__KEY_READER_CLASS_HEADER
