#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <U8g2lib.h>
#include "assets/icons/icons.h"

class Menu_Item {
    public:
        void draw(U8G2 &u8g2, const char * text, uint8_t icon_index, const uint8_t * font, uint8_t index);

    private:
        void text_prepare(U8G2 &u8g2, const uint8_t * font, int drawColorState);
};

#endif

