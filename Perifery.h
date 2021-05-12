#ifndef Perifery_h
#define Perifery_h

#include "PeriferyType.h"

class Perifery {
    private:
        int _pin;

        PeriferyType _type;
    public:
        Perifery(int pin, PeriferyType type);

        int getPin();

        PeriferyType getType();
};

#endif