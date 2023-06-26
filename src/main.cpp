#include <Arduino.h>
#include <U8g2lib.h>
#include "FS.h"
#include "SPIFFS.h"

#include "models/rotary_switch/rotary_switch.h"
#include "models/back_button/back_button.h"
#include "models/temp_sensor/temp_sensor.h"
#include "models/config/config.h"
#include "models/config_file/config_file.h"

#include "views/menu/menu_view.h"
#include "views/cont_temp/const_temp_view.h"
#include "views/timer/timer_view.h"
#include "views/gen_reflow/gen_reflow_view.h"
#include "views/config/config_view.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define RS_SWITCH_PIN 33
#define RS_DT_PIN 25
#define RS_CLK_PIN 26
#define BACK_BUTTON 5
#define OLED_I2C_ADDR 0x3C


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
RotarySwitch* r_switch = new RotarySwitch(RS_DT_PIN, RS_CLK_PIN, RS_SWITCH_PIN);
BackButton* back_button = new BackButton(BACK_BUTTON);
TempSensor* temp_sensor = new TempSensor();

Config* config = new Config();
ConfigFile* config_file = new ConfigFile();

uint8_t current_view = 0;

void setup(void) {
    Serial.begin(115200);

    temp_sensor->begin();

    // u8g2.setI2CAddress(2*0x3C);
    // u8g2.begin();
        
    r_switch->begin();
    back_button->begin();

    // config_file->begin();
    // // config_file->_read_file(config_file->_file_name);
    // config_file->update_config(config_file->get_configs(load_control)[2], 1);
    // config_file->update_config(config_file->get_configs(load_control)[1], 1);
    // config_file->update_config(config_file->get_configs(load_control)[0], 0);
    // config_file->_read_file(config_file->_file_name);
    // ConfigItem *item = config_file->get_configs(load_control);
    // Serial.println(item[1].is_selected);

    // Put current pins state in variables
    pinMode(RS_DT_PIN, INPUT);
    pinMode(RS_CLK_PIN, INPUT);

    // Set the Switch pin to use Arduino PULLUP resistors
    pinMode(RS_SWITCH_PIN, INPUT_PULLUP);

    // Set the Back button pin to input
    pinMode(BACK_BUTTON, INPUT);
}

void loop(void) {

    show_const_temp(current_view, temp_sensor, r_switch, back_button, u8g2, config);

    // switch (current_view) {
    //     case 0:
    //         show_menu(current_view, r_switch, u8g2);
    //         break;
        
    //     case 1:
    //         show_const_temp(current_view, temp_sensor, r_switch, back_button, u8g2, config);
    //         break;
        
    //     case 2:
    //         show_timer(current_view, temp_sensor, r_switch, back_button, u8g2, config);
    //         break;
        
    //     case 3: 
    //         show_gen_reflow(current_view, temp_sensor, r_switch, back_button, u8g2, config);
    //         break;

    //     case 5:
    //         show_config(current_view, r_switch, back_button, u8g2, config);
    //         break;

    //     default:
    //         show_menu(current_view, r_switch, u8g2);
    //         break;
    // }
};
