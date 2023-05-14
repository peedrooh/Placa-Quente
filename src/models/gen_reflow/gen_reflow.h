#ifndef GEN_REFLOW_H
#define GEN_REFLOW_H

#include <U8g2lib.h>

class GenericReflow {
    public:
        void draw_confirmation_screen(U8G2 &u8g2, byte is_yes);
    private:
        void _draw_facus_answer(U8G2 &u8g2, uint8_t x, uint8_t y);
};

#endif