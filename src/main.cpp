#include <Arduino.h>
#include <U8g2lib.h>

#include "models/menu/menu.h"
#include "models/rotary_switch/rotary_switch.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define RS_SWITCH_PIN 33
#define RS_DT_PIN 25
#define RS_CLK_PIN 26


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

Rotary_Switch* r_switch = new Rotary_Switch(RS_DT_PIN, RS_CLK_PIN, RS_SWITCH_PIN);

Menu* menu = new Menu();

void setup(void) {
    u8g2.begin();
    
    r_switch->begin();
    // Serial.begin(115200);
    // Put current pins state in variables
    pinMode(RS_DT_PIN, INPUT);
    pinMode(RS_CLK_PIN, INPUT);

    // // Set the Switch pin to use Arduino PULLUP resistors
    // pinMode(RS_SWITCH_PIN, INPUT_PULLUP);
}

void loop(void) {

    r_switch->turn_detect();

    if(r_switch->counter >= 6) r_switch->counter--;
    if(r_switch->counter <= 0) r_switch->counter++;
    u8g2.clearBuffer();
    menu->draw(u8g2, r_switch->counter);
    u8g2.sendBuffer();
    
    if(r_switch->get_switch_state()) {
        switch (r_switch->counter) {
            case 1:
                u8g2.clearBuffer();
                u8g2.drawStr(30, 30, "Temp. Constante");
                u8g2.sendBuffer();
                break;
            case 2:
                u8g2.clearBuffer();
                u8g2.drawStr(30, 30, "Temporizador");
                u8g2.sendBuffer();
                break;
            case 3:
                u8g2.clearBuffer();
                u8g2.drawStr(30, 30, "Refluxo Genérico");
                u8g2.sendBuffer();
                break;
            case 4:
                u8g2.clearBuffer();
                u8g2.drawStr(30, 30, "Refluxo Personalizado");
                u8g2.sendBuffer();
                break;
            case 5:
                u8g2.clearBuffer();
                u8g2.drawStr(30, 30, "Configuracoes");
                u8g2.sendBuffer();
                break;
        }
        delay(5000);
    }


    // for(int i = 0; i < 6; i++) {
    //     u8g2.clearBuffer();
    //     menu->draw(u8g2, i);
    //     u8g2.sendBuffer();
    //     delay(500);
    // }

    // for(int i = 5; i > 0; i--) {
    //     u8g2.clearBuffer();
    //     menu->draw(u8g2, i);
    //     u8g2.sendBuffer();
    //     delay(500);
    // }
};