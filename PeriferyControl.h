#ifndef PeriferyControl_h
#define PeriferyControl_h

#include "Input.h"
#include "Output.h"
#include <map>
#include <iostream>
#include <iterator>

typedef std::map<int, Output> OutputMap;
typedef std::map<int, Input> InputMap;

class PeriferyControl {
    private:
        OutputMap _outputs;
        InputMap _inputs;
    public:
        void addOutput(Output output);

        Output getOutput(int pin);

        void addInput(Input input);

        Input getInput(int pin);
};

#endif