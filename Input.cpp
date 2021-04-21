#include "Input.h"
#include "Arduino.h"
#include "Perifery.h"

Input::Input(int pin) : Perifery(pin) {
}

void Input::setup() {
    pinMode(getPin(), INPUT);
}