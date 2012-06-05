// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    12.05.2012 18:26:13 CEST
// File:    menu_element_classClass.hpp

#ifndef __MENUELEMENTCLASS_HEADER
#define __MENUELEMENTCLASS_HEADER

struct data_struct;

class menu_element_class
{
	public:
		menu_element_class(data_struct & data): data(&data), left(NULL), right(NULL), up(NULL), down(NULL) {}
		
        //This enter an leave actions are for scroling through the menus
        virtual void enter_action() {}
		virtual void leave_action() {}

        //this enter and leave are called when you leave the entire menu-structure
		virtual menu_element_class * leave_here() {return NULL;}
		virtual void enter_here() {}

        //incr and decr actions
        virtual void incr1_action() {}
		virtual void decr1_action() {}
		virtual void incr10_action() {}
		virtual void decr10_action() {}
        
        //only side actions, idle will run as long as there is on key and key_action is called
        //when a key is pressed in normal use (not in menu)
        virtual void idle_action() {};
        virtual void key_action() {};
		
		virtual menu_element_class * right_action(){
			if(right != this)
            {
                leave_action();
                right->enter_action();
            }
            else
            {
                incr1_action();
            }
            
			return right;
		}
		virtual menu_element_class * left_action(){
            if(left != this)
            {
                leave_action();
                left->enter_action();
            }
            else
            {
                decr1_action();
            }
			return left;
		}
		virtual menu_element_class * up_action(){
			if(up != this)
            {
                leave_action();
                up->enter_action();
            }
			return up;
		}
		virtual menu_element_class * down_action(){
			if(down != this)
            {
                leave_action();
                down->enter_action();
            }
			return down;
		}
        
        
        //only right and down direction need to be given
        //later neightbours will link up and left automatically
		inline void set_neighbours(menu_element_class * r, menu_element_class * d)
		{
            if(r == NULL)
                r = this;
            if(d == NULL)
                d = this;
                
			right = r;
			down = d;
            
            if(r != this)
                r->left = this;
            
            if(d != this)
                d->up = this;
            
            //default is self
            if(left == NULL)
                left = this;
			if(up == NULL)
                up = this;
		}
		
		data_struct * data;

		menu_element_class * left;
		menu_element_class * right;
		menu_element_class * up;
		menu_element_class * down;
		
};

#endif //__MENUELEMENTCLASS_HEADER
