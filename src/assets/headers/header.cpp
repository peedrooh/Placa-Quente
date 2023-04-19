#include "header.h"

Header::Header(const unsigned char * U8X8_PROGMEM header, uint8_t width,  uint8_t height) {
    this->_header = header;
    this->header_height = height;
    this->header_width = width;
};

const unsigned char * U8X8_PROGMEM Header::get_header() {
    return this->_header;
};