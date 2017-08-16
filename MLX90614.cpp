#include "MLX90614.h"

MLX90614::MLX90614(uint8_t i2caddr):i2c(new I2C(i2caddr)) {
    _addr = i2caddr;
}

double MLX90614::readObjectTempF(void) {
    return (readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}

double MLX90614::readAmbientTempF(void) {
    return (readTemp(MLX90614_TA) * 9 / 5) + 32;
}

double MLX90614::readObjectTempC(void) {
    return readTemp(MLX90614_TOBJ1);
}

double MLX90614::readAmbientTempC(void) {
    return readTemp(MLX90614_TA);
}

float MLX90614::readTemp(uint8_t reg) {
    float temp;
    temp = read16(reg);
    temp *= .02;
    temp -= 273.15;
    return temp;
}

uint16_t MLX90614::read16(uint8_t reg) {
    return i2c->read16bitRegister(reg);
}
