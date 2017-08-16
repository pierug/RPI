#ifndef I2C_H
#define I2C_H

#include <iostream>
#include <wiringPiI2C.h>
#include "WiringException.h"
using namespace std;

class I2CInterface {
public:
    virtual int read()=0;
    virtual int read8bitRegister(int Register)=0;
    virtual int read16bitRegister(int Register)=0;
    virtual void write(int data)=0;
    virtual void write8bitRegister(int Register,int data)=0;
    virtual void write16bitRegister(int Register,int data)=0;
};
class I2C : public I2CInterface{
public:
    I2C(int address);
    I2C(string device, int address);
    
    virtual ~I2C();
    
    int read() override;
    int read16bitRegister(int Register) override;
    int read8bitRegister(int Register) override;
    void write(int data) override;
    void write16bitRegister(int Register,int data) override;
    void write8bitRegister(int Register,int data) override;
private:
    int handle = -1;
    void throwIfNotInitialize();
};

#endif /* I2C_H */

