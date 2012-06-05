// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    01.06.2012 16:21:43 CEST
// File:    label_class.hpp

#ifndef __LABEL_CLASS_HEADER
#define __LABEL_CLASS_HEADER

#include "menu_element_class.hpp"
#include "../data_struct.hpp"


class label_class: public menu_element_class
{
public:
	label_class(data_struct & data, byte text): menu_element_class(data), text_nr(text) {}
	//------------------- enter -------------------
	inline void enter_action()
	{
        #ifdef CORE_ATMEGA
            
        #elif defined SIDE_ATMEGA
            data->lcd->print(text::get(text_nr));
        #endif
	}
    inline void leave_action()
	{
        #ifdef SIDE_ATMEGA
            data->lcd->clear();
        #endif
	}
    private:
        byte text_nr;
};

#endif //__LABEL_CLASS_HEADER
