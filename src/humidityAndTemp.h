/*
Device: DFROBOT SEN0546: CHT8305 Temperature & Humidity Sensor
Wire requires Wire.begin() in main setup

Note: Much of this code is taken from documentation from the dfrobot wiki
https://wiki.dfrobot.com/SKU_SEN0546_I2C_Temperature_and_Humidity_Sensor_Stainless_Steel_Shell
*/
#ifndef _HUMIDITY
#define _HUMIDITY
#include <Arduino.h>
#include <Wire.h>

#define ADDRESS 0x40

extern char dtaUart[15];
extern char dtaLen;
extern uint8_t Data[100];
extern uint8_t buff[100];

// function from the dfrobot wiki
uint8_t readReg(uint8_t reg, const void* pBuf, size_t size);
// returns a float value for the relative humidity
float getHumidity();
// returns a float temperature in celsius.
float getTemp();

#endif
