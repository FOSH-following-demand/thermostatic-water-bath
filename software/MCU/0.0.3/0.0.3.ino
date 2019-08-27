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
#include "peltier.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//TIME FOR DRAW!
byte UsingPID[] = {0x00,0x00,0x00,0x00,0x04,0x0E,0x1F,0x1F};
byte notUsingPID[] = {0x04,0x0E,0x15,0x15,0x04,0x0E,0x1F,0x1F};
byte bigP[] = {0x1E,0x11,0x11,0x1E,0x18,0x18,0x18,0x19};
byte bigH[] = {0x14,0x1C,0x14,0x06,0x09,0x0E,0x08,0x07};
byte steadySign[] = {0x0C,0x10,0x08,0x04,0x18,0x07,0x02,0x02};
byte microActivity[] = {0x0C,0x10,0x10,0x0C,0x02,0x05,0x07,0x05};

//Variables
float temperature_read = 0.0;

//IMPORTANT
float set_temperature = 25.5;
//END IMPORTANT


/* pin to connect the DS18B20 sensor */
const int pinDataDQ = 9;

/* Object creation of Temperature sensor and lcdScreen */

OneWire oneWireObject(pinDataDQ);
DallasTemperature sensorDS18B20(&oneWireObject);
LiquidCrystal_I2C lcd(0x27,16,2);

/* This is new */
peltier peltierA;

void setup() {
  /* A, B, enable, pwm */
  peltierA.createPeltier(4,7,6,5);
  /* All the requierd begins and custom character creations */
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
 /* end begins */

 /*First message lcd and string constants */
  lcd.setCursor(9,0);
  lcd.print("TWB 1.3");
  delay(1500);
  lcd.setCursor(9,0);
  lcd.print("       ");
  lcd.setCursor(0,0);
  lcd.print("Act:");
  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.setCursor(10,1);
  lcd.print("R:");
/* end messages and strings constants */
}

void loop() {
   sensorDS18B20.requestTemperatures();
  lcd.setCursor(4,0);
  lcd.print(sensorDS18B20.getTempCByIndex(0),2);
  lcd.setCursor(4,1);
  lcd.print(set_temperature,2);

 if (sensorDS18B20.getTempCByIndex(0) < set_temperature){
  peltierA.heat(1,255);
  lcd.setCursor(14,0);
  lcd.write(1);
  lcd.setCursor(12,1);
  lcd.print("ht");
 }
 else
 {
  peltierA.powerOff(1);
  lcd.setCursor(14,0);
  lcd.write(3);
  lcd.setCursor(12,1);
  lcd.print("0 ");
 }
}
