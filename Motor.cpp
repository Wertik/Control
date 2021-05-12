#include "Arduino.h"
#include "Servo.h"

#include "Motor.h"

Motor::Motor(int pin) : Output(pin, MOTOR) {
}

void Motor::setAngle(int angle) {
    this->_angle = angle;
}

int Motor::readAngle() {
    this->setAngle(this->_servo.read());
    return this->getAngle();
}

bool Motor::changeAngle(int angle) {

    if (angle > this->max || angle < this->min) {
        return false;
    }

    this->setAngle(angle);
    this->_servo.write(angle);
    return true;
}

void Motor::setup() {
    this->_servo.attach(this->getPin());
    this->readAngle();
}

String Motor::acceptCommand(String command) {
    int angle = command.toInt();
    if (!this->changeAngle(angle)) {
        return "400;Angle has to be between 0 and 180.";
    }

    return "200;Moved the motor.";
}

String Motor::composeState() {
    return String(this->_angle);
}