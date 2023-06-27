#ifndef TIMER_VIEW_H
#define TIMER_VIEW_H

#include "Adafruit_MLX90614.h"

#include "models/timer/timer.h"
#include "models/rotary_switch/rotary_switch.h"
#include "models/back_button/back_button.h"
#include "models/PID/PID.h"
#include "models/heat_plate/heat_plate.h"
#include "models/config/config.h"

extern void show_timer(uint8_t &current_view, Adafruit_MLX90614 &temp_sensor, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2, Config* &config);

#endif