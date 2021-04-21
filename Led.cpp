#include "Arduino.h"
#include "Led.h"

#include "Output.h"

Led::Led(int pin, String color) : Output(pin), _color(color) {
}

String Led::getColor() {
    return this->_color;
}

void Led::setColor(String color) {
    this->_color = color;
}