#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "models/menu/menu.h"
#include "models/back_button/back_button.h"
#include "models/rotary_switch/rotary_switch.h"

extern void show_menu(uint8_t &current_view, RotarySwitch* &r_switch, U8G2 &u8g2);

#endif