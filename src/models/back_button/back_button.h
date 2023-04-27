#ifndef BACK_BUTTON_H
#define BACK_BUTTON_H


#include <Arduino.h>

class BackButton {
    public:
        bool is_clicked();
        void begin();
        BackButton(uint8_t pin);
    private:
        uint8_t _pin;
        uint8_t _debounce_time;
};

#endif