#ifndef HEADER_H
#define HEADER_H

#include <U8g2lib.h>

class Header {
    private:
      const unsigned char * U8X8_PROGMEM _header;

    public:
      uint8_t header_height;
      uint8_t header_width;

      Header(const unsigned char * U8X8_PROGMEM header, uint8_t width,  uint8_t height);
      const unsigned char * U8X8_PROGMEM get_header();
};

#endif