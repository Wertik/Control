#ifndef Led_h
#define Led_h

#include "Arduino.h"
#include "Output.h"

class Led : public Output {
  private:
    String _color = "red";
  public:
    Led(int pin, String color);

    String getColor();

    void setColor(String color);
};

#endif