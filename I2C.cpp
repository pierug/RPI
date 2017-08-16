#include "I2C.h"

I2C::~I2C() {
}

void I2C::write8bitRegister(int Register, int data) {
    throwIfNotInitialize();
    wiringPiI2CWriteReg8(handle, Register, data);
}

void I2C::write16bitRegister(int Register, int data) {
    throwIfNotInitialize();
    wiringPiI2CWriteReg16(handle, Register, data);
}

void I2C::write(int data) {
    throwIfNotInitialize();
    int i = wiringPiI2CWrite(handle, data);
}

void I2C::throwIfNotInitialize() {
    if (handle == -1) {
        throw WiringException("I2C has not been initialized");
    }
}

int I2C::read16bitRegister(int Register) {
    throwIfNotInitialize();
    return wiringPiI2CReadReg16(handle, Register);
}

int I2C::read8bitRegister(int Register) {
    throwIfNotInitialize();
    return wiringPiI2CReadReg8(handle, Register);
}

int I2C::read() {
    throwIfNotInitialize();
    int i=wiringPiI2CRead(handle);
    return i;
}

I2C::I2C(string device, int address) {
    handle = wiringPiI2CSetupInterface(device.c_str(), address);
    if (handle == -1) {
        throw WiringException("Device " + device + " with address " + to_string(address) + " cannot initialize");
    }
}

I2C::I2C(int address) {
    handle = wiringPiI2CSetup(address);
    if (handle == -1) {
        throw WiringException("Device with address " + to_string(address) + " cannot initialize");
    }
}
