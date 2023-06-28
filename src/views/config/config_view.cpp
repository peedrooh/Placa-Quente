#include "config_view.h"


byte config_screen = 0;
uint8_t selected_config = 0;

extern void show_config(uint8_t &current_view, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2, Config* &config, ConfigFile* &config_file) {
    if(config_screen == 0) {
        r_switch->turn_detect();
        if(r_switch->counter > 1) r_switch->counter = 1;
        if(r_switch->counter <= -1) r_switch->counter = 0;
        selected_config = r_switch->counter;
        u8g2.clearBuffer();
        config->draw_config_menu(u8g2, r_switch->counter);
        u8g2.sendBuffer();
        if(r_switch->get_switch_state()) config_screen = 1;
        if(back_button->is_clicked()) current_view = 0;

    } else {
        r_switch->turn_detect();
        if(r_switch->counter > 1) r_switch->counter--;
        if(r_switch->counter <= -1) r_switch->counter++;
        if(r_switch->get_switch_state()) {
            for(int i = 0; i < 2; i++) {
                Serial.print(i);
                Serial.print("   ");
                Serial.println(selected_config);
                config->config_items[selected_config][i].is_selected = false;
                config_file->update_config(config->config_items[selected_config][i], 0);
                if(i == r_switch->counter) {
                    config->config_items[selected_config][i].is_selected = true;
                    config_file->update_config(config->config_items[selected_config][i], 1);
                }
            }
        }
        u8g2.clearBuffer();
        config->draw_config_selector(u8g2, selected_config, r_switch->counter);
        u8g2.sendBuffer();
        if(back_button->is_clicked()) config_screen = 0;
    }
}