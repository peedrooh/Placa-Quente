#include "number.h"

Number::Number(const unsigned char * U8X8_PROGMEM number, uint8_t width,  uint8_t height) {
    this->_number = number;
    this->number_height = height;
    this->number_width = width;
};

const unsigned char * U8X8_PROGMEM Number::get_number() {
    return this->_number;
};