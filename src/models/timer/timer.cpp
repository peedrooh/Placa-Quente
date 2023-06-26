#include "timer.h"
#include "assets/icons/icons.h"
#include "assets/headers/headers.h"
#include "assets/numbers/numbers.h"

#define celcius_normal_width 12
#define celcius_normal_height 10
static const unsigned char celcius_normal_bitmap[] U8X8_PROGMEM = {
  0x0E, 0x00, 0x9F, 0x07, 0xDB, 0x0F, 0xDF, 0x0C, 0xCE, 0x00, 0xC0, 0x00, 
  0xC0, 0x00, 0xC0, 0x0C, 0xC0, 0x0F, 0x80, 0x07, };

#define farenheight_normal_width 12
#define farenheight_normal_height 10
static const unsigned char farenheight_normal_bitmap[] U8X8_PROGMEM = {
  0x0E, 0x00, 0xDF, 0x0F, 0xDB, 0x0F, 0xDF, 0x00, 0xCE, 0x00, 0xC0, 0x03, 
  0xC0, 0x03, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, };

#define HEADER_DASHED_BACK 2

Timer::Timer() {
    this->_cursor_index = 0;
    this->set_time(1, 30);
    this->set_temp(100);
    this->set_timer_screen(0);
}

void Timer::_draw_enter_and_back(U8G2 &u8g2, byte is_focused) {
    // Draw back icon
    u8g2.setBitmapMode(false);
    u8g2.setDrawColor(1);
    u8g2.drawXBM(105, 34, all_icons[2]->icon_width, all_icons[2]->icon_height, all_icons[2]->get_icon());
     // Draw Enter
    u8g2.drawStr(96, 49, "Enter");
    // Enter Focus
    if(is_focused) {
        u8g2.drawLine(94, 48, 120, 48);
        u8g2.drawPixel(94, 49);
        u8g2.drawLine(93, 49, 93, 59);
        u8g2.drawPixel(120, 49);
        u8g2.drawLine(94, 60, 120, 60);
        u8g2.drawPixel(120, 59);
        u8g2.drawLine(121, 49, 121, 59);
        u8g2.drawPixel(94, 59);
    }
}

void Timer::_draw_message(U8G2 &u8g2, const char *str) {
    // Font Settings and text draw
    u8g2.setBitmapMode(true);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.drawStr(10, 3, str);
}

void Timer::_draw_keyboard(U8G2 &u8g2, uint8_t keyboard_key_index) {
    // Draw keyboard
    this->_draw_enter_and_back(u8g2, keyboard_key_index==12);

    for(int i = 0; i < 13; i++) {
        u8g2.setDrawColor(1);
        if(i < 2) {
            if(i == keyboard_key_index) {
                u8g2.drawBox(7+(i*11), 36, all_icons[i]->icon_width, all_icons[i]->icon_height);
                u8g2.setDrawColor(0);
            }
            u8g2.drawXBM(7+(11*i), 36, all_icons[i]->icon_width, all_icons[i]->icon_height, all_icons[i]->get_icon());
        } else if (i < 6) {
            if(i == keyboard_key_index) {
                u8g2.drawBox(7+(i*11), 36, 11, 13);
                u8g2.setDrawColor(0);
            }
            u8g2.drawStr(10+(11*i), 37, String(i - 2).c_str() );
        } else if (i < 12) {
            if(i == keyboard_key_index) {
                u8g2.drawBox(7+((i-6)*11), 36+12, 11, 13);
                u8g2.setDrawColor(0);
            }
            u8g2.drawStr(10+(11*(i-6)), 37+12, String(i - 2).c_str() );
        }
    }
}

