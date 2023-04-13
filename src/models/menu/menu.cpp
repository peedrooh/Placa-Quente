#include "menu.h"
#include "models/menu/menu_item.h"

#define SCREEN_SIZE 64

#define SCROLL_POSITION_X 126

#define BAR_X_POSITION 125
#define BAR_HEIGHT (SCREEN_SIZE / NUM_MENU_ITEMS)
#define BAR_WIDTH 3

#define MENU_ITEM_HEIGHT 20
#define MENU_ITEM_BOTTOM_MARGIN 2

void Menu::draw_srcrollbar(U8G2 &u8g2, int current_item) {
    // Draw scrollbar scroll
    for(int i = 1; i < SCREEN_SIZE; i+=2) {
      u8g2.drawPixel(SCROLL_POSITION_X, i);
    }
    // draw scrollbar bar
    u8g2.drawBox(BAR_X_POSITION, current_item*BAR_HEIGHT, BAR_WIDTH, BAR_HEIGHT);
}

void Menu::draw_focus_item(U8G2 &u8g2) {
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


void Menu::draw(U8G2 &u8g2, int current_item){
    if( current_item == 0) current_item = 1;
    this->draw_srcrollbar(u8g2, current_item);
    this->draw_focus_item(u8g2);
    Menu_Item* menu_item = new Menu_Item();
    // menu_item->draw(u8g2, "Menu Principal", 5, u8g2_font_helvB08_tr, 0); 
    // menu_item->draw(u8g2, "Temp. Constante", 8, u8g2_font_helvB08_tr, 1); 
    // menu_item->draw(u8g2, "Temporizador", 7, u8g2_font_haxrcorp4089_tr, 2);

    for(int i = current_item - 1; i <= current_item+1; i++) {
        if (((i - current_item+1) % 2) == 0) {
            menu_item->draw(u8g2, this->menu_titles[i], this->icons_indexes[i], u8g2_font_haxrcorp4089_tr, i - current_item+1); 
        } else {
            menu_item->draw(u8g2, this->menu_titles[i], this->icons_indexes[i], u8g2_font_helvB08_tr,  i - current_item+1); 
        }
    }
};