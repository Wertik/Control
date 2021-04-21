#ifndef Input_h
#define Input_h

#include "Perifery.h"

class Input : public Perifery {
    private:
    public:
        Input(int pin);
        void setup();
};

#endif