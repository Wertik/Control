#include "Led.h"

#include "Arduino.h"

#include "Output.h"
#include "Stateful.h"
#include "Util.h"

using namespace utl;

Led::Led(int pin, String color) : Output(pin, LED), _color(color) {
}

// ---- Led specific methods

String Led::getColor() {
    return this->_color;
}

void Led::setColor(String color) {
    this->_color = color;
}

// ---- Inherited from Stateful

String Led::composeState() {
    return this->_color + ":" + this->getState();
}

void Led::changeState(bool state) {
    if (this->getState() != state) {
        this->setState(state);

        Serial.println("Changing state to " + String(state));
        digitalWrite(this->getPin(), this->getState() ? HIGH : LOW); 
    }
}

bool Led::readState() {
    this->setState(digitalRead(getPin()));
    return this->getState();
}

String Led::acceptCommand(String command) {

    State state = stringToBoolean(command);
    
    if (state == NULL_STATE) {
        return "400;Invalid LED state.";
    }

    if (this->getState() == state) {
        return "400;The LED is already in this state.";
    }

    // Change the state
    this->changeState(state);

    return this->readState() == state ? "200;Changed the state." : "500;Failed to change the state.";
}

void Led::setup() {
    pinMode(this->getPin(), OUTPUT);
    this->readState();
}