#include <Arduino.h>
#include "peltier.h"
#include <stdio.h>
#include <PID_v1.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Thing.h>
#include <WebThingAdapter.h>


WebServer Servidor;
AutoConnect       Portal(Servidor);
AutoConnectConfig Config;       // Enable autoReconnect supported on v0.9.4
AutoConnectAux    Timezone;

/* Webthings Things! */
WebThingAdapter *adapter;

const char *sensorTypes[] = {"MultiLevelSensor", "Sensor", nullptr};
ThingDevice weather("ds18b20", "Chamber Temperature", sensorTypes);
ThingProperty weatherTemp("temperature", "The temperature measured by the sensor", NUMBER, "LevelProperty");

const char *ssid = "YourWiFiData";
const char *password = "yourPassword";

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
float temp_actual ;

void readData()
{
  delay(100);
  sensorDS18B20.requestTemperatures();
  temp_actual = sensorDS18B20.getTempCByIndex(0);
  Serial.println(temp_actual);
  ThingPropertyValue value;
   value.number = temp_actual;
    weatherTemp.setValue(value);
delay(100);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting Web Server");
    Serial.println("Starting temp sensor");
    sensorDS18B20.begin();
    sensorDS18B20.setResolution(12);

        WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
{
    delay(500);
    Serial.print(".");
}

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
Serial.println(WiFi.localIP());

   adapter = new WebThingAdapter("weathersensor", WiFi.localIP());
   weather.addProperty(&weatherTemp);
   adapter->addDevice(&weather);
   adapter->begin();
}

void loop() {
  readData();
  adapter->update();

}
