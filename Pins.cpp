/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pins.cpp
 * Author: Adam Piasecki
 * 
 * Created on 1 sierpnia 2017, 21:56
 */

#include "Pins.h"

Pins::Pins() {
    setDefault();
}

Pins::~Pins() {
}

int Pins::getAnalogValue(int pin) {
    throwExceptionIfPinNotCorrect(pin);
    return analogRead(pin);

}

int Pins::getPinState(int pin) {
    throwExceptionIfPinNotCorrect(pin);
    return digitalRead(pin);

}

void Pins::setAnalogValue(int pin, int state) {
    throwExceptionIfPinNotCorrect(pin);
    analogWrite(pin, state);

}

void Pins::setPWM(int pin, int value) {
    throwExceptionIfPinNotCorrect(pin);
    if (isPWMValueCorrect(value))
        analogWrite(pin, value);
    else
        throw WiringException("Wrong pwm value: " + to_string(value));

}

void Pins::setPinMode(int pin, int mode) {
    throwExceptionIfPinNotCorrect(pin);
    if (isPinModeCorrect(mode)) {
        pinMode(pin, mode);
        setPinInMap(pin, mode);
    } else
        throw WiringException("Wrong pin mode: " + to_string(mode));

}

void Pins::setPinState(int pin, int state) {
    throwExceptionIfPinNotCorrect(pin);
    if (isPinStateCorrect(state))
        digitalWrite(pin, state);
    else
        throw WiringException("Wrong pin state: " + to_string(state));

}

void Pins::setPullUpOrDownMode(int pin, int pull) {
    throwExceptionIfPinNotCorrect(pin);
    if (isPinPullCorrect(pull))
        pullUpDnControl(pin, pull);
    else
        throw WiringException("Wrong pin pull: " + to_string(pull));

}

void Pins::throwExceptionIfPinNotCorrect(int pin) {
    if (!(((pin >= wPI_0)&&(pin <= wPI_7)) || ((pin >= wPI_21)&&(pin <= wPI_29))))
        throw WiringException("Wrong pin number: " + to_string(pin));
}

bool Pins::isPWMValueCorrect(int value) {
    if (value >= 0 && value <= 1024)
        return true;
    return false;
}

bool Pins::isPinModeCorrect(int mode) {
    if (mode >= INPUT && mode <= PWM_TONE_OUTPUT)
        return true;
    return false;
}

bool Pins::isPinStateCorrect(int state) {
    if (state >= LOW && state <= HIGH)
        return true;
    return false;
}

bool Pins::isPinPullCorrect(int pull) {
    if (pull >= PUD_OFF && pull <= PUD_UP)
        return true;
    return false;
}

bool Pins::setDefault() {
    try {
        for (int i = wPI_0; i <= wPI_7; i++) {
            setPinMode(i, OUTPUT);
            setPinState(i, LOW);
        }
        for (int i = wPI_21; i <= wPI_29; i++) {
            setPinMode(i, OUTPUT);
            setPinState(i, LOW);
        }
    } catch (exception &e) {
        cout << e.what() << endl;
        return false;
    }
    return true;
}

void Pins::setPinInMap(int pin, int mode) {
    pinsMap[pin] = mode;
}

void Pins::printPinsMap() {
    cout << endl << "----Set pins----" << endl;
    for (pair<int, int> pin : pinsMap) {
        string mode;
        switch (pin.second) {
            case INPUT:
            {
                mode = "INPUT";
                break;
            }
            case OUTPUT:
            {
                mode = "OUTPUT";
                break;
            }
            case PWM_OUTPUT:
            {
                mode = "PWM_OUTPUT";
                break;
            }
            case GPIO_CLOCK:
            {
                mode = "GPIO_CLOCK";
                break;
            }
            case SOFT_PWM_OUTPUT:
            {
                mode = "SOFT_PWM_OUTPUT";
                break;
            }
            case SOFT_TONE_OUTPUT:
            {
                mode = "SOFT_TONE_OUTPUT";
                break;
            }
            case PWM_TONE_OUTPUT:
            {
                mode = "PWM_TONE_OUTPUT";
                break;
            }
        }
        cout << "Pin: " << pin.first << "\t|\tMode: " << mode << endl;
    }
}