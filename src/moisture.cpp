#include "moisture.h"

String getMoisture(){
    String soilCondition;
    int intervals = (AIR_MOISTURE - SUBMERGED_MOISTURE)/3;
    int soilMoistureValue = 0;

    soilMoistureValue = analogRead(MOISTURE_PIN);  //put Sensor insert into soil (Kevin: what does this mean?)

    if(soilMoistureValue > SUBMERGED_MOISTURE && soilMoistureValue < (SUBMERGED_MOISTURE + intervals))
    {
        soilCondition = "Very Wet";
    }
    else if(soilMoistureValue > (SUBMERGED_MOISTURE + intervals) && soilMoistureValue < (AIR_MOISTURE - intervals))
    {
        soilCondition = "Wet";
    }
    else if(soilMoistureValue < AIR_MOISTURE && soilMoistureValue > (AIR_MOISTURE - intervals))
    {
        soilCondition = "Dry";
    }
    else{
        soilCondition = "Error";
    }
    return soilCondition;
}