/*
Device: DS18S20 Digital Temperature Sensor
*/
#ifndef _TEMP
#define _TEMP

#include "OneWire.h"
#include "DallasTemperature.h"

/*
In order to find which pin to use, go to the wiki for the board expansion below.
https://wiki.dfrobot.com/Gravity_Shield_for_FireBeetle_2_SKU_DFR0762#target_4
Here, compare the board represented on the Digital Ports section (3.1) to the pin on the esp32 e board,
from the esp32 e wiki below.
https://www.dfrobot.com/product-2195.html
The pin should have Dx beside it. For example: pin 0 is D5.
*/
#define ONE_WIRE_BUS 0 // DS18S20 Signal pin on digital 5
extern OneWire ds;  // on digital pin 5
extern DallasTemperature sensors;

// returns the temperature taken by DS18S20 as float Celsius
float getTemp();

#endif