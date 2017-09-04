#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "MLX90614.h"
#include "DHT11.h"
#include "Pins.h"

#include <signal.h>
#include <unistd.h>

using namespace std;

void interupt1(int sig);

int main(void) {
    if (wiringPiSetup() == -1)
        exit(1);
    PINS.setPinMode(0,OUTPUT);
    PINS.setPinMode(2,OUTPUT);

    signal(SIGALRM, interupt1);   
    ualarm(5000, 5000);

    while (1) {
        PINS.setPinState(0,LOW);
        delay(200);
        PINS.setPinState(0,HIGH);
        delay(100);
    }

    return (0);
}

void interupt1(int sig){
    unsigned int i;
    i++;
    if(sig == SIGALRM)
    {
        if(i%2)
            PINS.setPinState(2,LOW);
        else
            PINS.setPinState(2,HIGH);
    }
}