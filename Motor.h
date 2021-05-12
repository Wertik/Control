#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#include "Motor.h"

#include "Servo.h"
#include "Output.h"

class Motor : public Output {
    private:
        int _angle = 0;
        Servo _servo;

    public:

        const int max = 180;
        const int min = 0;

        Motor(int pin);

        bool changeAngle(int angle);

        void setAngle(int angle);

        int getAngle() {
            return this->_angle;
        }

        int readAngle();

        // --- Output

        virtual void setup();

        virtual String acceptCommand(String command);

        virtual String composeState();
};

#endif