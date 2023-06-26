#include "timer_view.h"

Timer* timer = new Timer();
HeatPlate* heat_plate_tm = new HeatPlate();
PIDController* pid_tm = new PIDController(0.5, 0.1, 0.2, 100, 0, 100);

extern void show_timer(uint8_t &current_view, TempSensor* &temp_sensor, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2, Config* &config) {
    r_switch->turn_detect();
    // r_switch->counter =12;
    if(r_switch->counter > 12) r_switch->counter--;
    if(r_switch->counter <= -1) r_switch->counter++;
    if(timer->get_timer_screen() == 0) {
        if(back_button->is_clicked()) current_view = 0;
        if(r_switch->get_switch_state()) {
            if(r_switch->counter == 12) timer->set_timer_screen(1);
            uint8_t key = timer->get_key(r_switch->counter);
            timer->set_cursor_index(key, 1);
            if (r_switch->counter > 1 && r_switch->counter < 12) {
                uint8_t* sec_min = timer->get_time();
                int time_split_in_digits[4] = {
                    sec_min[0]%10,
                    sec_min[0]/10,
                    sec_min[1]%10,
                    sec_min[1]/10
                };
                if(timer->get_cursor_index() == 0) time_split_in_digits[0] = key;
                if(timer->get_cursor_index() == 1 && key < 6) time_split_in_digits[1] = key;
                if(timer->get_cursor_index() == 2) time_split_in_digits[2] = key;
                if(timer->get_cursor_index() == 3 && key < 6) time_split_in_digits[3] = key;

                timer->set_time(time_split_in_digits[2] + (10*time_split_in_digits[3]), time_split_in_digits[0] + (10*time_split_in_digits[1]));
            }
        } 
        u8g2.clearBuffer();
        timer->draw_set_time_screen(u8g2, r_switch->counter);
        u8g2.sendBuffer();
    } else if(timer->get_timer_screen() == 1) {
        if(back_button->is_clicked()) timer->set_timer_screen(0);
        if(r_switch->get_switch_state()) {
            if(r_switch->counter == 12) timer->set_timer_screen(2);
            uint8_t key = timer->get_key(r_switch->counter);
            timer->set_cursor_index(key, 0);
            if (r_switch->counter > 1 && r_switch->counter < 12) {
                uint8_t temp = timer->get_temp();
                int temp_split_in_digits[3] = {
                    temp%10,
                    (temp/10)%10,
                    temp/100
                };
                if(timer->get_cursor_index() == 0) temp_split_in_digits[0] = key;
                if(timer->get_cursor_index() == 1) temp_split_in_digits[1] = key;
                if(timer->get_cursor_index() == 2 && key < 3) temp_split_in_digits[2] = key;

                timer->set_temp((100*temp_split_in_digits[2])+(10*temp_split_in_digits[1])+temp_split_in_digits[0]);
            }
        }
        u8g2.clearBuffer();
        timer->draw_set_temp_screen(u8g2, r_switch->counter, config->config_items[0][0].is_selected);
        u8g2.sendBuffer();
    } else if(timer->get_timer_screen() == 2) {
        if(back_button->is_clicked()) current_view = 0;
        double temperature = timer->get_temp();

        uint8_t time_sec = timer->get_time()[0] + timer->get_time()[1]*60;
        uint8_t elapsed_time = 0;
        double curr_time = millis();
        double prev_time = curr_time;
        
        u8g2.clearBuffer();
        timer->draw_timer_screen(u8g2, temperature, (time_sec - elapsed_time)/60, (time_sec - elapsed_time)%60, config->config_items[0][0].is_selected);
        u8g2.sendBuffer();

        while (elapsed_time<time_sec) {
            if(back_button->is_clicked()) {
                current_view = 0;
                break;
            };
            curr_time = millis();

            // CONTROLE DE TEMPERATURA
            if(curr_time - prev_time >= 1000) {
                prev_time = curr_time;
                elapsed_time++;
                u8g2.clearBuffer();
                timer->draw_timer_screen(u8g2, temperature, (time_sec - elapsed_time)/60, (time_sec - elapsed_time)%60, config->config_items[0][0].is_selected);
                u8g2.sendBuffer();
            }
        }
        if(elapsed_time == time_sec) {
            current_view = 0;
        }
    }
}
