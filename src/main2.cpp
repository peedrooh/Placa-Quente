// #include <Arduino.h>
// #include <U8g2lib.h>
// #include "FS.h"
// #include "SPIFFS.h"

// // #include "models/menu/menu.h"
// // #include "models/const_temp/const_temp.h"
// #include "models/rotary_switch/rotary_switch.h"
// #include "assets/big_numbers/big_numbers.h"
// #include "models/back_button/back_button.h"
// #include "models/gen_reflow/gen_reflow.h"
// #include "models/timer/timer.h"
// #include "models/config/config.h"
// #include "models/config_file/config_file.h"
// #include "models/temp_sensor/temp_sensor.h"

// #include "views/menu/menu_view.h"
// #include "views/cont_temp/const_temp_view.h"

// #ifdef U8X8_HAVE_HW_SPI
// #include <SPI.h>
// #endif
// #ifdef U8X8_HAVE_HW_I2C
// #include <Wire.h>
// #endif

// #define RS_SWITCH_PIN 33
// #define RS_DT_PIN 25
// #define RS_CLK_PIN 26
// #define BACK_BUTTON 5
// #define OLED_I2C_ADDR 0x3C


// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// RotarySwitch* r_switch = new RotarySwitch(RS_DT_PIN, RS_CLK_PIN, RS_SWITCH_PIN);

// BackButton* back_button = new BackButton(BACK_BUTTON);

// // Menu* menu = new Menu();
// // ConstTemp* const_temp = new ConstTemp(555);

// GenericReflow* gen_relow = new GenericReflow();
// Timer* timer = new Timer();
// Config* config = new Config();
// ConfigFile* config_file = new ConfigFile();

// // int click_counter = 0;
// uint8_t current_view = 0;
// byte screen_state = 0;

// void setup(void) {

//     u8g2.setI2CAddress(2*0x3C);
//     u8g2.begin();
        
//     r_switch->begin();
//     back_button->begin();
//     Serial.begin(115200);

//     // config_file->begin();
//     // // config_file->_read_file(config_file->_file_name);
//     // config_file->update_config(config_file->get_configs(load_control)[2], 1);
//     // config_file->update_config(config_file->get_configs(load_control)[1], 1);
//     // config_file->update_config(config_file->get_configs(load_control)[0], 0);
//     // config_file->_read_file(config_file->_file_name);
//     // ConfigItem *item = config_file->get_configs(load_control);
//     // Serial.println(item[1].is_selected);

//     // Put current pins state in variables
//     pinMode(RS_DT_PIN, INPUT);
//     pinMode(RS_CLK_PIN, INPUT);

//     // Set the Switch pin to use Arduino PULLUP resistors
//     pinMode(RS_SWITCH_PIN, INPUT_PULLUP);

//     // Set the Back button pin to input
//     pinMode(BACK_BUTTON, INPUT);
// }
// byte was_answered = 0;
// float temperature = 20;
// void loop(void) {

//     // r_switch->turn_detect();
//     // if(r_switch->counter > 2) r_switch->counter--;
//     // if(r_switch->counter <= -1) r_switch->counter++;
//     // if(r_switch->get_switch_state()) {
//     //     for(int i = 0; i < 3; i++) {
//     //         config->config_items[2][i].is_selected = false;
//     //         if(i == r_switch->counter) config->config_items[2][i].is_selected = true;
//     //     }
//     // }
//     // u8g2.clearBuffer();
//     // Serial.println(r_switch->counter);
//     // config->draw_config_selector(u8g2, 2, r_switch->counter);
//     // u8g2.sendBuffer();

//     switch (current_view) {
//         case 0:
//             was_answered = 0;
//             show_menu(current_view, r_switch, u8g2);
//             break;
        
//         case 1:
//             show_const_temp(current_view, r_switch, back_button, u8g2, config);
//             break;
        
//         case 2:
                   
//             r_switch->turn_detect();
//             if(r_switch->counter > 12) r_switch->counter--;
//             if(r_switch->counter <= -1) r_switch->counter++;
//             if(timer->get_timer_screen() == 0) {
//                 if(back_button->is_clicked()) current_view = 0;
//                 if(r_switch->get_switch_state()) {
//                     if(r_switch->counter == 12) timer->set_timer_screen(1);
//                     uint8_t key = timer->get_key(r_switch->counter);
//                     timer->set_cursor_index(key, 1);
//                     if (r_switch->counter > 1 && r_switch->counter < 12) {
//                         uint8_t* sec_min = timer->get_time();
//                         int time_split_in_digits[4] = {
//                             sec_min[0]%10,
//                             sec_min[0]/10,
//                             sec_min[1]%10,
//                             sec_min[1]/10
//                         };
//                         if(timer->get_cursor_index() == 0) time_split_in_digits[0] = key;
//                         if(timer->get_cursor_index() == 1 && key < 6) time_split_in_digits[1] = key;
//                         if(timer->get_cursor_index() == 2) time_split_in_digits[2] = key;
//                         if(timer->get_cursor_index() == 3 && key < 6) time_split_in_digits[3] = key;

