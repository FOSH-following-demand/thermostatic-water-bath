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

OneWire oneWireObject(pinDataDQ);  //using one wire library and the data pin
DallasTemperature sensorDS18B20(&oneWireObject); // we connect the library to the sensor
LiquidCrystal_I2C lcd(0x27,16,2); // Watch out the address of the lcd screen, could be not the same

/* The creation of the peltier library*/
peltier peltierA;

void setup() {
  /* A, B, enable, pwm */
  /* We create a peltier element */
  peltierA.createPeltier(4,7,6,5);
  /* All the requierd begins and custom character creations */
  lcd.init(); // Init LCD
    lcd.backlight(); //Backlight on
      lcd.createChar(0, bigP); //custom char 1
         lcd.createChar(1, bigH); // custom char 2
          lcd.createChar(2, UsingPID); // custom char 3
           lcd.createChar(3, steadySign); // custom char 4
            lcd.createChar(4, microActivity); // custom char 5

      sensorDS18B20.begin(); //init sensor DS18B20
     sensorDS18B20.setResolution(12);  //12 bit resolution by default, it can be reduced but not increased
  Serial.begin(9600); //default comunication
 /* end begins */

 /*First message lcd and string constants */
  lcd.setCursor(9,0);
  lcd.print("TWB 1.3");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Act:");
  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.setCursor(10,1);
  lcd.print("R:");
/* end messages and strings constants */
}
/* It only work in a "on-off" configuration */

void loop() {
  sensorDS18B20.requestTemperatures(); //request temp from sensor
  lcd.setCursor(4,0);  //put the cursor of the lcd
  lcd.print(sensorDS18B20.getTempCByIndex(0),2); //print the temperature with 2 decimal round
  lcd.setCursor(4,1); //put the cursor of the lcd
  lcd.print(set_temperature,2); //print the final temperature with 2 decimal round

 if (sensorDS18B20.getTempCByIndex(0) < set_temperature){
  peltierA.heat(1,255); //heat to the maximum
  lcd.setCursor(14,0); //put the cursor of the lcd in 14 colum, 1st row
  lcd.write(1); //write custom character number 1,bigH
  lcd.setCursor(12,1); //put the cursor of the lcd in 12 colum, 2nd row
  lcd.print("ht"); //print ht on screen
 }
 else
 {
  peltierA.powerOff(1);  //power off the lcd
  lcd.setCursor(14,0); //put the cursor of the lcd in 14 colum, 1st row
  lcd.write(3); //write custom character number 4,steadySign
  lcd.setCursor(12,1); //put the cursor of the lcd in 12 colum, 2nd row
  lcd.print("0 ");  //print 0 in pwm
 }
}
