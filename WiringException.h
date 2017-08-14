#ifndef WIRINGEXCEPTION_H
#define WIRINGEXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

class WiringException : public exception {
private:
    string msg;
public:

    WiringException(string msg) : msg(msg) {

    }

    virtual const char* what() const throw () {
        return msg.c_str();
    }
};

#endif