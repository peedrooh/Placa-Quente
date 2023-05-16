#ifndef GEN_REFLOW_H
#define GEN_REFLOW_H

#include <U8g2lib.h>

class GenericReflow {
    public:
        void draw_confirmation_screen(U8G2 &u8g2, byte is_yes);
        void draw_temp_graph(U8G2 &u8g2);
        void add_point_in_graph(uint16_t time, float temperature);
        void reset_graph();
    private:
        void _draw_XY_axis(U8G2 &u8g2);
        void _draw_focus_answer(U8G2 &u8g2, uint8_t x, uint8_t y);
        float _points[330][2];
};

#endif