#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <U8g2lib.h>

class BigNum {
    private:
      const unsigned char * U8X8_PROGMEM _big_num;

    public:
      uint8_t big_num_height;
      uint8_t big_num_width;

      BigNum(const unsigned char * U8X8_PROGMEM big_num, uint8_t width,  uint8_t height);
      const unsigned char * U8X8_PROGMEM get_big_num();
};

#endif