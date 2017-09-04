#include "SPI.h"

bool isChannel0=false;
bool isChannel1=false;
bool isChannel2=false;

SPI::SPI(SPI_CHANNEL channel, uint64_t speed, SPI_MODE mode) {
    setChannel(channel);
    if (-1 == wiringPiSPISetupMode(channel, speed, mode)) {
        throw WiringException("Cant setup spi");
    }
    spiChannel = channel;
}

SPI::~SPI() {

}

list<char> SPI::readWrite(unsigned char* data, int len) {
    if (len <= 0) {
        len = sizeof(data)/sizeof(*data);
    }
    if (wiringPiSPIDataRW(spiChannel, data, len) == -1) {
        throw WiringException("Cant read write");
    }

    list<char> result(&data[0], &data[0] + len);
    return result;
}

void SPI::setChannel(SPI_CHANNEL channel) {
    switch (channel) {
        case CHANNEL_0:
        {
            if (isChannel0 == false) {
                isChannel0 = true;
            } else {
                throw WiringException("Channel " + to_string(channel) + " is already set");
            }
            break;
        }
        case CHANNEL_1:
        {
            if (isChannel1 == false) {
                isChannel1 = true;
            } else {
                throw WiringException("Channel " + to_string(channel) + " is already set");
            }
            break;
        }
        case CHANNEL_2:
        {
            if (isChannel2 == false) {
                isChannel2 = true;
            } else {
                throw WiringException("Channel " + to_string(channel) + " is already set");
            }
            break;
        }
    }
}
