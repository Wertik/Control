#ifndef Util_cpp
#define Util_cpp

#include "Arduino.h"
#include <iostream>

using namespace std;

namespace utl {
    enum State {
        OFF,
        ON,
        NULL_STATE = -1
    };

    inline String split(String data, char separator, int index) {
        int found = 0;
        int strIndex[] = {0, -1};
        int maxIndex = data.length() - 1;

        for (int i=0; i <= maxIndex && found <= index; i++){
            if (data.charAt(i) == separator || i == maxIndex){
                found++;
                strIndex[0] = strIndex[1] + 1;
                strIndex[1] = (i == maxIndex) ? i + 1 : i;
            }
        }

        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
    }

    inline State stringToBoolean(String str) {
        str.toLowerCase();
        str.trim();
        
        if (str.equals("true") || str.equals("1") || str.equals("yes")) {
            return ON;
        } else if (str.equals("false") || str.equals("0") || str.equals("no")) {
            return OFF;
        } else return NULL_STATE;
    }

    template<typename Base, typename T>
    inline bool instanceof(const T*) {
        return is_base_of<Base, T>::value;
    }
}

#endif