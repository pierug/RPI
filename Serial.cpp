#include "Serial.h"

Serial::Serial() {
    serialID = NOT_FOUND;
    isClosed = false;
}

Serial::Serial(const Serial& orig) {
}

Serial::~Serial() {
    if (isClosed == false)
        close();
}

void Serial::close() {
    throwExeptionIfNotSet();
    serialClose(serialID);
    isClosed = true;
}

char Serial::getChar() {
    throwExeptionIfNotSet();
    if (isDataAvailable())
        return serialGetchar(serialID);
    return '\t';
}

string Serial::getString() {
    throwExeptionIfNotSet();
    string in="";
    while (isDataAvailable()) {
        in += static_cast<char> (serialGetchar(serialID));
    }
    return in;
}

void Serial::open(string device, Baud baud) {
    serialID = serialOpen(device.c_str(), baud);
    throwExeptionIfNotSet();
}

void Serial::putChar(unsigned char out) {
    throwExeptionIfNotSet();
    serialPutchar(serialID, out);
}

void Serial::putString(string out) {
    throwExeptionIfNotSet();
    serialPuts(serialID, out.c_str());
}

void Serial::throwExeptionIfNotSet() {
    if (NOT_FOUND == serialID)
        throw WiringException("Serial device not found: "+to_string(serialID));
}

bool Serial::isDataAvailable() {
    if (serialDataAvail(serialID) != DATA_NOT_AVAILABLE)
        return true;
    return false;
}
