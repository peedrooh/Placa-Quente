#ifndef HEAT_PLATE_H
#define HEAT_PLATE_H

#include <Arduino.h>

class HeatPlate {
    public:
        HeatPlate();
        bool begin(uint8_t triac_pin, uint8_t hall_effect_pin);
        void turn_on(bool is_full_cicle, uint8_t duty_percentage);

    private:
        double _measure_current_amps();
        unsigned long _ACS712_SENSITIVITY;
        uint8_t _triac_pin;
        uint8_t _hall_effect_pin;
};


#endif