void Timer::draw_set_time_screen(U8G2 &u8g2, uint8_t keyboard_key_index) {
    this->_draw_message(u8g2, "Digite o tempo:");

    // Draw Separator
    u8g2.drawBox(63, 23, 2, 2);
    u8g2.drawBox(63, 27, 2, 2);

    // Draw Highlight
    if(this->_cursor_index > 1) {
        u8g2.drawLine(37, 19, 37+22-1, 19);
        u8g2.drawLine(37, 19, 37, 19+2);
        u8g2.drawLine(37+22-1, 19, 37+22-1, 19+2);
        u8g2.drawLine(37, 19+12, 37+22-1, 19+12);
        u8g2.drawLine(37, 19+10, 37, 19+12);
        u8g2.drawLine(37+22-1, 19+10, 37+22-1, 19+12);
    } else {
        u8g2.drawLine(69, 19, 69+22-1, 19);
        u8g2.drawLine(69, 19, 69, 19+2);
        u8g2.drawLine(69+22-1, 19, 69+22-1, 19+2);
        u8g2.drawLine(69, 19+12, 69+22-1, 19+12);
        u8g2.drawLine(69, 19+10, 69, 19+12);
        u8g2.drawLine(69+22-1, 19+10, 69+22-1, 19+12);
    }

    // Draw set time
    uint8_t* sec_min = this->get_time();
    String time_split_in_digits[4] = {
        String(sec_min[0]%10),
        String(sec_min[0]/10),
        String(sec_min[1]%10),
        String(sec_min[1]/10)
    };

    for(int i = 0; i < 4; i++) {

        if(i == this->_cursor_index) {
            u8g2.drawBox(this->_set_time_x_positions[i][1], 20, 11, 12);
            u8g2.setDrawColor(0);
        } else {
            u8g2.setDrawColor(1);
        }
        u8g2.drawStr(this->_set_time_x_positions[i][0], 20, time_split_in_digits[i].c_str());
        u8g2.setDrawColor(1);
    }

    this->_draw_keyboard(u8g2, keyboard_key_index);
}

void Timer::draw_set_temp_screen(U8G2 &u8g2, uint8_t keyboard_key_index, byte is_celcius) {
    this->_draw_message(u8g2, "Digite a temperatura:");

    // Draw Highlight    
    u8g2.drawLine(39, 19, 39+33+1, 19);
    u8g2.drawLine(39, 19+12, 39+33+1, 19+12);
    u8g2.drawLine(39, 19, 39, 19+2);
    u8g2.drawLine(39, 19+10, 39, 19+12);
    u8g2.drawLine(39+33+1, 19, 39+33+1, 19+2);
    u8g2.drawLine(39+33+1, 19+10, 39+33+1, 19+12);

    // Draw unit
    u8g2.drawLine(79, 19, 82, 19);
    u8g2.drawLine(78, 20, 78, 21);
    u8g2.drawLine(79, 22, 82, 22);
    u8g2.drawLine(83, 20, 83, 21);
    if(is_celcius) {
        u8g2.drawStr(84, 21, "C");
    } else {
        u8g2.drawStr(84, 21, "F");
    }
    

    // Draw set temperature
    uint8_t temp = this->get_temp();
    String temp_split_in_digits[3] = {
        String(temp%10),
        String((temp/10)%10),
        String(temp/100)
    };

    for(int i = 0; i < 3; i++) {

        if(i == this->_cursor_index) {
            u8g2.drawBox(this->_set_temp_x_positions[i][1], 20, 11, 12);
            u8g2.setDrawColor(0);
        } else {
            u8g2.setDrawColor(1);
        }
        u8g2.drawStr(this->_set_temp_x_positions[i][0], 20, temp_split_in_digits[i].c_str());
        u8g2.setDrawColor(1);
    }

    this->_draw_keyboard(u8g2, keyboard_key_index);
}

