#ifndef Led_h
#define Led_h

#include "Arduino.h"

#include "Output.h"
#include "Stateful.h"

class Led : public Output, public Stateful {
  private:
    String _color = "red";
  public:
    Led(int pin, String color);

    // --- Led specififc

    String getColor();

    void setColor(String color);

    // --- Inherited from Output

    virtual void setup();

    virtual String acceptCommand(String command);

    virtual String composeState();

    // --- Stateful

    virtual void changeState(bool state);

    virtual bool readState();

};

#endif