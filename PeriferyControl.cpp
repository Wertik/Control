#include "PeriferyControl.h"

#include "Arduino.h"

#include "Input.h"
#include "Output.h"
#include "Util.h"

#include <memory>

void PeriferyControl::addInput(Input* input) {
    this->_inputs.insert(std::make_pair(input->getPin(), input));

    Serial.print("perif ctrl | Added input perifery ");
    Serial.println(input->getPin());
}

void PeriferyControl::addOutput(Output* output) {
    this->_outputs.insert(std::make_pair(output->getPin(), output));

    Serial.print("perif ctrl | Added output perifery ");
    Serial.println(output->getPin());
}

Output* PeriferyControl::getOutput(int pin) {
    return this->_outputs.find(pin)->second;
}

Input* PeriferyControl::getInput(int pin) {
    return this->_inputs.find(pin)->second;
}

void PeriferyControl::setup() {
    // Setup outputs
    for (auto it = this->_outputs.begin(); it != this->_outputs.end(); ++it) {
        it->second->setup();
    }

    // Setup inputs
    for (auto it = this->_inputs.begin(); it != this->_inputs.end(); ++it) {
        it->second->setup();
    }
}

String PeriferyControl::composeState() {
    String data = "";
    for (auto it = this->_outputs.begin(); it != this->_outputs.end(); ++it) {
        data += String(it->first) + ":" + String(it->second->getType()) + ":" + it->second->composeState();
        if (std::next(it) != this->_outputs.end()) {
            data += ";";
        }
    }
    return data;
}

String PeriferyControl::distributeCommand(int pin, String command) {
    Serial.println("perif ctrl | accepted " + command + " for pin " + String(pin));

    Output* out = this->getOutput(pin);

    if (out == NULL) {
        Serial.println("perif ctrl | No perifery under pin " + String(pin));
        return "400;Invalid perifery";
    }

    return out->acceptCommand(command);
}