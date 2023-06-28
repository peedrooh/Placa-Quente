#ifndef CONFIG_VIEW_H
#define CONFIG_VIEW_H

#include "models/config/config.h"
#include "models/rotary_switch/rotary_switch.h"
#include "models/back_button/back_button.h"
#include "models/PID/PID.h"
#include "models/heat_plate/heat_plate.h"
#include "models/config/config.h"
#include "models/temp_sensor/temp_sensor.h"
#include "models/config_file/config_file.h"

extern void show_config(uint8_t &current_view, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2, Config* &config, ConfigFile* &config_file);

#endif