/*
Device: DFROBOT SEN0308 Analog Soil Moisture Sensor
Pin used: A0 refer to readme to change pin
*/
#ifndef _MOISTURE
#define _MOISTURE
#include "Arduino.h"
#include <ArduinoJson.h>

#define AIR_MOISTURE 3700   //you need to change this value that you had recorded in the air
#define SUBMERGED_MOISTURE 0 //you need to change this value that you had recorded in the water
#define MOISTURE_PIN 36

// returns a string moisture value such as dry, wet, etc.
String getMoisture();

#endif