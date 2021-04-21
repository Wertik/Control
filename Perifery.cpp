#include "Perifery.h"

Perifery::Perifery(int pin) : _pin(pin) {
}

int Perifery::getPin() {
    return this->_pin;
}