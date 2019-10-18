#include <Arduino.h>
#include "peltier.h"
#include <PID_v1.h>

#include <Thing.h>
#include <WebThingAdapter.h>

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/* Webthings Things! */
WebThingAdapter *adapter;

const char *sensorTypes[] = {"MultiLevelSensor", "Sensor", nullptr};
ThingDevice weather("ds18b20", "DS18B20 Temp Sensor", sensorTypes);
ThingProperty weatherTemp("temperature", "The temperature measured by the sensor", NUMBER, "LevelProperty");

struct chamber_data {
  double setPoint;
  double temp_act;
  int pwm;
  String message ;
  bool heatOrCool ;
} chamber;

/* Temperature sensor */
const int pinDataDQ = 23;
OneWire oneWireObject(pinDataDQ);
DallasTemperature sensorDS18B20(&oneWireObject);
double temp_actual ;

void readData()
{
  sensorDS18B20.requestTemperatures();
  temp_actual = sensorDS18B20.getTempCByIndex(0);
  ThingPropertyValue value;
   value.number = temp_actual;
    weatherTemp.setValue(value);

}
void setup() {
    Serial.begin(115200);
    Serial.println("Starting Web Server");
    Serial.println("Starting temp sensor");
    sensorDS18B20.begin();
    sensorDS18B20.setResolution(12);
    adapter = new WebThingAdapter("weathersensor", WiFi.localIP());
    weather.addProperty(&weatherTemp);
    adapter->addDevice(&weather);
    adapter->begin();
}

void loop() {
  readData();
  adapter->update();
}
