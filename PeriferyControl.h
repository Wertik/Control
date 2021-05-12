#ifndef PeriferyControl_h
#define PeriferyControl_h

#include "Arduino.h"

#include "Input.h"
#include "Output.h"

#include <memory>
#include <map>
#include <iostream>
#include <iterator>

typedef std::map<int, Output*> OutputMap;
typedef std::map<int, Input*> InputMap;

class PeriferyControl {
    private:
        OutputMap _outputs;
        InputMap _inputs;
    public:
        void setup();

        String distributeCommand(int pin, String command);

        String composeState();

        // ---- Output

        void addOutput(Output* output);

        Output* getOutput(int pin);

        // --- Input

        void addInput(Input* input);

        Input* getInput(int pin);
};

#endif