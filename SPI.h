#ifndef SPI_H
#define SPI_H

#include <wiringPiSPI.h>
#include "WiringException.h"
#include <list>
#include <iostream>
#include <cstring>
using namespace std;
enum SPI_CHANNEL{
    CHANNEL_0=0,
    CHANNEL_1=1,
    CHANNEL_2=2
};
enum SPI_MODE{
    MODE_0=0,
    MODE_1=1,
    MODE_2=2,
    MODE_3=3
};
class SPIInterface{
public:
    virtual list<char> readWrite(unsigned char *data, int len=0)=0;
};

class SPI :public SPIInterface{
public:
    SPI(SPI_CHANNEL channel = CHANNEL_0, uint64_t speed= 500000,SPI_MODE mode = MODE_0);
    
    virtual ~SPI();
    list<char> readWrite(unsigned char *data, int len=0) override;
private:
    void setChannel(SPI_CHANNEL channel);
    SPI_CHANNEL spiChannel;
};

#endif /* SPI_H */

