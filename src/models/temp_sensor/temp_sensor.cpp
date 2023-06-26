#include "temp_sensor.h"

#define TEMP_SENSOR_I2C_ADDR 0x5A

TempSensor::TempSensor() {
    this->mlx = Adafruit_MLX90614();
}

bool TempSensor::begin() {
    if (!this->mlx.begin(TEMP_SENSOR_I2C_ADDR)) {
        Serial.println("Error connecting to MLX sensor. Check wiring.");
        return false;
    };
    return true;
}

double TempSensor::read_temp(bool is_degrees_celcius = true) {
    if(is_degrees_celcius)
        return mlx.readObjectTempC() + 2;

    return mlx.readObjectTempF() + 4;
}