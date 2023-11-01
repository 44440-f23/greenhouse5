/*
Device: DFROBOT DFR0026 Analog Ambient Light Sensor

Note: Cannot convert data to lux
See https://community.silabs.com/s/article/kba-sens-0107-si1153-33-ambient-light-sensing-and-lux-calculation?language=en_US
and FAQ here https://wiki.dfrobot.com/DFRobot_Ambient_Light_Sensor_SKU_DFR0026 
*/
#ifndef _LIGHT
#define _LIGHT

// This defines a pin to Analogue Pin 3. Refer to temeperature.h to see how I found this.
#define LIGHT_ANALOG_PIN 35
/* 
returns a ratiometric value, an int between 0 - 1023 based on this formula: (1023 / 3.3V) * (Voltage from device) = ratiometric value
based on what the device can detect within it's range of 1-6000 Lux.
*/
int getLight();
#endif