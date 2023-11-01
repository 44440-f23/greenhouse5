#include <Arduino.h>
#include "light.h"

int getLight(){
    return analogRead(LIGHT_ANALOG_PIN);
}