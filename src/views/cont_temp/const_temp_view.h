#ifndef CONST_TEMP_VIEW
#define CONST_TEMP_VIEW

#include "models/const_temp/const_temp.h"
#include "models/rotary_switch/rotary_switch.h"
#include "models/back_button/back_button.h"
#include "models/PID/PID.h"
#include "models/heat_plate/heat_plate.h"

extern void show_const_temp(uint8_t &current_view, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2);

#endif