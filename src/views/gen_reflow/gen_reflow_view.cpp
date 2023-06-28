#include "gen_reflow_view.h"

GenericReflow* gen_reflow = new GenericReflow();
HeatPlate* heat_plate_gr = new HeatPlate();

byte was_answered = 0;

float temperature = 20;
double curr_time_gr = millis();
double prev_time_gr = curr_time_gr;
int elapsed_time_gr = 0;

extern void show_gen_reflow(uint8_t &current_view, Adafruit_MLX90614 &temp_sensor, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2, Config* &config) {
    byte answer = 0;
    byte is_full_cicle_gr = config->config_items[1][0].is_selected;
    byte is_celcius_gr = config->config_items[0][0].is_selected;

    if(!was_answered) {
        r_switch->turn_detect();
        answer = 0;
        if(r_switch->counter % 2) {
            answer = 1;
        }
    } 

    if(was_answered) {
        temperature = temp_sensor.readObjectTempC();
        elapsed_time_gr = 0;

        gen_reflow->reset_graph();

        u8g2.clearBuffer();
        gen_reflow->draw_temp_graph(u8g2, is_celcius_gr);
        u8g2.sendBuffer();

        while(elapsed_time_gr < 90) {
            curr_time_gr = millis();
            if(back_button->is_clicked()) {
                current_view = 0;
                break;
            }
            if (curr_time_gr - prev_time_gr >= 1000) {
                prev_time_gr = curr_time_gr;
                elapsed_time_gr++;

                temperature = temp_sensor.readObjectTempC();

                gen_reflow->add_point_in_graph(elapsed_time_gr, temperature);

                u8g2.clearBuffer();
                gen_reflow->draw_temp_graph(u8g2, is_celcius_gr);
                u8g2.sendBuffer();
            }
            if(temperature >= 140) heat_plate_gr->turn_on(is_full_cicle_gr, 0);
            else heat_plate_gr->turn_on(is_full_cicle_gr, 40);
        }

        while(elapsed_time_gr < 180) {
            curr_time_gr = millis();
            if(back_button->is_clicked()) {
                current_view = 0;
                break;
            }
            if (curr_time_gr - prev_time_gr >= 1000) {
                prev_time_gr = curr_time_gr;
                elapsed_time_gr++;

                temperature = temp_sensor.readObjectTempC();

                gen_reflow->add_point_in_graph(elapsed_time_gr, temperature);

                u8g2.clearBuffer();
                gen_reflow->draw_temp_graph(u8g2, is_celcius_gr);
                u8g2.sendBuffer();
            }
            if(temperature >= 180) heat_plate_gr->turn_on(is_full_cicle_gr, 0);
            else heat_plate_gr->turn_on(is_full_cicle_gr, 20);
        }

        while(elapsed_time_gr < 245) {
            curr_time_gr = millis();
            if(back_button->is_clicked()) {
                current_view = 0;
                break;
            }
            if (curr_time_gr - prev_time_gr >= 1000) {
                prev_time_gr = curr_time_gr;
                elapsed_time_gr++;

                temperature = temp_sensor.readObjectTempC();

                gen_reflow->add_point_in_graph(elapsed_time_gr, temperature);

                u8g2.clearBuffer();
                gen_reflow->draw_temp_graph(u8g2, is_celcius_gr);
                u8g2.sendBuffer();
            }
            heat_plate_gr->turn_on(is_full_cicle_gr, 100);
        }

        while(elapsed_time_gr < 270) {
            curr_time_gr = millis();
            if(back_button->is_clicked()) {
                current_view = 0;
                break;
            }
            if (curr_time_gr - prev_time_gr >= 1000) {
                prev_time_gr = curr_time_gr;
                elapsed_time_gr++;

                temperature = temp_sensor.readObjectTempC();

                gen_reflow->add_point_in_graph(elapsed_time_gr, temperature);

                u8g2.clearBuffer();
                gen_reflow->draw_temp_graph(u8g2, is_celcius_gr);
                u8g2.sendBuffer();
            }
        }
        delay(5000);
        current_view = 0;
    } else {
        u8g2.clearBuffer();
        gen_reflow->draw_confirmation_screen(u8g2, answer);
        u8g2.sendBuffer();
    }
    
    if(back_button->is_clicked()) {
        current_view = 0;
    }
    if(r_switch->get_switch_state()) {
        if(answer == 0 && !was_answered) {
            current_view = 0;
        } else {
            was_answered = 1;
        }
    }
}