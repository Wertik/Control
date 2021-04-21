#include "Output.h"
#include "Arduino.h"
#include "Perifery.h"

Output::Output(int pin) : Perifery(pin) {
}

bool Output::getState() {
    return this->_state;
}

bool Output::readState() {
    this->_state = digitalRead(getPin());
}

bool Output::switchState() {
    setState(!this->_state);
    return this->_state;
}

void Output::setState(bool state) {
    if (this->_state != state) {
        this->_state = state;
        digitalWrite(getPin(), this->_state ? HIGH : LOW); 
    }
}

void Output::setup() {
    pinMode(getPin(), OUTPUT);
}