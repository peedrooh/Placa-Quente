#include "rotary_switch.h"


RotarySwitch::RotarySwitch(int data_pin, int clock_pin, int switch_pin)

{
    this->_DATA_PIN = data_pin;
    this->_CLOCK_PIN = clock_pin;
    this->_SWITCH_PIN = switch_pin;
}

void RotarySwitch::begin() {
    pinMode(this->_DATA_PIN, INPUT);
    pinMode(this->_CLOCK_PIN, INPUT);
    pinMode(this->_SWITCH_PIN, INPUT_PULLUP);

    // Private variables initial values
    this->counter = 0;
    this->was_clicked = 0;
    this->_is_clockwise = 0;
    this->_turnDetect = 0;
    this->_prev_turnDetect = 0;
    this->_last_debounce_time = 0;
    this->_debounce_delay = 10;
    this->_clock_ticks = 0;
}

byte RotarySwitch::get_switch_state() {
    delay(this->_debounce_delay);
    this->was_clicked = !digitalRead(this->_SWITCH_PIN); 
    return this->was_clicked;
}
void RotarySwitch::turn_detect() {
    this->_turnDetect = digitalRead(this->_DATA_PIN);

    if(this->_turnDetect != this->_prev_turnDetect) {
        this->_prev_turnDetect = this->_turnDetect;
        delay(this->_debounce_delay/3);
        this->_clock_ticks++;
        if(((millis() - this->_last_debounce_time) > this->_debounce_delay)) {
            this->_PDT = this->_DT;
            this->_PCLK = this->_CLK;

            this->_check_states();
            // Serial.print("----------- ");
            // Serial.print(this->counter);
            // Serial.println(" -----------");

            this->_last_debounce_time = millis();
        }
    }
}


void RotarySwitch::_check_states() {
    this->_CLK = digitalRead(this->_CLOCK_PIN);
    this->_DT = digitalRead(this->_DATA_PIN);

    // // Rotary Switches States prints to help indentify patterns.
    // Serial.println(" PDT | PCLK | INC | DT | CLK");
    // Serial.print("  ");
    // Serial.print(this->_PDT);
    // Serial.print("  |  ");
    // Serial.print(this->_PCLK);
    // Serial.print("   |  ");
    // Serial.print(this->_clock_ticks);
    // Serial.print("  |  ");
    // Serial.print(this->_DT);
    // Serial.print(" |  ");
    // Serial.println(this->_CLK);

    if(this->_clock_ticks != 1) {
        this->_clock_ticks = 0;
        return;
    }

    if(this->_PDT == this->_PCLK && this->_DT == this->_CLK ) {
        this->_is_clockwise = true;
        this->counter++;
        this->_clock_ticks = 0;
        return;
    } else {
        this->_is_clockwise = false;
        this->counter--;
        this->_clock_ticks = 0;
        return;
    }
};

