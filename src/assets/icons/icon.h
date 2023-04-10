#ifndef ICON_H
#define ICON_H

#include <U8g2lib.h>

class Icon {
    private:
      const unsigned char * U8X8_PROGMEM _icon;

    public:
      uint8_t icon_height;
      uint8_t icon_width;

      Icon(const unsigned char * U8X8_PROGMEM icon, uint8_t width,  uint8_t height);
      const unsigned char * U8X8_PROGMEM get_icon();
};

#endif