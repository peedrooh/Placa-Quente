#include "menu_view.h"

Menu* menu = new Menu();

extern void show_menu(uint8_t &current_view, RotarySwitch* &r_switch, U8G2 &u8g2) {
    r_switch->turn_detect();

    if(r_switch->counter >= 6) r_switch->counter--;
    if(r_switch->counter <= 0) r_switch->counter++;

    u8g2.clearBuffer();
    menu->draw(u8g2, r_switch->counter);
    u8g2.sendBuffer();

    if(r_switch->get_switch_state()) current_view = r_switch->counter;
}