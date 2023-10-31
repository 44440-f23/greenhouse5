#include "humidity.h"
#include <Arduino.h>
#include <Wire.h>

char dtaUart[15];
char dtaLen = 0;
uint8_t Data[100] = {0};
uint8_t buff[100] = {0};

float getHumidity(){
    readReg(0x00, buff, 4);
    uint16_t data, data1;
    float temp;
    float hum;
    data = buff[0] << 8 | buff[1];
    data1 = buff[2] << 8 | buff[3];
    temp = ((float)data * 165 / 65535.0) - 40.0;
    hum =  ((float)data1 / 65535.0) * 100;
    return hum;
}

uint8_t readReg(uint8_t reg, const void* pBuf, size_t size){
  if (pBuf == NULL) {
    Serial.println("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  Wire.beginTransmission(ADDRESS);
  Wire.write(&reg, 1);
  if ( Wire.endTransmission() != 0) {
    return 0;
  }
  delay(20);
  Wire.requestFrom(ADDRESS, (uint8_t) size);
  for (uint16_t i = 0; i < size; i++) {
    _pBuf[i] = Wire.read();
  }
  return size;
}

