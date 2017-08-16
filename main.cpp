#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "MLX90614.h"
#include "DHT11.h"
#include "Pins.h"
using namespace std;

int main(void) {
    printf("Raspberry Pi wiringPi DHT11 Temperature test program\n");

    if (wiringPiSetup() == -1)
        exit(1);

    while (1) {
        
    }

    return (0);
}