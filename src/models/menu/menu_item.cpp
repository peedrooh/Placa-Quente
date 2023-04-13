#include "menu_item.h"
#include "assets/icons/icons.h"

#define TEXT_LEFT_PADDING 29 // 2*ICON_LEFT_PADDING + ICON_WIDTH + 5
#define TEXT_TOP_PADDING_TOP 5

#define TEXT_HEIGHT 10

#define ICON_LEFT_PADDING 4
#define ICON_TOP_PADDING 2
#define ICON_HEIGHT 16
#define ICON_WIDTH 16

void Menu_Item::text_prepare(U8G2 &u8g2, const uint8_t * font, int drawColorState) {
    u8g2.setFont(font);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(drawColorState);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
};

void Menu_Item::draw(U8G2 &u8g2, const char * text, uint8_t icon_index, const uint8_t * font, uint8_t index) {
    int position = 22 * index;

    text_prepare(u8g2, font, 1);
    u8g2.drawStr(TEXT_LEFT_PADDING, position + (TEXT_TOP_PADDING_TOP) , text);
    u8g2.drawXBMP(ICON_LEFT_PADDING, position + ICON_TOP_PADDING, ICON_WIDTH, ICON_HEIGHT, all_icons[icon_index]->get_icon());
};