#include <Arduino.h>
#include <U8g2lib.h>

#include "assets/icons/icons.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


#define TEXT_LEFT_PADDING 29 // 2*ICON_LEFT_PADDING + ICON_WIDTH + 5
#define TEXT_TOP_PADDING_TOP 4

#define TEXT_HEIGHT 10

#define ICON_LEFT_PADDING 4
#define ICON_TOP_PADDING 2
#define ICON_HEIGHT 16
#define ICON_WIDTH 16


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void draw_srcrollbar() {
    // Draw scrollbar scroll
    for(int i = 1; i < 64; i++) {
      u8g2.drawPixel(126, i);
      i++;
    }
    // draw scrollbar bar
    u8g2.drawBox(125, 64/5 * 2, 3, 64/5);
}

void draw_focus_item() {
    // Draw Foucus Item
    u8g2.drawLine(1, 24, 1, 40);
    u8g2.drawLine(1, 24, 3, 22);
    u8g2.drawLine(3, 22, 119, 22);
    u8g2.drawLine(119, 22, 121, 24);
    u8g2.drawLine(121, 24, 121, 40);
    u8g2.drawLine(120, 24, 120, 40);
    u8g2.drawLine(121, 40, 119, 42);
    u8g2.drawLine(119, 42, 3, 42);
    u8g2.drawLine(3, 41, 119, 41);
    u8g2.drawLine(3, 42, 1, 40);
};

void text_prepare(const uint8_t * font, int drawColorState) {
  u8g2.setFont(font);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(drawColorState);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void draw_menu() {
  draw_srcrollbar();
  draw_focus_item();

  text_prepare(u8g2_font_haxrcorp4089_tr, 1);
  u8g2.drawStr(TEXT_LEFT_PADDING, (TEXT_TOP_PADDING_TOP) , "Menu Principal");
  u8g2.setDrawColor(1);
  u8g2.drawXBMP(ICON_LEFT_PADDING, ICON_TOP_PADDING, ICON_WIDTH, ICON_HEIGHT, all_icons[5]->get_icon());

  text_prepare(u8g2_font_helvB08_tr, 1);
  u8g2.drawStr(TEXT_LEFT_PADDING, 22+(TEXT_TOP_PADDING_TOP) , "Temp. Constante");
  u8g2.setDrawColor(1);
  u8g2.drawXBMP(ICON_LEFT_PADDING, 22+ICON_TOP_PADDING, ICON_WIDTH, ICON_HEIGHT, all_icons[8]->get_icon());

  text_prepare(u8g2_font_haxrcorp4089_tr, 1);
  u8g2.drawStr(TEXT_LEFT_PADDING, 44+(TEXT_TOP_PADDING_TOP) , "Temporizador");
  u8g2.setDrawColor(1);
  u8g2.drawXBMP(ICON_LEFT_PADDING, 44+ICON_TOP_PADDING, ICON_WIDTH, ICON_HEIGHT, all_icons[7]->get_icon());
};

void setup(void) {
  u8g2.begin();
  // Serial.begin(9600);
}

void loop(void) {
  u8g2.clearBuffer();
  draw_menu();
  u8g2.sendBuffer();
}