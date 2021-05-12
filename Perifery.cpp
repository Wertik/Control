#include "Perifery.h"

Perifery::Perifery(int pin, PeriferyType type) : _pin(pin), _type(type) {
}

int Perifery::getPin() {
    return this->_pin;
}

PeriferyType Perifery::getType() {
    return this->_type;
}