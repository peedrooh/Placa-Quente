#include "timer.h"
#include "assets/icons/icons.h"


Timer::Timer() {
    this->_time_cursor_index = 0;
    this->set_time(5, 25);
    // Array containing the string x position and highligth box x position for each number to set
}

void Timer::draw_set_time_screen(U8G2 &u8g2, uint8_t keyboard_key_index) {
    // Font Settings and text draw
    u8g2.setBitmapMode(true);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.drawStr(10, 3, "Digite o tempo:");

    // Draw Separator
    u8g2.drawBox(63, 23, 2, 2);
    u8g2.drawBox(63, 27, 2, 2);

    // Draw Highlight
    if(this->_time_cursor_index > 1) {
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

    uint8_t* sec_min = this->get_time();
    String time_split_in_digits[4] = {
        String(sec_min[0]%10),
        String(sec_min[0]/10),
        String(sec_min[1]%10),
        String(sec_min[1]/10)
    };

    for(int i = 0; i < 4; i++) {

        if(i == this->_time_cursor_index) {
            u8g2.drawBox(this->_set_time_x_positions[i][1], 20, 11, 12);
            u8g2.setDrawColor(0);
        } else {
            u8g2.setDrawColor(1);
        }
        u8g2.drawStr(this->_set_time_x_positions[i][0], 20, time_split_in_digits[i].c_str());
        u8g2.setDrawColor(1);
    }


    // Draw back icon
    u8g2.setBitmapMode(false);
    u8g2.setDrawColor(1);
    u8g2.drawXBM(105, 34, all_icons[2]->icon_width, all_icons[2]->icon_height, all_icons[2]->get_icon());

    // Draw Enter
    u8g2.drawStr(96, 49, "Enter");
    // Enter Focus
    if(keyboard_key_index == 12) {
        u8g2.drawLine(94, 48, 120, 48);
        u8g2.drawPixel(94, 49);
        u8g2.drawLine(93, 49, 93, 59);
        u8g2.drawPixel(120, 49);
        u8g2.drawLine(94, 60, 120, 60);
        u8g2.drawPixel(120, 59);
        u8g2.drawLine(121, 49, 121, 59);
        u8g2.drawPixel(94, 59);
    }


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

void Timer::set_time(uint8_t minutes, uint8_t seconds) {
    this->_minutes = minutes;
    this->_seconds = seconds;
}

uint8_t Timer::get_key(uint8_t index) {
    if(index < 0 || index > 12) return 13;
    return this->_keyboard_keys[index];
}

void Timer::set_time_cursor_index(uint8_t keyboard_key) {
    if(keyboard_key == 11 && this->_time_cursor_index < 3) this->_time_cursor_index++;
    if(keyboard_key == 12 && this->_time_cursor_index > 0) this->_time_cursor_index--;
    return;
}

uint8_t* Timer::get_time() {
    static uint8_t time[2];
    time[0] = this->_seconds;
    time[1] = this-> _minutes;
    return time;
}

uint8_t Timer::get_time_cursor_index() {
    return this->_time_cursor_index;
}