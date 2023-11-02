/*
Device: DS18B20 Digital Temperature Sensor
Pin used: D5 refer to readme to change pin
sensors variable requires sensors.begin() in main setup
*/
#ifndef _SOIL_TEMP
#define _SOIL_TEMP

#include "OneWire.h"
#include "DallasTemperature.h"

#define ONE_WIRE_BUS 0 // DS18B20 Signal pin on digital 5.
extern OneWire ds;  // on digital pin 5
extern DallasTemperature sensors;

// returns the temperature taken by DS18S20 as float Celsius
float getSoilTemp();

#endif
