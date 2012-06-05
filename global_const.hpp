// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.05.2012 17:50:52 CEST
// File:    global_const.hpp

#ifndef __GLOBAL_CONST_HEADER
#define __GLOBAL_CONST_HEADER

#include <Arduino.h>

typedef long unsigned int luint;

namespace disp
{
    enum disp_options
    {
          key = 0
        , time
        , dark
        , apm
        , n_disp
    };
}

namespace navi
{
    enum menu_keys
	{
		  toggle = 19
		, enter = 19
		, exit = 19
		, left = 22
		, right = 23
		, up = 21
		, down = 20
		, incr_1 = 0
		, decr_1 = 1
		, incr_10 = 2
		, decr_10 = 3
        , tier = 249
        , idle = 250
        , key_action = 251
        , start = 252
        , leave = 253        
	};
}

namespace mods
{
    enum mod_keys
    {
          down = 1
        , up
        , shift
        , gui
        , alt
        , on
        , ctrl
    };
}

namespace usb
{
    enum usb_spez_key
    {
          base = 103
        , tier0 = 104
        , tier1
        , tier2
        , tier3
    };
}

namespace cnst
{
    const byte LIST_SIZE = 6;
    //~ const byte BUFFER_SIZE = 4;
    const byte t_steps_1 = 5; //for APM
    const byte t_steps_2 = 60; //for APM
    
    const short delayLoops = 300;
	const short delayLed = 50;
    
    const byte empty = 255;
    const byte not_set = 255;
    const byte ready = 1;
    
    const short watch_time = 800;
    
    const byte end_key = 24;
    const byte n_prof = 9;
    const byte n_tier = 3;
    const byte name_length = 7;
    
    const short x_up = 700;	//threshold for digitalRead
	const short y_up = 700;
	const short x_down = 400;
	const short y_down = 400;
}

namespace text
{
    enum text_loc
    {
          init
        , version
        , switchProf
        , swapDone
        , swapDone2nd
        , swapProfil
        , red
        , blue
        , green
        , swapKeys
        , firstKey
        , secondKey
        , chooseFunc
        , selKey
        , tarKey
        , setKey
        , lcdShutter
        , ledHigh
        , ledLow
        , dispTime
        , timeRun
        , dispKey
        , keyPressed
        , dispDark
        , dispDarkText
        , lcdBright
        , lightMenu
        , dispMenu
        , mainMenu
        , profMenu
        , keyMenu
        , setKeyDone
        , empty
        , menuKey
        , swapTier
        , renameTier
        , editName
        , renameDone
        , dispAPM
        , dispAPMrun
    };
};
#endif //__GLOBAL_CONST_HEADER
