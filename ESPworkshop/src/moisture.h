/*
Device: DS18B20 Digital Temperature Sensor
*/
#ifndef _MOISTURE
#define _MOISTURE
#include "Arduino.h"
#include <ArduinoJson.h>

//moisture variables/values
#define AIR_MOISTURE 3700   //you need to change this value that you had recorded in the air
#define SUBMERGED_MOISTURE 0 //you need to change this value that you had recorded in the water

// returns a string moisture value such as dry, wet, etc.
String getMoisture();

#endif