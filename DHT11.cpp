#include "DHT11.h"

DHT11::DHT11(uint8_t pin) : pin(pin) {
    humidity = 0;
    temperatureC = 0;
    temperatureF = 0;
}

DHT11::~DHT11() {

}
  
const double DHT11::getHumidity() {
    getData();
    return humidity;
}

const double DHT11::getTemperatureC() {
    getData();
    return temperatureC;
}

const double DHT11::getTemperatureF() {
    getData();
    return temperatureF;
}

void DHT11::getData() {
    unsigned char laststate = HIGH;
    unsigned char counter = 0;
    unsigned char j = 0, i;
    float f;
    int dht11_dat[5] = {0, 0, 0, 0, 0};
    initTransmision();
    for (i = 0; i < MAXTIMINGS; i++) {
        counter = 0;
        while (PINS.getPinState(pin) == laststate) {
            counter++;
            delayMicroseconds(1);
            if (counter == 255) {
                break;
            }
        }
        laststate = PINS.getPinState(pin);
        if (counter == 255)
            break;
        if ((i >= 4) && (i % 2 == 0)) {
            dht11_dat[j / 8] <<= 1;
            if (counter > 16)
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }
    if ((j >= 40) &&
            (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF))) {
        f = dht11_dat[2] * 9. / 5. + 32;
        printf("Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
                dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f);
        humidity = (dht11_dat[0]*10 + dht11_dat[1]) / 10;
        temperatureC = (dht11_dat[2]*10 + dht11_dat[3]) / 10;
        temperatureF = f;
    }
}

void DHT11::initTransmision() {
    PINS.setPinMode(pin, OUTPUT);
    PINS.setPinState(pin, LOW);
    delay(18);
    PINS.setPinState(pin, HIGH);
    delayMicroseconds(40);
    PINS.setPinMode(pin, INPUT);
}

