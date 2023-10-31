#include "ArduinoJson.h"
#include <Arduino.h>
StaticJsonDocument<200> doc;
//moisture variables/values
#define baseStationID = 0;
const int AirValue = 3700;   //you need to change this value that you had recorded in the air
const int WaterValue = 0; //you need to change this value that you had recorded in the water
String soilCondition;
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;


//Temp and Humidity Sensor
#include "Wire.h"
#define address 0x40
char dtaUart[15];
char dtaLen = 0;
uint8_t Data[100] = {0};
uint8_t buff[100] = {0};
uint8_t readReg(uint8_t reg, const void* pBuf, size_t size);

//Temperature Sensor 
#include "OneWire.h"
#include "DallasTemperature.h"
float getTemp();
#define ONE_WIRE_BUS 2 //DS18S20 Signal pin on digital 2
//Temperature chip i/o
OneWire ds(ONE_WIRE_BUS);  // on digital pin 2
DallasTemperature sensors(&ds);


void setup() {
  Serial.begin(9600);
  doc["greenhouse"] = 5;
  Wire.begin();
  sensors.begin();
}
uint16_t data, data1;
float temp;
float hum;
void loop() {    
  //Moisture Sensor Code
  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
  //Serial.println(soilMoistureValue);

    if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
    {
      soilCondition = "Very Wet";
    }
    else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
    {
      soilCondition = "Wet";
    }
    else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
    {
      soilCondition = "Dry";
    }
    else{
      soilCondition = "Error";
    }
    doc["moisture"] = soilCondition;
    delay(100);

  //temp and humidity sensor loop code
  readReg(0x00, buff, 4);
  data = buff[0] << 8 | buff[1];
  data1 = buff[2] << 8 | buff[3];
  temp = ((float)data * 165 / 65535.0) - 40.0;
  hum =  ((float)data1 / 65535.0) * 100;

  sensors.requestTemperatures();
  doc["temperature"] = sensors.getTempCByIndex(0);
  int val;
  val=analogRead(A0);   //connect grayscale sensor to Analog 0
  doc["light"] = val;
  //Serial.println(val,DEC);//print the value to serial

  //Serial.println(sensors.getTempCByIndex(0));
  //float temperature = getTemp();
  //Serial.println(temperature);
  delay(2000);

  doc["humidity"] = hum;
  // Serial.print("temp(C):");
  // Serial.print(temp);
  // Serial.print("\t");
  // Serial.print("hum(%RH):");
  // Serial.println(hum);
  serializeJsonPretty(doc, Serial);
  delay(500);
}
uint8_t readReg(uint8_t reg, const void* pBuf, size_t size)
{
  if (pBuf == NULL) {
    Serial.println("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  Wire.beginTransmission(address);
  Wire.write(&reg, 1);
  if ( Wire.endTransmission() != 0) {
    return 0;
  }
  delay(20);
  Wire.requestFrom(address, (uint8_t) size);
  for (uint16_t i = 0; i < size; i++) {
    _pBuf[i] = Wire.read();
  }
  return size;

//light sensor
int val;
val=analogRead(A0);   //connect grayscale sensor to Analog 0
doc["light"] = val;
//Serial.println(val,DEC);//print the value to serial
delay(100);

//Temperature Sensor
sensors.requestTemperatures();
doc["temperature"] = sensors.getTempCByIndex(0);
//Serial.println(sensors.getTempCByIndex(0));
// float temperature = getTemp();
// Serial.println(temperature);
delay(2000);
}

// float getTemp(){
//   //returns the temperature from one DS18S20 in DEG Celsius

//   byte data[12];
//   byte addr[8];

//   if ( !ds.search(addr)) {
//       //no more sensors on chain, reset search
//       ds.reset_search();
//       return -1000;
//   }

//   if ( OneWire::crc8( addr, 7) != addr[7]) {
//       Serial.println("CRC is not valid!");
//       return -1001;
//   }

//   if ( addr[0] != 0x10 && addr[0] != 0x28) {
//       Serial.print("Device is not recognized");
//       return -1002;
//   }

//   ds.reset();
//   ds.select(addr);
//   ds.write(0x44,1); // start conversion, with parasite power on at the end

//   byte present = ds.reset();
//   ds.select(addr);
//   ds.write(0xBE); // Read Scratchpad


//   for (int i = 0; i < 9;  i++  ) { // we need 9 bytes
//     data[i] = ds.read();
//   }

//   ds.reset_search();

//   byte MSB = data[1];
//   byte LSB = data[0];

//   float tempRead = ((MSB << 8) | LSB); //using two's compliment
//   float TemperatureSum = tempRead / 16;

//   return TemperatureSum;

// }

void taskSendMessage( String moisture, double temp, double digitalTemp, double humid, int light) {
}