//                         timer->set_time(time_split_in_digits[2] + (10*time_split_in_digits[3]), time_split_in_digits[0] + (10*time_split_in_digits[1]));
//                     }
//                 } 
//                 u8g2.clearBuffer();
//                 timer->draw_set_time_screen(u8g2, r_switch->counter);
//                 u8g2.sendBuffer();
//             } else if(timer->get_timer_screen() == 1) {
//                 if(back_button->is_clicked()) timer->set_timer_screen(0);
//                 if(r_switch->get_switch_state()) {
//                     if(r_switch->counter == 12) timer->set_timer_screen(2);
//                     uint8_t key = timer->get_key(r_switch->counter);
//                     timer->set_cursor_index(key, 0);
//                     if (r_switch->counter > 1 && r_switch->counter < 12) {
//                         uint8_t temp = timer->get_temp();
//                         int temp_split_in_digits[3] = {
//                             temp%10,
//                             (temp/10)%10,
//                             temp/100
//                         };
//                         if(timer->get_cursor_index() == 0) temp_split_in_digits[0] = key;
//                         if(timer->get_cursor_index() == 1) temp_split_in_digits[1] = key;
//                         if(timer->get_cursor_index() == 2 && key < 3) temp_split_in_digits[2] = key;

//                         timer->set_temp((100*temp_split_in_digits[2])+(10*temp_split_in_digits[1])+temp_split_in_digits[0]);
//                     }
//                 }
//                 u8g2.clearBuffer();
//                 timer->draw_set_temp_screen(u8g2, r_switch->counter);
//                 u8g2.sendBuffer();
//             } else if(timer->get_timer_screen() == 2) {
//                 if(back_button->is_clicked()) current_view = 0;
//                 double temperature = 100.0;

//                 uint8_t* time = timer->get_time();
                
//                 u8g2.clearBuffer();
//                 timer->draw_timer_screen(u8g2, temperature, time);
//                 u8g2.sendBuffer();
//             }
            
//             break;
        
//         case 3: {
//             byte answer = 0;

//             if(!was_answered) {
//                 r_switch->turn_detect();
//                 answer = 0;
//                 if(r_switch->counter % 2) {
//                     answer = 1;
//                 }
//             } 

//             if(was_answered) {
//                 temperature = 0;
//                 gen_relow->reset_graph();
//                 u8g2.clearBuffer();
//                 gen_relow->draw_temp_graph(u8g2);
//                 u8g2.sendBuffer();


//                 for(int i = 0; i < 330; i++) {
//                     if(back_button->is_clicked()) {
//                         current_view = 0;
//                         break;
//                     }
//                     if(i < 90) {
//                         temperature += 1.3;
//                     }else if(i > 90 && i < 180) {
//                         temperature += 0.3;
//                     }else if(i > 180 && i < 240) {
//                         temperature += 1;
//                     }else if(i > 240 && i < 280) {
//                         temperature  = temperature;
//                     } else {
//                         temperature = temperature - 2;
//                     }

//                     gen_relow->add_point_in_graph(i, temperature);

//                     u8g2.clearBuffer();
//                     gen_relow->draw_temp_graph(u8g2);
//                     u8g2.sendBuffer();
//                     delay(100);
//                 }
//                 delay(3000);
//                 current_view = 0;
//             } else {
//                 u8g2.clearBuffer();
//                 gen_relow->draw_confirmation_screen(u8g2, answer);
//                 u8g2.sendBuffer();
//             }

//             if(back_button->is_clicked()) {
//                 current_view = 0;
//             }
//             if(r_switch->get_switch_state()) {
//                 if(answer == 0 && !was_answered) {
//                     current_view = 0;
//                 } else {
//                     was_answered = 1;
//                 }
//             }
//         }break;

//         case 5:
//             r_switch->turn_detect();
//             if(r_switch->counter >= 3) r_switch->counter = 2;
//             if(r_switch->counter <= -1) r_switch->counter = 0;
//             u8g2.clearBuffer();
//             config->draw_config_menu(u8g2, r_switch->counter);
//             u8g2.sendBuffer();
//             if(back_button->is_clicked()) {
//                 current_view--;
//             }
//             break;

//         default:
//             show_menu(current_view, r_switch, u8g2);
//             break;
//     }
// };












// void setup() {
//     Serial.begin(115200);
//     Serial.println(F("I2C test"));

//     Wire.begin();
//     // Wire1.begin(SDA_2, SCL_2);
//     u8g2.setI2CAddress(2*0x3C);
//     u8g2.begin();
//     // if(!u8g2.begin()) {

//     //     Serial.println("Error connecting to OLEDdisplay. Check wiring.");
//     //     while(1);
//     // }

//     // if(!mlx.begin(0x5A, &Wire1)) {
//     //     Serial.println("Error connecting to MLX sensor. Check wiring.");
//     //     while(1);
//     // }

//     Serial.println();
// }

// void loop() {

//     u8g2.clearBuffer();
//     u8g2.setBitmapMode(true);
//     u8g2.setFont(u8g2_font_haxrcorp4089_tr);
//     u8g2.setFontRefHeightExtendedText();
//     u8g2.setDrawColor(1);
//     u8g2.setFontPosTop();
//     u8g2.setFontDirection(0);
//     u8g2.drawStr(6, 0, "T. Const");
//     u8g2.sendBuffer();

//     // double temp = mlx.readObjectTempC();
//     // Serial.println(temp);
//     // delay(1000);
// }