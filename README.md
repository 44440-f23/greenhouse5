## Project: SensorPlatform4 - GreenHouse5
#### Github: https://github.com/44440-f23/greenhouse5
#### Team:
- Braeden
- Luke
- Daniel
- Kevin

#### Project Description:
Sensor Project to update a campus greenhouse alert system. The system is broken up into 6 greenhouse devices that communicate to a base station with Json (See main.cpp for Json example). This is the code for the greenhouse 5 device. The base station takes readings from the greenhouse devices and based on their readings may send an alert to the manager of the greenhouses.

#### Board and Expansion
- Firebeetle 2 esp32 e
  - https://wiki.dfrobot.com/FireBeetle_Board_ESP32_E_SKU_DFR0654
- Gravity: IO Shield for FireBeetle 2 (ESP32-E/M0)
  - https://wiki.dfrobot.com/Gravity_Shield_for_FireBeetle_2_SKU_DFR0762

#### Sensors:
- DS18B20 Digital Temperature Sensor
  - Get it working with this tutorial using the DallasTemperature library to simplify code https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/ 
- DFROBOT SEN0308 Analog Soil Moisture Sensor
  - https://wiki.dfrobot.com/Waterproof_Capacitive_Soil_Moisture_Sensor_SKU_SEN0308 
- DFROBOT DFR0026 Analog Ambient Light Sensor
  - https://wiki.dfrobot.com/DFRobot_Ambient_Light_Sensor_SKU_DFR0026 
- DFROBOT SEN0546: CHT8305 Temperature & Humidity Sensor (used to take soil temperature)
  - https://wiki.dfrobot.com/SKU_SEN0546_I2C_Temperature_and_Humidity_Sensor_Stainless_Steel_Shell

### Development Notes:
#### How to find analog or digital pin
Software analog and digital pins were found for expansion board by going to the wiki https://wiki.dfrobot.com/Gravity_Shield_for_FireBeetle_2_SKU_DFR0762#target_4 Then, compare the board represented on the Digital or Analog Ports section to the pin on the esp32 e board, from the esp32 e wiki https://www.dfrobot.com/product-2195.html A digital pin should have Dx beside it. For example: pin 0 is D5.

#### Moisture calibration values when colaborating
Everyone might have different calibration values. The value returned by the device will be proportionate to the calibration values. From how we have it described in Json “soilM”: 12.53, we might be able to send a float value that is: analogRead(PIN) / (AIR_CAL_VAL - SUBMERGED_CAL_VAL) = rough percentage of "dryness”.

#### Values from the light sensor
The light sensor can sense illuminance (lux) but it cannot measure in lux. The value taken from analogRead is a ratiometric value, an int between 0 - 1023 based on this formula: (1023 / 3.3V) * (Voltage from device) = ratiometric value, and based on what the device can detect within its range of 1-6000 Lux.
For why data cannot be converted to lux, see https://community.silabs.com/s/article/kba-sens-0107-si1153-33-ambient-light-sensing-and-lux-calculation?language=en_US
and FAQ here https://wiki.dfrobot.com/DFRobot_Ambient_Light_Sensor_SKU_DFR0026 
