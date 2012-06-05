// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    17.05.2012 12:25:22 CEST
// File:    progmem.hpp

#ifndef __PROGMEM_KEYS_HEADER
#define __PROGMEM_KEYS_HEADER

#ifdef CORE_ATMEGA
    fail   //make sure that this file isn't included by core.cpp
#endif

//all the string are stored in programm memory in order not to consume the 2kB SRAM

#include "../global_const.hpp"

#include <avr/pgmspace.h>

namespace keys //keySpace
{
    char buffer[16];

    prog_char n00[] PROGMEM = "      ";
    prog_char n01[] PROGMEM = "      ";
    prog_char n02[] PROGMEM = "      ";
    prog_char n03[] PROGMEM = "      ";
    prog_char n04[] PROGMEM = "key A ";
    prog_char n05[] PROGMEM = "key B ";
    prog_char n06[] PROGMEM = "key C ";
    prog_char n07[] PROGMEM = "key D ";
    prog_char n08[] PROGMEM = "key E ";
    prog_char n09[] PROGMEM = "key F ";
    prog_char n10[] PROGMEM = "key G ";
    prog_char n11[] PROGMEM = "key H ";
    prog_char n12[] PROGMEM = "key I ";
    prog_char n13[] PROGMEM = "key J ";
    prog_char n14[] PROGMEM = "key K ";
    prog_char n15[] PROGMEM = "key L ";
    prog_char n16[] PROGMEM = "key M ";
    prog_char n17[] PROGMEM = "key N ";
    prog_char n18[] PROGMEM = "key O ";
    prog_char n19[] PROGMEM = "key P ";
    prog_char n20[] PROGMEM = "key Q ";
    prog_char n21[] PROGMEM = "key R ";
    prog_char n22[] PROGMEM = "key S ";
    prog_char n23[] PROGMEM = "key T ";
    prog_char n24[] PROGMEM = "key U ";
    prog_char n25[] PROGMEM = "key V ";
    prog_char n26[] PROGMEM = "key W ";
    prog_char n27[] PROGMEM = "key X ";
    prog_char n28[] PROGMEM = "key Z ";
    prog_char n29[] PROGMEM = "key Y ";
    prog_char n30[] PROGMEM = "key 1 ";
    prog_char n31[] PROGMEM = "key 2 ";
    prog_char n32[] PROGMEM = "key 3 ";
    prog_char n33[] PROGMEM = "key 4 ";
    prog_char n34[] PROGMEM = "key 5 ";
    prog_char n35[] PROGMEM = "key 6 ";
    prog_char n36[] PROGMEM = "key 7 ";
    prog_char n37[] PROGMEM = "key 8 ";
    prog_char n38[] PROGMEM = "key 9 ";
    prog_char n39[] PROGMEM = "key 0 ";
    prog_char n40[] PROGMEM = "enter ";
    prog_char n41[] PROGMEM = "escape";
    prog_char n42[] PROGMEM = "backSp";
    prog_char n43[] PROGMEM = "tab   ";
    prog_char n44[] PROGMEM = "space ";
    prog_char n45[] PROGMEM = "key ' ";
    prog_char n46[] PROGMEM = "key ^ ";
    prog_char n47[] PROGMEM = {'k','e','y',' ',245, ' ', 0};
    prog_char n48[] PROGMEM = "key ! ";
    prog_char n49[] PROGMEM = "no key ";
    prog_char n50[] PROGMEM = "key $ ";
    prog_char n51[] PROGMEM = {'k','e','y',' ',239, ' ', 0};
    prog_char n52[] PROGMEM = {'k','e','y',' ',225, ' ', 0};
    prog_char n53[] PROGMEM = {'k','e','y',' ',223, ' ', 0};
    prog_char n54[] PROGMEM = "key , ";
    prog_char n55[] PROGMEM = "key . ";
    prog_char n56[] PROGMEM = "key - ";
    prog_char n57[] PROGMEM = "caps  ";
    prog_char n58[] PROGMEM = "F1    ";
    prog_char n59[] PROGMEM = "F2    ";
    prog_char n60[] PROGMEM = "F3    ";
    prog_char n61[] PROGMEM = "F4    ";
    prog_char n62[] PROGMEM = "F5    ";
    prog_char n63[] PROGMEM = "F6    ";
    prog_char n64[] PROGMEM = "F7    ";
    prog_char n65[] PROGMEM = "F8    ";
    prog_char n66[] PROGMEM = "F9    ";
    prog_char n67[] PROGMEM = "F10   ";
    prog_char n68[] PROGMEM = "F11   ";
    prog_char n69[] PROGMEM = "F12   ";
    prog_char n70[] PROGMEM = "prtScr";
    prog_char n71[] PROGMEM = "sclLck";
    prog_char n72[] PROGMEM = "pause ";
    prog_char n73[] PROGMEM = "insert";
    prog_char n74[] PROGMEM = "home  ";
    prog_char n75[] PROGMEM = "pgUp  ";
    prog_char n76[] PROGMEM = "delete";
    prog_char n77[] PROGMEM = "end   ";
    prog_char n78[] PROGMEM = "pgDown";
    prog_char n79[] PROGMEM = {'a','r','r','o','w', 126, 0};
    prog_char n80[] PROGMEM = {'a','r','r','o','w', 127, 0};
    prog_char n81[] PROGMEM = {'a','r','r','o','w', mods::down, 0};
    //~ prog_char n81[] PROGMEM = "arr dw";
    prog_char n82[] PROGMEM = {'a','r','r','o','w', mods::up, 0};
    //~ prog_char n82[] PROGMEM = "arr up";
    prog_char n83[] PROGMEM = "numLck";
    prog_char n84[] PROGMEM = "pad / ";
    prog_char n85[] PROGMEM = "pad * ";
    prog_char n86[] PROGMEM = "pad - ";
    prog_char n87[] PROGMEM = "pad + ";
    prog_char n88[] PROGMEM = "padEtr";
    prog_char n89[] PROGMEM = "pad 1 ";
    prog_char n90[] PROGMEM = "pad 2 ";
    prog_char n91[] PROGMEM = "pad 3 ";
    prog_char n92[] PROGMEM = "pad 4 ";
    prog_char n93[] PROGMEM = "pad 5 ";
    prog_char n94[] PROGMEM = "pad 6 ";
    prog_char n95[] PROGMEM = "pad 7 ";
    prog_char n96[] PROGMEM = "pad 8 ";
    prog_char n97[] PROGMEM = "pad 9 ";
    prog_char n98[] PROGMEM = "pad 0 ";
    prog_char n99[] PROGMEM = "pad . ";
    prog_char n100[] PROGMEM = "key < ";
    prog_char n101[] PROGMEM = "apps  ";
    prog_char n102[] PROGMEM = {'k', 'e', 'y', ' ', mods::on, ' ', 0};
    //~ prog_char n102[] PROGMEM = "key on";
    prog_char n103[] PROGMEM = "pad = ";
    prog_char n104[] PROGMEM = "tier 0";
    prog_char n105[] PROGMEM = "tier 1";
    prog_char n106[] PROGMEM = "tier 2";

    const char *strTb[] PROGMEM = {
          n00, n01, n02, n03, n04, n05, n06, n07, n08, n09
        , n10, n11, n12, n13, n14, n15, n16, n17, n18, n19
        , n20, n21, n22, n23, n24, n25, n26, n27, n28, n29
        , n30, n31, n32, n33, n34, n35, n36, n37, n38, n39
        , n40, n41, n42, n43, n44, n45, n46, n47, n48, n49
        , n50, n51, n52, n53, n54, n55, n56, n57, n58, n59
        , n60, n61, n62, n63, n64, n65, n66, n67, n68, n69
        , n70, n71, n72, n73, n74, n75, n76, n77, n78, n79
        , n80, n81, n82, n83, n84, n85, n86, n87, n88, n89
        , n90, n91, n92, n93, n94, n95, n96, n97, n98, n99
        , n100,n101,n102,n103,n104,n105,n106//, n107, n108, n109
    };

    char * get(byte i)
    {
        strcpy_P(buffer, (char*)pgm_read_word(&strTb[i]));
        return buffer;
    }
}

#endif //__PROGMEM_KEYS_HEADER
