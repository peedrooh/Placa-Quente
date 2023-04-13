#include <Arduino.h>
#include <U8g2lib.h>

#include "models/menu/menu.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define RS_SWITCH_PIN 6
#define RS_DT_PIN 7
#define RS_CLK_PIN 8
// Variables to debounce Rotary Encoder
long RS_last_debounce_time = 0;
int RS_debounce_delay = 5;
int RS_increment = 0;
bool turnDetect = false;
bool prev_turnDetect = false;

byte RS_PDT; 
byte RS_DT; 
byte RS_PCLK;
byte RS_CLK;
byte RS_is_clockwise;

int counter = 0;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


Menu* menu = new Menu();


void check_RS_states() {
    RS_CLK = digitalRead(RS_CLK_PIN);
    RS_DT = digitalRead(RS_DT_PIN);

    // Serial.print("----------- ");
    // Serial.print(counter);
    // Serial.println(" -----------");
    // Serial.println(" PDT | PCLK | INC | DT | CLK");
    // Serial.print("  ");
    // Serial.print(RS_PDT);
    // Serial.print("  |  ");
    // Serial.print(RS_PCLK);
    // Serial.print("   |  ");
    // Serial.print(RS_increment);
    // Serial.print("  |  ");
    // Serial.print(RS_DT);
    // Serial.print(" |  ");
    // Serial.println(RS_CLK);
    // Serial.println("");

    if(RS_increment != 1) {
        RS_increment = 0;
        return;
    }

    if(RS_PDT != RS_PCLK && RS_DT != RS_CLK) {
        RS_is_clockwise = true;
        counter++;
        RS_increment = 0;
        return;
    }

    if(RS_DT != RS_CLK) {
        RS_is_clockwise = true;
        counter++;
        RS_increment = 0;
        return;
    }

    if(RS_PDT == RS_PCLK && RS_DT == RS_CLK && RS_PDT != RS_CLK) {
        RS_is_clockwise = false;
        counter--;
        RS_increment = 0;
        return;
    } else {
        counter++;
    }

    RS_increment = 0;
};

void RS_turn_detect() {
    turnDetect = digitalRead(RS_CLK_PIN);
    // Serial.println(turnDetect);

    if(turnDetect != prev_turnDetect) {
      prev_turnDetect = turnDetect;
      delay(RS_debounce_delay/3);
      RS_increment++;
      if(((millis() - RS_last_debounce_time) > RS_debounce_delay)) {
          RS_PDT = RS_DT;
          RS_PCLK = RS_CLK;

          check_RS_states();

          RS_last_debounce_time = millis();
      }
    //   Serial.println(counter);'
    }
}

void setup(void) {
    u8g2.begin();
    // Serial.begin(9600);
    // Put current pins state in variables
    pinMode(RS_DT_PIN, INPUT);
    pinMode(RS_CLK_PIN, INPUT);

    // // Set the Switch pin to use Arduino PULLUP resistors
    // pinMode(RS_SWITCH_PIN, INPUT_PULLUP);
}

void loop(void) {

    RS_turn_detect();

    if(counter >= 6) counter--;
    if(counter <= 0) counter++;
    u8g2.clearBuffer();
    menu->draw(u8g2, counter);
    u8g2.sendBuffer();


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
