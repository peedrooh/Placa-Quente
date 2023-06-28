#include "config.h"
#include "assets/headers/headers.h"
#include "assets/icons/icons.h"

#define SCREEN_SIZE 64

#define HEADER_DASHED_BACK 2

#define SCROLL_POSITION_X 126

#define NUM_CONFIG_ITEMS 3
#define BAR_X_POSITION 125
#define BAR_HEIGHT 10
#define BAR_WIDTH 3
#define BAR_Y_POSITION (50 / (NUM_CONFIG_ITEMS - 1))


void Config::_draw_header(U8G2 &u8g2, byte header_type) {
    // Header Draw
    u8g2.setBitmapMode(false);
    u8g2.setDrawColor(1);
    u8g2.drawXBM(0, 0, all_headers[HEADER_DASHED_BACK]->header_width, all_headers[HEADER_DASHED_BACK]->header_height, all_headers[HEADER_DASHED_BACK]->get_header());
    // Font Settings and text draw
    u8g2.setBitmapMode(true);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.drawStr(6, 0, "Configs.");
}

void Config::_draw_scroll_bar(U8G2 &u8g2, int current_config) {
    // Draw scrollbar scroll
    for(int i = 14; i < SCREEN_SIZE; i+=2) {
      u8g2.drawPixel(SCROLL_POSITION_X, i);
    }
    // draw scrollbar bar
    if (!current_config) u8g2.drawBox(BAR_X_POSITION, 14 + (BAR_Y_POSITION*current_config), BAR_WIDTH, BAR_HEIGHT);
    // else if (current_config == NUM_CONFIG_ITEMS - 1) u8g2.drawBox(BAR_X_POSITION, 14 + (BAR_Y_POSITION*current_config) - BAR_HEIGHT, BAR_WIDTH, BAR_HEIGHT);
    else u8g2.drawBox(BAR_X_POSITION, 54, BAR_WIDTH, BAR_HEIGHT);
}

void Config::_draw_config_menu_items(U8G2 &u8g2, int current_config) {
    u8g2.setBitmapMode(true);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    if(current_config == 0) {
        // If is first item
        for(int i = current_config; i <= current_config + 2; i++) {
            if(i == 0) {
                u8g2.setDrawColor(1);
                u8g2.drawBox(3, 18+(i*15), 119, 13);
                u8g2.drawLine(3-1, 1+18+(i*15), 3-1, 1+18+(i*15)+10);
                u8g2.drawLine(119+3, 1+18+(i*15), 119+3, 1+18+(i*15)+10);
                u8g2.setDrawColor(0);
                u8g2.drawStr(5, 19+(i*15), this->_items_titles[i]);
                u8g2.drawXBM(111, 18+(i*15), all_icons[1]->icon_width, all_icons[1]->icon_height, all_icons[1]->get_icon());
            } else {
                u8g2.setDrawColor(1);
                u8g2.drawStr(5, 19+(i*15), this->_items_titles[i]);
            }
        }
    } else if ((current_config == NUM_CONFIG_ITEMS-1)) {
        // If is last item
        for(int i = current_config-2; i <= current_config; i++) {
            if(i == 2) {
                u8g2.setDrawColor(1);
                u8g2.drawBox(3, 18+(i*15), 119, 13);
                u8g2.drawLine(3-1, 1+18+(i*15), 3-1, 1+18+(i*15)+10);
                u8g2.drawLine(119+3, 1+18+(i*15), 119+3, 1+18+(i*15)+10);
                u8g2.setDrawColor(0);
                u8g2.drawStr(5, 19+(i*15), this->_items_titles[i]);
                u8g2.drawXBM(111, 18+(i*15), all_icons[1]->icon_width, all_icons[1]->icon_height, all_icons[1]->get_icon());
            } else {
                u8g2.setDrawColor(1);
                u8g2.drawStr(5, 19+(i*15), this->_items_titles[i]);
            }
        }
    } else {
        for(int i = current_config - 1; i <= current_config + 1; i++) {
            if(i == 1) {
                u8g2.setDrawColor(1);
                u8g2.drawBox(3, 18+(i*15), 119, 13);
                u8g2.drawLine(3-1, 1+18+(i*15), 3-1, 1+18+(i*15)+10);
                u8g2.drawLine(119+3, 1+18+(i*15), 119+3, 1+18+(i*15)+10);
                u8g2.setDrawColor(0);
                u8g2.drawStr(5, 19+(i*15), this->_items_titles[i]);
                u8g2.drawXBM(111, 18+(i*15), all_icons[1]->icon_width, all_icons[1]->icon_height, all_icons[1]->get_icon());
            } else {
                u8g2.setDrawColor(1);
                u8g2.drawStr(5, 19+(i*15), this->_items_titles[i]);
            }
        }
    }

}

void Config::draw_config_menu(U8G2 &u8g2, int current_config) {
    if(current_config > NUM_CONFIG_ITEMS - 1) return;
    this->_draw_header(u8g2, 0);
    this->_draw_scroll_bar(u8g2, current_config);
    this->_draw_config_menu_items(u8g2, current_config);
}

void Config::draw_config_selector(U8G2 &u8g2, int current_config, int current_item) {
    if(current_item > 2) current_item = 2;
    if(this->config_items[current_config][2].title == "" && current_item == 2) current_item = 1;
    // Draw Title
    u8g2.setBitmapMode(true);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    String title = this->_items_titles[current_config];
    title+=":";
    u8g2.drawStr(5, 2, title.c_str());

    // Draw Back
    u8g2.setDrawColor(1);
    u8g2.drawXBM(112, 51, all_icons[2]->icon_width, all_icons[2]->icon_height, all_icons[2]->get_icon());

    // Draw Focus
    u8g2.setDrawColor(1);
    u8g2.drawBox(3, 18+(current_item*16), 107, 13);
    u8g2.drawLine(3-1, 1+18+(current_item*16), 3-1, 1+18+(current_item*16)+10);
    u8g2.drawLine(107+3, 1+18+(current_item*16), 107+3, 1+18+(current_item*16)+10);

    // Draw ConfigItem
    for(int i = 0; i < 3; i++) {
        u8g2.setDrawColor(1);
        if(i == current_item) u8g2.setDrawColor(0);
        if(this->config_items[current_config][i].is_selected) u8g2.drawXBM(4, 18+(i*16), all_icons[13]->icon_width, all_icons[13]->icon_height, all_icons[13]->get_icon());
        u8g2.drawStr(20, 19+(i*16), this->config_items[current_config][i].title.c_str());
    }
}