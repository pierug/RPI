/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Serial.h
 * Author: adam
 *
 * Created on 8 sierpnia 2017, 19:30
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <wiringSerial.h>
#include "WiringException.h"

using namespace std;

enum Baud{
    BAUD_110=110,
    BAUD_300=300,
    BAUD_600=600,
    BAUD_1200=1200,
    BAUD_2400=2400,
    BAUD_4800=4800,
    BAUD_9600=9600,
    BAUD_14400=14400,
    BAUD_19200=19200,
    BAUD_28800=28800,
    BAUD_38400=38400,
    BAUD_56000=56000,
    BAUD_57600=57600,
    BAUD_115200=115200,
    BAUD_128000=128000,
    BAUD_153600=153600,
    BAUD_230400=230400,
    BAUD_256000=256000,
    BAUD_460800=460800,
    BAUD_921600=921600
};

const int NOT_FOUND = -1;
const int DATA_NOT_AVAILABLE = -1;

class SerialInterface{
public:
    virtual ~SerialInterface() {}
    virtual void open(string,Baud=BAUD_9600)=0;
    virtual void close()=0;
    virtual void putChar(unsigned char)=0;
    virtual void putString(string)=0;
    virtual string getString()=0;
    virtual char getChar()=0;
};

class Serial : public SerialInterface{
public:
    Serial();
    Serial(const Serial& orig);
    virtual ~Serial();
    void close() override;
    char getChar() override;
    string getString() override;
    void open(string, Baud=BAUD_9600) override;
    void putChar(unsigned char) override;
    void putString(string) override;

private:
    bool isDataAvailable();
    int serialID;
    bool isDeviceFound();
    void throwExeptionIfNotSet();
    bool isClosed;
};

#endif /* SERIAL_H */

