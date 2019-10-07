   #include <Wire.h>
    #include <OneWire.h>
#include <DallasTemperature.h>


void temperatureTask(void *parameters){
/* pin to connect the DS18B20 sensor */

const int pinDataDQ = 17;
OneWire oneWireObject(pinDataDQ);
DallasTemperature sensorDS18B20(&oneWireObject);
  Serial.println("Starting temp sensor");
         sensorDS18B20.begin();
     sensorDS18B20.setResolution(12);
  for(;;){
        sensorDS18B20.requestTemperatures();
        double temp_actual = sensorDS18B20.getTempCByIndex(0);
        TEMP_ACT.put(0,temp_actual);
        Serial.println(temp_actual);        
    vTaskDelay(10);
  }
  vTaskDelete( NULL );
}
