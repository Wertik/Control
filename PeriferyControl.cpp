#include "PeriferyControl.h"
#include "Input.h"
#include "Output.h"

void PeriferyControl::addInput(Input input) {
    this->_inputs.emplace(input.getPin(), input);
}

void PeriferyControl::addOutput(Output output) {
    this->_outputs.emplace(output.getPin(), output);
}

Output PeriferyControl::getOutput(int pin) {
    
}

Input PeriferyControl::getInput(int pin) {
    
}