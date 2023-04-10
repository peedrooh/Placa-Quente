#include "Icon.h"

Icon::Icon(const unsigned char * U8X8_PROGMEM icon, uint8_t width,  uint8_t height) {
    this->_icon = icon;
    this->icon_height = height;
    this->icon_width = width;
};

const unsigned char * U8X8_PROGMEM Icon::get_icon() {
    return this->_icon;
};