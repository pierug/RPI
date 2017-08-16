#ifndef DHT11_H
#define DHT11_H

#include "Pins.h"

class DHT11 {
public:

    DHT11(uint8_t pin);
    virtual ~DHT11();   
    
    const double getHumidity();
    const double getTemperatureC(); 
    const double getTemperatureF(); 
private:
    uint8_t pin;
    const int MAXTIMINGS = 85;
    
    void initTransmision();

    void getData();
    double humidity;
    double temperatureC;
    double temperatureF;
};

#endif /* DHT11_H */

