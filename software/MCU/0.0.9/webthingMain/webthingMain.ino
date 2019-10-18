
/************************************/
/*****This code is DEBUG*************/
/*****This is not a release version**/
/*****Please don't use it in release*/
/************************************/
/*****Juan Blanc***TECSCI 2019*******/
/************************************/
/**********Version 0.0.9*************/
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

#include <PID_v1.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

WebServer Servidor;
AutoConnect       Portal(Servidor);
AutoConnectConfig Config;       // Enable autoReconnect supported on v0.9.4
AutoConnectAux    Timezone;
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>    
#include <Thing.h>
#include <WebThingAdapter.h>
#include <ArduinoJson.h>

/* Task handlers */

TaskHandle_t Task0, Task1, Task2, Task3, Task4;

/* Struct data control */
struct chamber_data {
  double setPoint;
  double temp_act;
  int pwm;
  String message ;
  bool heatOrCool ; 
} chamber;

/* queue to store all the global data */
QueueHandle_t queue;


void setup()
{
  Serial.begin(115200);
  /* Queue declaration for use in tasks*/

  queue = xQueueCreate(1, sizeof(struct chamber_data)) ;

   
  /*                    functionName,HumanAliasName,stack_size,parameters,priority,handler,coreAttachto */
  xTaskCreatePinnedToCore(controlTask, "PID__Control", 2535, NULL, 1, &Task0, 1);
  xTaskCreatePinnedToCore(lcdTask, "LCD_____task", 1500, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(serverTask, "Server", 1000, NULL, 1, &Task2, 1);
  xTaskCreatePinnedToCore(alarmTask, "Alarm_Task", 900, NULL, 1, &Task3, 0);
  xTaskCreatePinnedToCore(temperatureTask, "Temp_Task", 1535, NULL, 1, &Task4, 1);

  Serial.println("Starting Web Server");
  Config.title = "TWB 1.5";
  Config.apid = "TWB-" + String((uint32_t)(ESP.getEfuseMac() >> 32), HEX); //For Unique SSID, we'll use the last 4 digits of the MAC Address
  Config.autoReconnect = false;  // If you have a stored AP, it'll connect
  Config.autoRise = true;      // If you don't have it, change it to true
  Portal.config(Config);  // Catch all the previous config
  
  Servidor.on("/", rootPage); // We define the root page to direct at function rootPage
  Servidor.on("/setSetpoint", handle_setPoint);

  // Establish a connection with an autoReconnect option.
  if (Portal.begin()) {
    /* Nothing else matters */
  }

}

void loop()
{
  Portal.handleClient();
}


/* TASK 1 */

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//TIME FOR DRAW!
byte UsingPID[] = {0x06, 0x05, 0x06, 0x15, 0x01, 0x13, 0x15, 0x13};
byte notUsingPID[] = {0x04, 0x0E, 0x15, 0x15, 0x04, 0x0E, 0x1F, 0x1F};
byte bigP[] = {0x1E, 0x11, 0x11, 0x1E, 0x18, 0x18, 0x18, 0x19};
byte bigH[] = {0x14, 0x1C, 0x14, 0x06, 0x09, 0x0E, 0x08, 0x07};
byte steadySign[] = {0x0C, 0x10, 0x08, 0x04, 0x18, 0x07, 0x02, 0x02};
byte microActivity[] = {0x0C, 0x10, 0x10, 0x0C, 0x02, 0x05, 0x07, 0x05};
byte wifiA[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08};
byte wifiB[] = {0x00, 0x00, 0x00, 0x00, 0x18, 0x04, 0x1A, 0x0A};
byte wifiC[] = {0x00, 0x00, 0x19, 0x04, 0x02, 0x01, 0x01, 0x00};

/*First message lcd and string constants */
void lcdTask(void *parameter)
{
  Serial.println("Starting LCD");
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, bigP);
  lcd.createChar(1, bigH);
  lcd.createChar(2, UsingPID);
  lcd.createChar(3, steadySign);
  lcd.createChar(4, microActivity);
  lcd.createChar(5, wifiA);
  lcd.createChar(6, wifiB);
  lcd.createChar(7, wifiC);
  lcd.clear();
  lcd.setCursor(9, 0);
  lcd.print("TWB 1.5");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP().toString());
  vTaskDelay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Act:");
  lcd.setCursor(0, 1);
  lcd.print("Set:");
  lcd.setCursor(10, 1);
  lcd.print("P:");
  double temp = 0;
  for (;;)
  {

    lcd.setCursor(4, 1);    
      lcd.setCursor(4, 0);
      lcd.print(chamber.temp_act);
      lcd.setCursor(4, 1);
      lcd.print(chamber.setPoint);
      lcd.setCursor(12,1);
      lcd.print(chamber.pwm);
      vTaskDelay(50);
    }

  }

/* TASK 4 */
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

