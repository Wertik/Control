#ifndef Perifery_h
#define Perifery_h

class Perifery {
    private:
        int _pin;
    public:
        Perifery(int pin);

        int getPin();
};

#endif