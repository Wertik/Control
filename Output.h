#ifndef Output_h
#define Output_h

#include "Arduino.h"

#include "Perifery.h"
#include "Controllable.h"
#include "Stateful.h"

class Output : public Perifery, public Controllable {
    public:
        Output(int pin, PeriferyType type);

        virtual void setup() {
            pinMode(this->getPin(), OUTPUT);
        }

        virtual String acceptCommand(String command) = 0;

        virtual String composeState() = 0;
};

#endif