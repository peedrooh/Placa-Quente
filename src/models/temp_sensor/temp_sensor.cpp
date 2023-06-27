#include "temp_sensor.h"

// #define TEMP_SENSOR_I2C_ADDR 0x5A
// #define SDA_2 33
// #define SCL_2 32

// TempSensor::TempSensor() {
//     this->mlx = Adafruit_MLX90614();
//     this->_Wire1 = Wire1;
// }

// bool TempSensor::begin() {
//     this->_Wire1.begin(SDA_2, SCL_2);
//     if (!this->mlx.begin(TEMP_SENSOR_I2C_ADDR, &this->_Wire1)) {
//         Serial.println("Error connecting to MLX sensor. Check wiring.");
//         return false;
//     };
//     return true;
// }

// double TempSensor::read_temp(bool is_degrees_celcius = true) {
//     if(is_degrees_celcius)
//         return mlx.readObjectTempC() + 2;

//     return mlx.readObjectTempF() + 4;
// }