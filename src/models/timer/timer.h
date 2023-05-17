#ifndef TIMER_H
#define TIMER_H

#include <U8g2lib.h>

class Timer {
    public:
        Timer();
        void draw_set_time_screen(U8G2 &u8g2, uint8_t keyboard_key_index);
        void draw_set_temp_screen(U8G2 &u8g2, uint8_t keyboard_key_index);
        void draw_timer_screen(U8G2 &u8g2, double temperature, uint8_t* time);
        uint8_t* get_time();
        void set_time(uint8_t minutes, uint8_t seconds);
        uint8_t get_temp();
        void set_temp(uint8_t temperature);
        uint8_t get_key(uint8_t index);
        void set_cursor_index(uint8_t keyboard_key, byte is_set_time);
        uint8_t get_cursor_index();
        void set_timer_screen(uint8_t current_screen);
        uint8_t get_timer_screen();
    private:
        void _draw_keyboard(U8G2 &u8g2, uint8_t keyboard_key_index);
        void _draw_enter_and_back(U8G2 &u8g2, byte is_focused);
        void _draw_message(U8G2 &u8g2, const char *str);
        uint8_t _timer_screen;
        uint8_t _keyboard_keys[13] = {11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        uint8_t _minutes;
        uint8_t _seconds;
        uint8_t _temperature;
        uint8_t _cursor_index;
        // Array containing the string x position and highligth box x position for each number to set
        uint8_t _set_time_x_positions[4][2] = {{83, 80}, {72, 69}, {51, 48}, {40, 37} };
        uint8_t _set_temp_x_positions[3][2] = {{66, 63}, {54, 51}, {42, 39}};
};

#endif