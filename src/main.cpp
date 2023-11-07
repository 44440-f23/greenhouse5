/*
Project: SensorPlatform4 - GreenHouse5
Github: https://github.com/44440-f23/greenhouse5
Team: Braeden, Luke, Daniel, Kevin

Main Device: firebeetle 2 esp32 e
Expansion Device: Gravity: IO Shield for FireBeetle 2 (ESP32-E/M0)
*/
#include <ArduinoJson.h>
#include <Arduino.h>
#include "moisture.h"
#include "humidityAndTemp.h"
#include "light.h"
#include "soilTemp.h"
#include "mesh.h"

#define SENSOR_READ_INTERVAL 2000 // 2 seconds

StaticJsonDocument<200> doc;
unsigned long last_check = 0;

void setup() {
  Serial.begin(9600);
  doc["id"] = 5;
  last_check = 0;

  sensors.begin();
  Wire.begin(); // required by Humidity and Temp sensor
  setupMesh();
}

void loop() {
  if(millis() - last_check > SEND_INTERVAL*1000){ // Matchest send message from mesh, may need to reduce.
    last_check = millis();
    doc["soilM"] = getMoisture();
    doc["soilT"] = getSoilTemp();
    doc["temp"] = getTemp();
    doc["humidity"] = getHumidity();
    doc["lightS"] = getLight();
    // serializeJsonPretty(doc, Serial); // debug code
    serializeJson(doc, mesh_msg);
  }
  
  mesh.update();
}
