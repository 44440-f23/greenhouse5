#include "soilTemp.h"

OneWire ds(ONE_WIRE_BUS);
DallasTemperature sensors(&ds);

float getSoilTemp(){
    sensors.requestTemperatures();
    return  sensors.getTempCByIndex(0);
}
