#include "Input.h"
#include "Arduino.h"
#include "Perifery.h"

Input::Input(int pin, PeriferyType type) : Perifery(pin, type) {
}

void Input::setup() {
    pinMode(getPin(), INPUT);
}