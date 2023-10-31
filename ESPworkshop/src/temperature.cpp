#include "temperature.h"

OneWire ds(ONE_WIRE_BUS);
DallasTemperature sensors(&ds);

float getTemp(){
    sensors.requestTemperatures();
    return  sensors.getTempCByIndex(0);
}