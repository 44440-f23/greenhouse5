/*
Device: DFROBOT DFR0026 Analog Ambient Light Sensor
Pin used: A3 refer to readme to change pin
*/
#ifndef _LIGHT
#define _LIGHT

#define LIGHT_ANALOG_PIN 35
/* 
returns a ratiometric value, an int between 0 - 1023 based on this formula: (1023 / 3.3V) * (Voltage from device) = ratiometric value
based on what the device can detect within it's range of 1-6000 Lux.
*/
int getLight();
#endif