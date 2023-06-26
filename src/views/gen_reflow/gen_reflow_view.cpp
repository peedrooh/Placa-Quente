#include "gen_reflow_view.h"

GenericReflow* gen_reflow = new GenericReflow();

byte was_answered = 0;

float temperature = 20;

extern void show_gen_reflow(uint8_t &current_view, TempSensor* &temp_sensor, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2, Config* &config) {
    byte answer = 0;

    if(!was_answered) {
        r_switch->turn_detect();
        answer = 0;
        if(r_switch->counter % 2) {
            answer = 1;
        }
    } 

    if(was_answered) {
        temperature = 0;
        gen_reflow->reset_graph();

        u8g2.clearBuffer();
        gen_reflow->draw_temp_graph(u8g2);
        u8g2.sendBuffer();

        for(int i = 0; i < 330; i++) {
            if(back_button->is_clicked()) {
                current_view = 0;
                break;
            }

            if(i < 90) {
                temperature += 1.3;
            }else if(i > 90 && i < 180) {
                temperature += 0.3;
            }else if(i > 180 && i < 240) {
                temperature += 1;
            }else if(i > 240 && i < 280) {
                temperature  = temperature;
            } else {
                temperature = temperature - 2;
            }

            gen_reflow->add_point_in_graph(i, temperature);

            u8g2.clearBuffer();
            gen_reflow->draw_temp_graph(u8g2);
            u8g2.sendBuffer();
            delay(100);
        }

        delay(2000);
        current_view = 0;
        was_answered = 0;
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