#include "const_temp_view.h"

ConstTemp* const_temp = new ConstTemp(25);
HeatPlate* heat_plate = new HeatPlate();
int click_counter = 0;

extern void show_const_temp(uint8_t &current_view, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2) {
    if(click_counter > 0) {
        r_switch->turn_detect();
        if(r_switch->counter > 9) r_switch->counter--;
        if(r_switch->counter <= -1) r_switch->counter++;
        u8g2.clearBuffer();
        const_temp->draw(u8g2, click_counter, r_switch->counter);
        u8g2.sendBuffer();
    }
    if(r_switch->get_switch_state()) {
        int t = const_temp->get_temperature();
        int hundreds = (int) t/100;
        int decimals = (int) (t - hundreds*100)/10;
        int units = (int) (t - (hundreds*100) - (decimals*10));

        if(click_counter == 2) r_switch->counter = hundreds;
        if(click_counter == 3) r_switch->counter = decimals;
        if(click_counter == 0) r_switch->counter = units;
        click_counter--;
        u8g2.clearBuffer();
        const_temp->draw(u8g2, click_counter, r_switch->counter);
        u8g2.sendBuffer();
    }
    if(click_counter < 0) click_counter = 3;

    if(back_button->is_clicked()) {
        current_view--;
    }
    heat_plate->turn_on(true, 100);
}
