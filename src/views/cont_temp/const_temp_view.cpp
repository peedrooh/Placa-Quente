#include "const_temp_view.h"


ConstTemp* const_temp = new ConstTemp(80);
HeatPlate* heat_plate_ct = new HeatPlate();
PIDController* pid_ct = new PIDController(2, 0.1, 0.2, 100, 0, 100);


int click_counter = 0;

byte was_controlling_temp = 0;
byte is_heating = 0;

double current_time = millis();
double previous_time = 0;

double duty_cycle;

int set_temp = const_temp->get_temperature();
float curr_temp = 0.0;

extern void show_const_temp(uint8_t &current_view, Adafruit_MLX90614 &temp_sensor, RotarySwitch* &r_switch, BackButton* &back_button, U8G2 &u8g2, Config* &config) {
    u8g2.clearBuffer();
    const_temp->draw(u8g2, click_counter, r_switch->counter, set_temp - 5 > curr_temp, config);
    u8g2.sendBuffer();
    set_temp = const_temp->get_temperature();
    pid_ct->setSetpoint(set_temp);
    pid_ct->resetVars();
    byte is_full_cicles = config->config_items[1][0].is_selected;
    
    while(click_counter == 0) {
        if(r_switch->get_switch_state()) {
            was_controlling_temp = 1;
            break;
        }
        if(back_button->is_clicked()) {
            current_view--;
            return;
        }
        if(config->config_items[0][0].is_selected) {
            curr_temp = temp_sensor.readObjectTempC();
        } else {
            curr_temp = temp_sensor.readObjectTempF();
        }
        
        if(set_temp - 5 > curr_temp) {
            duty_cycle = 100;
        } else {
            duty_cycle = pid_ct->compute(curr_temp);
        }
        // Serial.print("D:");
        // Serial.print(duty_cycle);
        // Serial.print("    T:"); 
        // Serial.print(curr_temp);
        // Serial.print("    S:");
        // Serial.println(set_temp);
        heat_plate_ct->turn_on(is_full_cicles, duty_cycle);
    }

    if(r_switch->get_switch_state() || was_controlling_temp) {
        was_controlling_temp = 0;
        int t = const_temp->get_temperature();
        int hundreds = (int) t/100;
        int decimals = (int) (t - hundreds*100)/10;
        int units = (int) (t - (hundreds*100) - (decimals*10));


        if(click_counter == 2) r_switch->counter = hundreds;
        if(click_counter == 3) r_switch->counter = decimals;
        if(click_counter == 0) r_switch->counter = units;
        click_counter--;
        if(click_counter < 0) click_counter = 3;
    }

    if(click_counter > 0) {
        r_switch->turn_detect();
        if(click_counter == 1 && r_switch->counter > 2) r_switch->counter--;

        if(r_switch->counter > 9) r_switch->counter--;
        if(r_switch->counter <= -1) r_switch->counter++;
    }

}
