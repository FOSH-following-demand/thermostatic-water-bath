
/************************************/
/*****This code is DEBUG*************/
/*****This is not a release version**/
/*****Please don't use it in release*/
/************************************/
/*****Juan Blanc***TECSCI 2019*******/
/************************************/
/**********Version 0.0.6.1*************/
/************************************/

/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

        #include "peltier.h"
        #include "EEPROM.h"
EEPROMClass SETPOINT("eeprom3", 0x500);
EEPROMClass  TEMP_ACT("eeprom2", 0x500);
EEPROMClass  PWM("eeprom1", 0x500);
EEPROMClass  MESSAGES("eeprom0", 0xFFF);

    #include <PID_v1.h>
    #include <WiFi.h>
    #include <WebServer.h>
    #include <AutoConnect.h>

    WebServer Servidor;
AutoConnect       Portal(Servidor);
AutoConnectConfig Config;       // Enable autoReconnect supported on v0.9.4
AutoConnectAux    Timezone;
    
    #include "task0.h"
    #include "task1.h"
    #include "task2.h"
    #include "task3.h"
    #include "task4.h"

/* Task handlers */

TaskHandle_t Task0, Task1, Task2, Task3, Task4; 
// cola;
struct Data{
  double setPoint;
  float temp_act;
  String message ;
  int pwm;
};


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 THE WEB</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperatura</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humedad</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";


String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = 12;
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}
String readDHTTemperature() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  float t = 1234;
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  return String();
}
void rootPage() {
 //   sensorDS18B20.requestTemperatures();
 double temp;
   
    Servidor.send(200, "text/html", index_html);
  }
/* queue to store all the global data */
xQueueHandle cola;
void setup()
{

Serial.begin(115200);
cola = xQueueCreate( 1, sizeof( struct Data ) );

 // Input = sensorDS18B20.getTempCByIndex(0);
 // Setpoint = temperature_read;
  /*                    functionName,HumanAliasName,stack_size,parameters,priority,handler,coreAttachto */
  xTaskCreatePinnedToCore(controlTask,"PID__Control",6535,NULL,1,&Task0,1);
  xTaskCreatePinnedToCore(lcdTask,"LCD_____task",10000,NULL,1,&Task1,0);
  xTaskCreatePinnedToCore(serverTask,"Server",1000000,NULL,2,&Task2, 1);
  xTaskCreatePinnedToCore(alarmTask,"Alarm_Task",5500,NULL,1,&Task3,0);
  xTaskCreatePinnedToCore(temperatureTask,"Temp_Task",6535,NULL,0,&Task4,1);

 Serial.println("Starting Web Server");
 Config.title = "TWB 1.5";
  Config.apid = "TWB-" + String((uint32_t)(ESP.getEfuseMac() >> 32), HEX); //For Unique SSID, we'll use the last 4 digits of the MAC Address
  Config.autoReconnect = true;  // If you have a stored AP, it'll connect
  Portal.config(Config);  //Catch all the previous config
  Servidor.on("/", rootPage); // We define the root page to direct at function rootPage
  

  // Establish a connection with an autoReconnect option.
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }

}

void loop()
{
}
