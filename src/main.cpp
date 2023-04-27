#include <Arduino.h>
#include <U8g2lib.h>

// #include "models/menu/menu.h"
#include "models/rotary_switch/rotary_switch.h"
#include "assets/big_numbers/big_numbers.h"
#include "models/const_temp/const_temp.h"
#include "models/back_button/back_button.h"

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

int click_counter = 0;
uint8_t current_view = 0;
byte screen_state = 0;

void setup(void) {
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

void loop(void) {

    switch (current_view) {
        case 0:
            show_menu(current_view, r_switch, u8g2);
            break;
        
        case 1:
            if(click_counter > 0) {
                r_switch->turn_detect();
                if(r_switch->counter > 9) r_switch->counter--;
                if(r_switch->counter <= 0) r_switch->counter++;
            }
            if(r_switch->get_switch_state()) {
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
