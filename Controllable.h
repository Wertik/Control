#ifndef Controllable_h
#define Controllable_h

#include "Arduino.h"

// A perifery that accepts commands.
class Controllable {
    public:
        // Process a String command
        virtual String acceptCommand(String command) = 0;
};

#endif