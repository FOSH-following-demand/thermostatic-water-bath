
/************************************/
/*****This code is DEBUG*************/
/*****This is not a release version**/
/*****Please don't use it in release*/
/************************************/
/*****Juan Blanc***TECSCI 2019*******/
/************************************/
/**********Version 0.0.2*************/
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

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <PID_v1.h>
#include "peltier.h"
#include <Wire.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>


#define SEALEVELPRESSURE_HPA (1020)  //This might need to be adjust

/* pin to connect the DS18B20 sensor */
const int pinDataDQ = 9;

/* Object creation of Temperature sensor and lcdScreen */ 
peltier peltier1;
Adafruit_BME280 bme;

//TIME FOR DRAW!
byte UsingPID[] = {0x06,0x05,0x06,0x15,0x01,0x13,0x15,0x13};
byte notUsingPID[] = {0x04,0x0E,0x15,0x15,0x04,0x0E,0x1F,0x1F};
byte qubit[] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
byte bigH[] = {0x14,0x1C,0x14,0x06,0x09,0x0E,0x08,0x07};
byte steadySign[] = {0x0C,0x10,0x08,0x04,0x18,0x07,0x02,0x02};
byte microActivity[] = {0x0C,0x10,0x10,0x0C,0x02,0x05,0x07,0x05};

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
float temperature_read = 0;

//Pins
int peltierA = 4 ;  //Digital
int peltierB = 7 ;  //Digital
int enablePeltier = 6 ; //Digital
int pwmPeltier = 5 ;    //Used to control the driver

//Define the aggressive and conservative Tuning Parameters
double aggKp=12, aggKi=.80, aggKd=12;
double consKp=8, consKi=.50, consKd=8;


OneWire oneWireObject(pinDataDQ);
DallasTemperature sensorDS18B20(&oneWireObject);
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
LiquidCrystal_I2C lcd(0x27,16,2);  

/* EXPERIMENTAL  */
int pinA = 2; // Interrupt Hardware Pin Digital 2
int pinB = 3; // Interrupt Hardware Pin Digital 3
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent
 
void setup()
{
  
peltier1.createPeltier(peltierA,peltierB,enablePeltier,pwmPeltier);

  //initialize the variables we're linked to
   lcd.init();
    lcd.backlight();
      lcd.createChar(0, qubit);
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
      Serial.println("NoAmbientSensor");
      Setpoint = 25 ; 
      delay(1000);
      lcd.clear();
      delay(1000);
  }

    /* if is ok the sensor, we define the setpoint as the ambient temperature */
    Setpoint = bme.readTemperature();
  

   /*First message lcd and string constants */
  lcd.setCursor(0,0);
  lcd.print("THERMOELECTRIC");
  lcd.setCursor(0,1);
  lcd.print("WATER BATH v1.5");
  delay(1200);
  for (int i=0; i<16 ; i++)
  {
    lcd.setCursor(i,0);
    lcd.write(0);
    lcd.setCursor(i,1);
    lcd.write(0);
    delay(50);
  }
  delay(1200);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Act:");
  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.setCursor(10,1);
  lcd.print("P:");
/* end messages and strings constants */

 /* end begins */
  Input = sensorDS18B20.getTempCByIndex(0);

  
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
      Serial.println("SensorDS18B20Error"); //this line must go in release
      delay(1000);
      lcd.clear();
      delay(1000);
  }
}
/* end safe test */

/*turn the PID on*/
  myPID.SetMode(AUTOMATIC);


   //Configuracion del pin switch del Encoder Rotativo
  pinMode (buttonPin, INPUT_PULLUP);
  //Configuracion de pines y rutinas de interrupcion para Encoder Rotativo
  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(0,PinA,RISING); // Set Interrupt pin A
  attachInterrupt(1,PinB,RISING); // Set interrupt pin B
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
  peltier1.heat(1,Output*30);
   lcd.setCursor(15,0);
   lcd.print(" ");}
  else
  {
    peltier1.heat(1,Output);
     lcd.setCursor(14,0);
      lcd.write(" ");
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

/* Interruption routines for the rotary encoder */
void PinA(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if(reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    Setpoint -= .1  ;
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts

}

void PinB(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    Setpoint += .1 ;
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}
