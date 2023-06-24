#include "heat_plate.h"

bool HeatPlate::begin(uint8_t triac_pin = 32, uint8_t hall_effect_pin = 34) {
    this-> _ACS712_SENSITIVITY = 0.185;
    this-> _triac_pin = triac_pin;
    this-> _hall_effect_pin = hall_effect_pin;
    pinMode(hall_effect_pin, INPUT);
    pinMode(triac_pin, OUTPUT);
    return true;
}

HeatPlate::HeatPlate() {
    this->begin();
}

double HeatPlate::_measure_current_amps() {
    // Read the analog input
    uint16_t sensorValue = analogRead(this-> _hall_effect_pin);

    // Convert the analog value to voltage
    // Every ACS712 has a random voltage offset in it's out 
    // pin. In our case, this random number is 2.05V.
    double voltage = (sensorValue * (5.0 / 1023.0)) - 2.05;

    // Calculate the current in amperes
    double current_amps = voltage / this-> _ACS712_SENSITIVITY;

    return current_amps;
}

void HeatPlate::turn_on(bool is_full_cicle = true, uint8_t duty_percentage = 100) {
    if(duty_percentage == 0){
        digitalWrite(this-> _triac_pin, LOW);
        return;
    }
    int full_cicle_period_microseconds = 16383;
    double current = this->_measure_current_amps();
    if (is_full_cicle) {
        // Wait cicle start
        while(current <= 0.05 && current >= -0.05) {
            current = this->_measure_current_amps();
        }

        uint8_t full_cicles_on = duty_percentage / 10;
        for (int i = 0; i < full_cicles_on; i++) {
            digitalWrite(this-> _triac_pin, HIGH);
            delayMicroseconds(full_cicle_period_microseconds);
        }

        uint8_t full_cicles_off = 10 - full_cicles_on;
        for (int i = 0; i < full_cicles_off; i++) {
            digitalWrite(this-> _triac_pin, LOW);
            delayMicroseconds(full_cicle_period_microseconds);
        }
        digitalWrite(this-> _triac_pin, LOW);
    } else { // dimmerize
        // Wait cicle start
        while(current <= 0.05 && current >= -0.05) {
            current = this->_measure_current_amps();
        }
        
        // Turn the heat plate on for 10 ac main periods
        for (int i = 0; i < 10; i++) {
            // It will turn the heat place for x% of a single cicle on and
            // 100%  - x% of a cicle off.
            digitalWrite(this-> _triac_pin, HIGH);
            delayMicroseconds(full_cicle_period_microseconds * (duty_percentage / 100.0));
            digitalWrite(this-> _triac_pin, LOW);
            delayMicroseconds((full_cicle_period_microseconds * (1 - (duty_percentage / 100.0))));
        }
    }
}