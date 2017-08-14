#include <iostream>
#include <cstdlib>
#include "Pins.h"
#include "Serial.h"

using namespace std;

int main(int argc, char** argv) {
    PINS;
    Serial serial;
    char byteGPS = 0;
    int i = 0;
    int h = 0;

    // Buffers for data input
    char inBuffer[300] = "";
    char GPS_RMC[100] = "";
    char GPS_GGA[100] = "";

    try {
        serial.open("/dev/ttyAMA0", Baud::BAUD_4800);
        printf("Starting...\n");
        delay(1000);
        wiringPiSetup();
        while (1) {
            byteGPS = 0;
            byteGPS = serial.getChar();
            while (byteGPS != 'R') {
                byteGPS = serial.getChar();
            }
            GPS_RMC[0] = '$';
            GPS_RMC[1] = 'G';
            GPS_RMC[2] = 'P';
            GPS_RMC[3] = 'R';

            i = 4;
            while (byteGPS != '*') {
                byteGPS = serial.getChar();
                inBuffer[i] = byteGPS;
                GPS_RMC[i] = byteGPS;
                i++;
            }
            byteGPS = 0;
            byteGPS = serial.getChar();
            while (byteGPS != 'A') {
                byteGPS = serial.getChar();
            }
            GPS_GGA[0] = '$';
            GPS_GGA[1] = 'G';
            GPS_GGA[2] = 'P';
            GPS_GGA[3] = 'G';
            GPS_GGA[4] = 'G';
            GPS_GGA[5] = 'A';

            i = 6;
            while (byteGPS != '*') {
                byteGPS = serial.getChar();
                inBuffer[i] = byteGPS;
                GPS_GGA[i] = byteGPS;
                i++;
            }

            // print the GGA sentence to USB
            
            printf("GGA sentence: \n");
            h = 0;
            while (GPS_GGA[h] != 42) {
                delay(10);
                printf("%c", GPS_GGA[h]);
                h++;
            }
            printf("\n");

            // print the RMC sentence to USB
            printf("RMC sentence: \n");
            h = 0;
            while (GPS_RMC[h] != 42) {
                delay(10);
                printf("%c", GPS_RMC[h]);
                h++;
            }
            printf("\n");
        }
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    return 0;
}

