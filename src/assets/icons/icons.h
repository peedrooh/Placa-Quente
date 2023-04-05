#ifndef ICONS_H
#define ICONS_H
#include <Arduino.h>

class Icons {
    public:
        const unsigned char PROGMEM * icon_arrow_left();
        const unsigned char PROGMEM * icon_arrow_right();
        const unsigned char PROGMEM * icon_back();
        const unsigned char PROGMEM * icon_cus_reflow();
        const unsigned char PROGMEM * icon_gen_reflow();
        const unsigned char PROGMEM * icon_menu();
        const unsigned char PROGMEM * icon_settings();
        const unsigned char PROGMEM * icon_t_const();
        const unsigned char PROGMEM * icon_t_cooling();
        const unsigned char PROGMEM * icon_t_heating_1();
        const unsigned char PROGMEM * icon_t_heating_2();
        const unsigned char PROGMEM * icon_timer();
};

#endif