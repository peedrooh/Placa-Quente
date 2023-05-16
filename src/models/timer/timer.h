#ifndef TIMER_H
#define TIMER_H

#include <U8g2lib.h>

class Timer {
    public:
        Timer();
        void draw_set_time_screen(U8G2 &u8g2, uint8_t keyboard_key_index);
        uint8_t* get_time();
        void set_time(uint8_t minutes, uint8_t seconds);
        uint8_t get_key(uint8_t index);
        void set_time_cursor_index(uint8_t keyboard_key);
        uint8_t get_time_cursor_index();
    private:
        uint8_t _keyboard_keys[13] = {11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        uint8_t _minutes;
        uint8_t _seconds;
        uint8_t _time_cursor_index;
        uint8_t _set_time_x_positions[4][2] = {{83, 80}, {72, 69}, {51, 48}, {40, 37} };
};

#endif