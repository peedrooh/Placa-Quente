#include "back_button.h"

BackButton::BackButton(uint8_t pin) {
    this->_pin = pin;
    this->_debounce_time = 150;
}

void BackButton::begin() {
    pinMode(this->_pin, INPUT);
}

bool BackButton::is_clicked() {
    if(digitalRead(this->_pin)) {
        return false;
    }

    delay(this->_debounce_time);
    return true;
}