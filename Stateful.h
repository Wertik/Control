#ifndef Stateful_h
#define Stateful_h

class Stateful {
    private:
        bool _state = false;
    public:
        virtual bool switchState() {
            changeState(!this->_state);
            return this->_state;
        }

        // Set the variable and change the state of the physical perifery
        virtual void changeState(bool state) = 0;

        // Set the state variable
        virtual void setState(bool state) {
            this->_state = state;
        }

        // Read the physical state of the perifery.
        virtual bool readState() = 0;

        virtual bool getState() {
            return this->_state;
        }
};

#endif