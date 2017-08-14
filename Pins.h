#ifndef PINS_H
#define PINS_H

#define PINS Pins::getInstance()
#include <wiringPi.h>
#include "WiringException.h"
#include <iostream>
#include <map>

using namespace std;

enum WIRING_PINS{
    wPI_0=0,
    wPI_1=1,
    wPI_2=2,
    wPI_3=3,
    wPI_4=4,
    wPI_5=5,
    wPI_6=6,
    wPI_7=7,
    wPI_21=21,
    wPI_22=22,
    wPI_23=23,
    wPI_24=24,
    wPI_25=25,
    wPI_26=26,
    wPI_27=27,
    wPI_28=28,
    wPI_29=29
};

class PinsInterface{
public:
    virtual ~PinsInterface(){}
    virtual void setPinMode(int pin, int mode)=0;
    virtual void setPullUpOrDownMode(int pin, int pull)=0;
    virtual void setPinState(int pin, int state)=0;
    virtual void setAnalogValue(int pin, int state)=0;
    virtual int getPinState(int pin)=0;
    virtual int getAnalogValue(int pin)=0;
    virtual void setPWM(int pin, int value)=0;
};

class Pins :public PinsInterface{
public:
    static Pins& getInstance(){
        static Pins pins;
        return pins;
    }
    virtual ~Pins();
    virtual int getAnalogValue(int pin) override;
    virtual void setPullUpOrDownMode(int pin, int pull) override;
    virtual void setPinState(int pin, int state) override;
    virtual void setPinMode(int pin, int mode) override;
    virtual void setPWM(int pin, int value) override;
    virtual void setAnalogValue(int pin, int state) override;
    virtual int getPinState(int pin) override;
    void printPinsMap();
private:
    Pins();
    Pins(const Pins& orig)=delete;
    Pins& operator=(const Pins& orig)=delete;
    void throwExceptionIfPinNotCorrect(int pin);
    bool isPWMValueCorrect(int value);
    bool isPinModeCorrect(int mode);
    bool isPinStateCorrect(int state);
    bool isPinPullCorrect(int pull);
    bool setDefault();
    map<int,int> pinsMap;
    void setPinInMap(int pin, int mode);
};

#endif /* PINS_H */

