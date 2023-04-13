#ifndef MENU_H
#define MENU_H

#include <U8g2lib.h>
#include "models/menu/menu_item.h"


#define font_primary u8g2_font_haxrcorp4089_tr
#define font_focus u8g2_font_helvB08_tr

#define NUM_MENU_ITEMS 6

class Menu {
    public:
        void draw_srcrollbar(U8G2 &u8g2, int current_item);
        void draw_focus_item(U8G2 &u8g2);
        void draw(U8G2 &u8g2, int current_item);

    private:
        uint8_t icons_indexes[NUM_MENU_ITEMS+1] = {
            5,
            8, 
            7, 
            4, 
            3, 
            6,
            12
        };
        const char * menu_titles[NUM_MENU_ITEMS+1] = {
            "Menu Principal", 
            "Temp. Constante", 
            "Temporizador", 
            "Refluxo Gen.",
            "Refluxo Per.",
            "Configuracoes", 
            ""
        };
};

#endif