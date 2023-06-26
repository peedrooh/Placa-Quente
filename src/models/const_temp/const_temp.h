#ifndef CONST_TEMP_H
#define CONST_TEMP_H

#include "assets/headers/headers.h"
#include "models/config/config.h"
#include <U8g2lib.h>

class ConstTemp {
    public:
        ConstTemp(int temperature);
        void draw(U8G2 &u8g2, uint8_t digit_index, uint8_t counter, byte is_heating, Config* &config);
        int get_temperature();
        void set_temperature(int temperature);
    private:
        void _draw_header(U8G2 &u8g2);
        void _draw_icon(U8G2 &u8g2, byte is_heating);
        void _draw_unit(U8G2 &u8g2, byte is_celcius);
        void _draw_focus(U8G2 &u8g2);
        void _draw_big_digit(U8G2 &u8g2, uint8_t digit_index, uint8_t digit, byte is_bk_white);
        int _temperature;
};

#endif