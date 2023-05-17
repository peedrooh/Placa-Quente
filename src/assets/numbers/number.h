#ifndef NUMBER_H
#define NUMBER_H

#include <U8g2lib.h>

class Number {
    private:
      const unsigned char * U8X8_PROGMEM _number;

    public:
      uint8_t number_height;
      uint8_t number_width;

      Number(const unsigned char * U8X8_PROGMEM number, uint8_t width,  uint8_t height);
      const unsigned char * U8X8_PROGMEM get_number();
};

#endif