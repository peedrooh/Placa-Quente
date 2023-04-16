#ifndef ROTARY_SWITCH_H
#define ROTARY_SWITCH_H

#include <Arduino.h>

class Rotary_Switch {
    public: 
        Rotary_Switch(int data_pin, int clock_pin, int switch_pin);
        void begin();
        void turn_detect();
        int counter;
        byte was_clicked;
        byte get_switch_state();
    private:
        uint8_t _DATA_PIN;
        uint8_t _CLOCK_PIN;
        uint8_t _SWITCH_PIN;
        void _check_states();
        byte _PDT; // previous data state
        byte _DT; // current data state
        byte _PCLK; // previous clock state
        byte _CLK; // current clock state
        byte _is_clockwise; // rotation state
        byte _turnDetect; // stores if the rotary switch rotated
        byte _prev_turnDetect; // previous rotation state
        long _last_debounce_time = 0; 
        uint8_t _debounce_delay = 10;
        uint8_t _clock_ticks = 0; // sum of clocks occured in one single debounce time
};

#endif