void Timer::draw_timer_screen(U8G2 &u8g2, double temperature, uint8_t min, uint8_t sec, byte is_celcius) {
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
    u8g2.drawStr(6, 0, "Tempor.");

    // Draw circle
    u8g2.drawCircle(13+21, 18+21, 21);
    u8g2.drawCircle(13+21, 18+21, 20);

    uint8_t* total_time_array = this->get_time();
    uint8_t total_time = total_time_array[0] + (total_time_array[1] * 60);

    uint8_t curr_time = sec + (min * 60);

    float time_percentage = (float)curr_time/total_time;

    u8g2.drawDisc(13+21, 18+21, 20*(1-time_percentage));

    // Draw Temperature
    uint8_t temp_unit = int(temperature)%10;
    uint8_t temp_dec = int(temperature/10)%10;
    uint8_t temp_hun = int(temperature)/100;

    u8g2.drawXBM(75, 23, all_numbers[temp_hun]->number_width, all_numbers[temp_hun]->number_height, all_numbers[temp_hun]->get_number());
    u8g2.drawXBM(75+ all_numbers[temp_dec]->number_width, 23, all_numbers[temp_dec]->number_width, all_numbers[temp_dec]->number_height, all_numbers[temp_dec]->get_number());
    u8g2.drawXBM(75 + (2*all_numbers[temp_unit]->number_width), 23, all_numbers[temp_unit]->number_width, all_numbers[temp_unit]->number_height, all_numbers[temp_unit]->get_number());
    if(is_celcius) {
        u8g2.drawXBM(75 + (3*all_numbers[4]->number_width)+1, 23, celcius_normal_width, celcius_normal_height, celcius_normal_bitmap);
    } else {
        u8g2.drawXBM(75 + (3*all_numbers[4]->number_width)+1, 23, farenheight_normal_width, farenheight_normal_height, farenheight_normal_bitmap);
    }
    
    // Draw Time
    // Draw Separator
    u8g2.drawBox(75+(2*all_numbers[4]->number_width)+4, 23+22+2, 2, 2);
    u8g2.drawBox(75+(2*all_numbers[4]->number_width)+4, 23+22+6, 2, 2);

    u8g2.drawXBM(75, 23+22, all_numbers[min/10]->number_width, all_numbers[min/10]->number_height, all_numbers[min/10]->get_number());
    u8g2.drawXBM(75+all_numbers[min%10]->number_width, 23+22, all_numbers[min%10]->number_width, all_numbers[min%10]->number_height, all_numbers[min%10]->get_number());
    u8g2.drawXBM(75+(2*all_numbers[sec/10]->number_width)+8, 23+22, all_numbers[sec/10]->number_width, all_numbers[sec/10]->number_height, all_numbers[sec/10]->get_number());
    u8g2.drawXBM(75+(3*all_numbers[sec%10]->number_width)+8, 23+22, all_numbers[sec%10]->number_width, all_numbers[sec%10]->number_height, all_numbers[sec%10]->get_number());
}


void Timer::set_time(uint8_t minutes, uint8_t seconds) {
    this->_minutes = minutes;
    this->_seconds = seconds;
}

uint8_t Timer::get_key(uint8_t index) {
    if(index < 0 || index > 12) return 13;
    return this->_keyboard_keys[index];
}

void Timer::set_cursor_index(uint8_t keyboard_key, byte is_set_time) {
    if(keyboard_key == 11 && this->_cursor_index < 3 && is_set_time) this->_cursor_index++;
    if(keyboard_key == 11 && this->_cursor_index < 2 && !is_set_time) this->_cursor_index++;
    if(keyboard_key == 12 && this->_cursor_index > 0) this->_cursor_index--;
    return;
}

uint8_t* Timer::get_time() {
    static uint8_t time[2];
    time[0] = this->_seconds;
    time[1] = this->_minutes;
    return time;
}

uint8_t Timer::get_temp() {
    return this->_temperature;
}

void Timer::set_temp(uint8_t temperature) {
    this->_temperature = temperature;
}

uint8_t Timer::get_cursor_index() {
    return this->_cursor_index;
}

void Timer::set_timer_screen(uint8_t current_screen) {
    if(current_screen >= 0 && current_screen <= 2) this->_timer_screen = current_screen;
}

uint8_t Timer::get_timer_screen() {
    return this->_timer_screen;
}