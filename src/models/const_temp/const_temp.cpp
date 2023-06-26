#include "const_temp.h"
#include "assets/headers/headers.h"
#include "assets/big_numbers/big_numbers.h"
#include "assets/icons/icons.h"

// #define HEADER_DOTED_BACK 0
// #define HEADER_DOTED 1
#define HEADER_DASHED_BACK 2
// #define HEADER_DASHED 3

#define BN_X_POS 40
#define BN_X_PADDING 5
#define BN_Y_POS 25
#define BN_Y_PADDING 3


#define celcius_width 24
#define celcius_height 20
static const unsigned char celcius_bitmap[] U8X8_PROGMEM = {
  0xFC, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xFF, 0xC3, 0x3F, 0xFF, 0xC3, 0x3F, 
  0xCF, 0xF3, 0xFF, 0xCF, 0xF3, 0xFF, 0xFF, 0xF3, 0xF0, 0xFF, 0xF3, 0xF0, 
  0xFC, 0xF0, 0x00, 0xFC, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 
  0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0xF0, 0xF0, 
  0x00, 0xF0, 0xFF, 0x00, 0xF0, 0xFF, 0x00, 0xC0, 0x3F, 0x00, 0xC0, 0x3F, 
  };

#define farenheight_width 24
#define farenheight_height 20
static const unsigned char farenheight_bitmap[] U8X8_PROGMEM = {
  0xFC, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xFF, 0xF3, 0xFF, 0xFF, 0xF3, 0xFF, 
  0xCF, 0xF3, 0xFF, 0xCF, 0xF3, 0xFF, 0xFF, 0xF3, 0x00, 0xFF, 0xF3, 0x00, 
  0xFC, 0xF0, 0x00, 0xFC, 0xF0, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 
  0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 
  0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 
  };

#define focus_temp_width 79
#define focus_temp_height 27
static const unsigned char focus_temp_bitmap[] U8X8_PROGMEM = {
  0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFC, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x0E, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x60, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, };


ConstTemp::ConstTemp(int temperature) {
    this->set_temperature(temperature);
}

void ConstTemp::_draw_header(U8G2 &u8g2) {
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
    u8g2.drawStr(6, 0, "T. Const");
}

void ConstTemp::_draw_unit(U8G2 &u8g2, byte is_celcius) {
    u8g2.setBitmapMode(false);
    u8g2.setDrawColor(1);
    if(is_celcius) {
        u8g2.drawXBM(90, 28, celcius_width, celcius_height, celcius_bitmap);
    } else {
        u8g2.drawXBM(90, 28, farenheight_width, farenheight_height, farenheight_bitmap);
    }
}


void ConstTemp::_draw_icon(U8G2 &u8g2, byte is_heating) {
    u8g2.setBitmapMode(false);
    u8g2.setDrawColor(1);
    if(is_heating) {
        u8g2.drawXBM(15, 32, all_icons[10]->icon_width, all_icons[10]->icon_height, all_icons[10]->get_icon());
    } else {
        u8g2.drawXBM(15, 32, all_icons[8]->icon_width, all_icons[8]->icon_height, all_icons[8]->get_icon());
    }
}

void ConstTemp::_draw_focus(U8G2 &u8g2) {
    u8g2.setBitmapMode(false);
    u8g2.setDrawColor(1);
    u8g2.drawXBM(BN_X_POS, BN_Y_POS, focus_temp_width, focus_temp_height, focus_temp_bitmap);
}


void ConstTemp::_draw_big_digit(U8G2 &u8g2, uint8_t digit_index, uint8_t digit, byte is_bk_white) {
    if(is_bk_white) {
        u8g2.setBitmapMode(true);
        u8g2.setDrawColor(1);
        u8g2.drawBox(BN_X_POS+BN_X_PADDING+(all_big_nums[digit]->big_num_width*digit_index), BN_Y_POS+BN_Y_PADDING, all_big_nums[digit]->big_num_width , all_big_nums[digit]->big_num_height);
        u8g2.setDrawColor(0);
        u8g2.drawXBM(BN_X_POS+BN_X_PADDING+(all_big_nums[digit]->big_num_width*digit_index), BN_Y_POS+BN_Y_PADDING, all_big_nums[digit]->big_num_width , all_big_nums[digit]->big_num_height, all_big_nums[digit]->get_big_num());
    } else {
        u8g2.setBitmapMode(false);
        u8g2.setDrawColor(1);
        u8g2.drawXBM(BN_X_POS+BN_X_PADDING+(all_big_nums[digit]->big_num_width*digit_index), BN_Y_POS+BN_Y_PADDING, all_big_nums[digit]->big_num_width , all_big_nums[digit]->big_num_height, all_big_nums[digit]->get_big_num());
    }
}

void ConstTemp::draw(U8G2 &u8g2, uint8_t digit_index, uint8_t counter, byte is_heating, Config* &config) {
    this->_draw_header(u8g2);
    int hundreds = (int) this->_temperature/100;
    int decimals = (int) (this->_temperature - hundreds*100)/10;
    int units = (int) (this->_temperature - (hundreds*100) - (decimals*10));
    int temp[3] = {
        hundreds,
        decimals,
        units
    };
    temp[digit_index - 1] = counter;
    this->set_temperature(temp[2]+(temp[1]*10)+(temp[0]*100));

    if(digit_index > 0) {
        this->_draw_focus(u8g2);

        for(int i = 1; i <= 3; i++) {
            this->_draw_big_digit(u8g2, i - 1, temp[i - 1], i==digit_index);
        }
    } else {
        for(int i = 1; i <= 3; i++) {
            this->_draw_big_digit(u8g2, i - 1, temp[i - 1], false);
        }
    }

    
    this->_draw_icon(u8g2, is_heating);
    this->_draw_unit(u8g2, config->config_items[0][0].is_selected);
}

void ConstTemp::set_temperature(int temperature) {
    this->_temperature = temperature;
}

int ConstTemp::get_temperature() {
    return this->_temperature;
}