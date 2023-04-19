#include "big_number.h"

BigNum::BigNum(const unsigned char * U8X8_PROGMEM big_num, uint8_t width,  uint8_t height) {
    this->_big_num = big_num;
    this->big_num_height = height;
    this->big_num_width = width;
};

const unsigned char * U8X8_PROGMEM BigNum::get_big_num() {
    return this->_big_num;
};