void temperatureTask(void *parameter) {
 
  const int pinDataDQ = 23;
  OneWire oneWireObject(pinDataDQ);
  DallasTemperature sensorDS18B20(&oneWireObject);
  Serial.println("Starting temp sensor");
  sensorDS18B20.begin();
  sensorDS18B20.setResolution(12);
  double temp_actual ;
  for (;;) {
    sensorDS18B20.requestTemperatures();
    temp_actual = sensorDS18B20.getTempCByIndex(0);
    if (temp_actual > 0) {
      Serial.println(temp_actual);
      chamber.temp_act = temp_actual;
    }
    else {
      Serial.print("No hay datos\n");
         }
    vTaskDelay(100);
    Serial.println("Reading Temp");
  }
}
/* END TASK 4 */



String SendHTML(double maintemp, float setpoint) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta http-equiv=\"refresh\" content=\"4\" >\n";
  /* Added by juanstdio */
  ptr += "<link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">\n";
  /* end added */
  ptr += "<title>Thermostatic Water Bath Remote control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";

  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Thermostatic Water Bath 0.0.8</h1>\n";

  ptr += "<p><i class=\"fas fa-temperature-high\"></i>\n";
  ptr += "TEMPERATURE: ";
  ptr += (double)maintemp;
  ptr += " C</p>";
  ptr += "<p><i class=\"fas fa-thermometer\"></i>\n";
  ptr += "SETPOINT: ";
  ptr += (float)setpoint;
  ptr += " C </p>";
  ptr += "<form action=\"/setSetpoint\">\n";
  ptr += "<input type=\"text\" name=\"theSetpoint\" value=\"\"><br> ";
  ptr += "<input type=\"submit\" value=\"SET Setpoint\">";
  ptr += "</form>\n";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}



void handle_setPoint() {
  
  String setFromWeb = Servidor.arg(0);
   
  chamber.setPoint = setFromWeb.toDouble();
    Serial.println("Showdata");
    Serial.println(chamber.setPoint);
    Serial.println(chamber.temp_act);
 String s = "<a href='/'> Redirect... </a> <meta http-equiv=\"refresh\" content=\"0;url=/\">";
  Servidor.send(200, "text/html", s);
  
  }


void rootPage() {
    Serial.println(chamber.setPoint);
    Serial.println(chamber.temp_act);
    Servidor.send(200, "text/html", SendHTML(chamber.temp_act, chamber.setPoint));
    Serial.println("Data send to web");
}

void handle_NotFound() {
  Servidor.send(404, "text/plain", "Not found");
}


/* Server TASK  to handle the data*/


void serverTask(void *parameter){
     for(;;){
      yield();
  }
  vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
}


void controlTask( void * parameter ){
  Serial.println("Starting PID...");
  
//Define Variables we'll be connecting to
double Input, Output;
double Setpoint;
//Pins
int peltierA = 32 ;  //Digital GPIO
int peltierB = 33 ;  //Digital GPIO
int enablePeltier = 25 ; //Digital GPIO
int pwmPeltier = 26 ;    //Used to control the driver GPIO

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=.225, aggKd=8;
double consKp=.3, consKi=.15, consKd=.4;

  PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
  
  peltier thePeltier ;
  
  thePeltier.createPeltier(peltierA,peltierB,enablePeltier,pwmPeltier);

/*turn the PID on*/
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-10, 95);
  double lastTemp = chamber.temp_act ; 
  double gap ;    
for(;;){
  
  if(lastTemp != chamber.temp_act) {  // only calculating the PID value if there is new temperature
    gap  = abs(chamber.setPoint-chamber.temp_act); //distance away from setpoint
    lastTemp = chamber.temp_act ; 
  if (gap < 10)
  {  //we're close to setpoint, use CONSERVATIVE tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
    Serial.println("Conservative mode");
  }
  else
  {
     //we're far from setpoint, use AGGRESIVE tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
     Serial.println("Aggresive mode");
   }

  myPID.Compute();
  if(Output<30){
  chamber.pwm = Output ; 
   thePeltier.heat(1, Output);
   Serial.println("Computed PID, Output now to the peltier");
  }
  else
  {
     chamber.pwm = Output ; 
  }
  vTaskDelay(100);

//Serial.println("KILL TASK PID");
//vTaskDelete(Task0);
}

/* Monitoring */
 lastTemp = chamber.temp_act ;
  vTaskDelay(150);
  }
  }
/* END -- > Task "Control" used to set the pwm in order to heat */





/* Task "Alarm", to fetch if the sensor is plugged in */
void alarmTask(void *parameter)
{
  Serial.println("Starting alarms");
/* Safe test, is the sensor plugged in?  */
for(;;){
  
 vTaskDelay(10);
}
/* END ---> Task "Alarm", to fetch if the sensor is plugged in */
}
