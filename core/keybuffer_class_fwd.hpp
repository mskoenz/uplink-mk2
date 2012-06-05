// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 21:44:56 CEST
// File:    keybuffer_class_fwd.hpp

#ifndef __KEYBUFFER_CLASS_FWD_HEADER
#define __KEYBUFFER_CLASS_FWD_HEADER

#include <list_class.hpp>
#include "../global_const.hpp"


struct data_struct;

class keybuffer_class
{
public:
	keybuffer_class(data_struct * data);
	void inline insert(byte pos);
	void inline remove(byte const pos);
	inline void update();
	inline byte top();
	inline byte * get();
    inline operator byte * ();
private:	
	list<byte> key_list;
	list<byte> key_list_all;
	bit_vector_class ptr;
	data_struct * data;
    byte pure_mod;
    byte buffer[BUFFER_SIZE];
};


#endif //__KEYBUFFER_CLASS_FWD_HEADER
