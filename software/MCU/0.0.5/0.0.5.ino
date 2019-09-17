
/************************************/
/*****This code is DEBUG*************/
/*****This is not a release version**/
/*****Please don't use it in release*/
/************************************/
/*****Juan Blanc***TECSCI 2019*******/
/************************************/
/**********Version 0.0.5*************/
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
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <PID_v1.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include "peltier.h"

//needed for library
#define SEALEVELPRESSURE_HPA (1020)

/* pin to connect the DS18B20 sensor */
const int pinDataDQ = 17;

/* Object creation of Temperature sensor and lcdScreen */
Adafruit_BME280 bme;
peltier thePeltier ;

//TIME FOR DRAW!
byte UsingPID[] = {0x06,0x05,0x06,0x15,0x01,0x13,0x15,0x13};
byte notUsingPID[] = {0x04,0x0E,0x15,0x15,0x04,0x0E,0x1F,0x1F};
byte bigP[] = {0x1E,0x11,0x11,0x1E,0x18,0x18,0x18,0x19};
byte bigH[] = {0x14,0x1C,0x14,0x06,0x09,0x0E,0x08,0x07};
byte steadySign[] = {0x0C,0x10,0x08,0x04,0x18,0x07,0x02,0x02};
byte microActivity[] = {0x0C,0x10,0x10,0x0C,0x02,0x05,0x07,0x05};

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
float temperature_read = 0;

//Pins
int peltierA = 32 ;  //Digital GPIO
int peltierB = 33 ;  //Digital GPIO
int enablePeltier = 25 ; //Digital GPIO
int pwmPeltier = 26 ;    //Used to control the driver GPIO

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=.225, aggKd=8;
double consKp=.3, consKi=.15, consKd=.4;


OneWire oneWireObject(pinDataDQ);
DallasTemperature sensorDS18B20(&oneWireObject);

PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

LiquidCrystal_I2C lcd(0x27,16,2);

/* EXPERIMENTAL  */

int pinA = 2; // InterruptHardware Pin Digital GPIO 2
int pinB = 15; // Interrupt Hardware Pin Digital GPIO 15
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

const byte  buttonPin = 8;
byte        oldButtonState = HIGH;  // assume switch open because of pull-up resistor
byte        buttonState;
const unsigned long debounceTime = 10;  // milliseconds
unsigned long buttonPressTime;  // when the switch last changed state
bool buttonPressed = 0; // a flag variable

void setup()
{
thePeltier.createPeltier(peltierA,peltierB,enablePeltier,pwmPeltier);

  //initialize the variables we're linked to
   lcd.init();
    lcd.backlight();
      lcd.createChar(0, bigP);
         lcd.createChar(1, bigH);
          lcd.createChar(2, UsingPID);
           lcd.createChar(3, steadySign);
            lcd.createChar(4, microActivity);
       sensorDS18B20.begin();
     sensorDS18B20.setResolution(12);
  Serial.begin(9600);
  if (!bme.begin(0x76)) {
    lcd.setCursor(0,0);
      lcd.print("ALARM!!");
      lcd.setCursor(0,1);
      lcd.print("B1- No Amb sensor");
      Serial.println("ErrorSensorAmbiente");
      delay(1000);
      lcd.clear();
      delay(1000);
  }
   /*First message lcd and string constants */
  lcd.setCursor(9,0);
  lcd.print("TWB 1.5");
  delay(1500);
  lcd.setCursor(9,0);
  lcd.print("       ");
  lcd.setCursor(0,0);
  lcd.print("Act:");
  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.setCursor(10,1);
  lcd.print("P:");
/* end messages and strings constants */

 /* end begins */
  Input = sensorDS18B20.getTempCByIndex(0);
  Setpoint = temperature_read;

/* Safe test, is the sensor plugged in? */
sensorDS18B20.requestTemperatures();
if (sensorDS18B20.getTempCByIndex(0) < (-4))
{
  while (true)
  {
      lcd.setCursor(0,0);
      lcd.print("ALARM!!");
      lcd.setCursor(0,1);
      lcd.print("S1-chk n' reboot");
      Serial.println("SensorDS18B20Error"); 
      delay(1000);
      lcd.clear();
      delay(1000);
  }
}
/* end safe test */

/*turn the PID on*/
  myPID.SetMode(AUTOMATIC);

Setpoint = bme.readTemperature();
  /* END SETUP */
}

void loop()
{
  sensorDS18B20.requestTemperatures();
  lcd.setCursor(4,0);
  lcd.print(sensorDS18B20.getTempCByIndex(0),2);
  lcd.setCursor(4,1);
  lcd.print(Setpoint);
  Input = sensorDS18B20.getTempCByIndex(0);

  double gap = abs(Setpoint-Input); //distance away from setpoint

  if (gap < 10)
  {  //we're close to setpoint, use CONSERVATIVE tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
    lcd.setCursor(14,0);
    lcd.write(2);
  }
  else
  {
     //we're far from setpoint, use AGGRESIVE tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
      lcd.setCursor(14,0);
      lcd.write(2);
  }

  myPID.Compute();

  if(Output<30){
  lcd.setCursor(12,1);
  lcd.print(Output);
   lcd.setCursor(15,0);
   lcd.print(" ");
   thePeltier.heat(1, Output);
  }
  else
  {
     lcd.setCursor(14,0);

      lcd.print(" ");
  }

  if(Output = 0 || Output < 2)
  {
  lcd.setCursor(15,0);

  lcd.write(3);  //Stedy sign
  }

/* Monitoring */
Serial.println(sensorDS18B20.getTempCByIndex(0),4);

/* Comp. Activity blink */
lcd.setCursor(15,1);
lcd.write(4);

}
