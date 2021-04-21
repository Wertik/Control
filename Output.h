#ifndef Output_h
#define Output_h

#include "Perifery.h"

class Output : public Perifery {
    private:
        bool _state = false;
    public:
        Output(int pin);

        bool switchState();

        void setState(bool state);

        bool getState();

        bool readState();

        void setup();
};

#endif