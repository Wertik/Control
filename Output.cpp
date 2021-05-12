#include "Arduino.h"

#include "Output.h"
#include "Perifery.h"

Output::Output(int pin, PeriferyType type) : Perifery(pin, type) {
}