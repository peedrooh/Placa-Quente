#include <Arduino.h>
#include <U8g2lib.h>

// #include "models/menu/menu.h"
#include "models/rotary_switch/rotary_switch.h"
#include "assets/big_numbers/big_numbers.h"
#include "models/const_temp/const_temp.h"
#include "models/back_button/back_button.h"
#include "models/gen_reflow/gen_reflow.h"
#include "models/timer/timer.h"
#include "models/config/config.h"

#include "views/menu/menu_view.h"

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


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

RotarySwitch* r_switch = new RotarySwitch(RS_DT_PIN, RS_CLK_PIN, RS_SWITCH_PIN);

BackButton* back_button = new BackButton(BACK_BUTTON);

// Menu* menu = new Menu();

ConstTemp* const_temp = new ConstTemp(555);
GenericReflow* gen_relow = new GenericReflow();
Timer* timer = new Timer();
Config* config = new Config();

int click_counter = 0;
uint8_t current_view = 0;
byte screen_state = 0;

void setup(void) {
    
    // ConstTemp knda(444);
    // knda.draw(u8g2, 1, 1);

    u8g2.begin();
    
    r_switch->begin();
    back_button->begin();
    Serial.begin(115200);
    // Put current pins state in variables
    pinMode(RS_DT_PIN, INPUT);
    pinMode(RS_CLK_PIN, INPUT);

    // Set the Switch pin to use Arduino PULLUP resistors
    pinMode(RS_SWITCH_PIN, INPUT_PULLUP);

    // Set the Back button pin to input
    pinMode(BACK_BUTTON, INPUT);
}
byte was_answered = 0;
float temperature = 20;
void loop(void) {
    
    // r_switch->turn_detect();
    // if(r_switch->counter > 3) r_switch->counter--;
    // if(r_switch->counter <= -1) r_switch->counter++;
    // u8g2.clearBuffer();
    // config->draw_config_menu(u8g2, r_switch->counter);
    // u8g2.sendBuffer();

    switch (current_view) {
        case 0:
            was_answered = 0;
            show_menu(current_view, r_switch, u8g2);
            break;
        
        case 1:
            if(click_counter > 0) {
                r_switch->turn_detect();
                if(r_switch->counter > 9) r_switch->counter--;
                if(r_switch->counter <= -1) r_switch->counter++;
            }
            if(r_switch->get_switch_state()) {
                int t = const_temp->get_temperature();
                int hundreds = (int) t/100;
                int decimals = (int) (t - hundreds*100)/10;
                int units = (int) (t - (hundreds*100) - (decimals*10));

                if(click_counter == 2) r_switch->counter = hundreds;
                if(click_counter == 3) r_switch->counter = decimals;
                if(click_counter == 0) r_switch->counter = units;
                click_counter--;
            }
            if(click_counter < 0) click_counter = 3;

            u8g2.clearBuffer();
            const_temp->draw(u8g2, click_counter, r_switch->counter);
            u8g2.sendBuffer();
            if(back_button->is_clicked()) {
                current_view--;
            }
            break;
        
        case 2:
                   
            r_switch->turn_detect();
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
                timer->draw_set_temp_screen(u8g2, r_switch->counter);
                u8g2.sendBuffer();
            } else if(timer->get_timer_screen() == 2) {
                if(back_button->is_clicked()) current_view = 0;
                double temperature = 100.0;

                uint8_t* time = timer->get_time();
                
                u8g2.clearBuffer();
                timer->draw_timer_screen(u8g2, temperature, time);
                u8g2.sendBuffer();
            }
            
            break;
        
        case 3: {
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
                gen_relow->reset_graph();
                u8g2.clearBuffer();
                gen_relow->draw_temp_graph(u8g2);
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

                    gen_relow->add_point_in_graph(i, temperature);

                    u8g2.clearBuffer();
                    gen_relow->draw_temp_graph(u8g2);
                    u8g2.sendBuffer();
                    delay(100);
                }
                delay(3000);
                current_view = 0;
            } else {
                u8g2.clearBuffer();
                gen_relow->draw_confirmation_screen(u8g2, answer);
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
        }break;

        case 5:
            r_switch->turn_detect();
            if(r_switch->counter >= 3) r_switch->counter = 2;
            if(r_switch->counter <= -1) r_switch->counter = 0;
            u8g2.clearBuffer();
            config->draw_config_menu(u8g2, r_switch->counter);
            u8g2.sendBuffer();
            if(back_button->is_clicked()) {
                current_view--;
            }
            break;

        default:
            show_menu(current_view, r_switch, u8g2);
            break;
    }

    

    // BASIC IMPLEMENTATION OF THE CONSTANT TEMPERATURE VIEW
    // -----------------------------------------------------
    // if(click_counter > 0) {
    //     r_switch->turn_detect();
    //     if(r_switch->counter >= 9) r_switch->counter--;
    //     if(r_switch->counter <= 0) r_switch->counter++;
    // }
    // if(r_switch->get_switch_state()) {
    //     click_counter--;
    // }
    // if(click_counter < 0) click_counter = 3;

    // u8g2.clearBuffer();
    // const_temp->draw(u8g2, click_counter, r_switch->counter);
    // u8g2.sendBuffer();
    // ----------------------------------------------------


    // BASIC IMPLEMETATION OF THE MAIN MENU VIEW
    // ----------------------------------------------------

    // if(r_switch->get_switch_state()) screen_state = !screen_state;
    
    // if(screen_state) {
    //     switch (r_switch->counter) {
    //         case 1:
    //             u8g2.clearBuffer();
    //             const_temp->draw(u8g2, 0, 0);
    //             u8g2.sendBuffer();
    //             break;
    //         case 2:
    //             u8g2.clearBuffer();
    //             u8g2.drawStr(30, 30, "Temporizador");
    //             u8g2.sendBuffer();
    //             break;
    //         case 3:
    //             u8g2.clearBuffer();
    //             u8g2.drawStr(30, 30, "Refluxo Genérico");
    //             u8g2.sendBuffer();
    //             break;
    //         case 4:
    //             u8g2.clearBuffer();
    //             u8g2.drawStr(30, 30, "Refluxo Personalizado");
    //             u8g2.sendBuffer();
    //             break;
    //         case 5:
    //             u8g2.clearBuffer();
    //             u8g2.drawStr(30, 30, "Configuracoes");
    //             u8g2.sendBuffer();
    //             break;
    //     }
    //     // delay(5000);
    // } else {
    //     r_switch->turn_detect();

    //     if(r_switch->counter >= 6) r_switch->counter--;
    //     if(r_switch->counter <= 0) r_switch->counter++;
    //     u8g2.clearBuffer();
    //     menu->draw(u8g2, r_switch->counter);
    //     u8g2.sendBuffer();
    // }
    // ----------------------------------------------------
};
