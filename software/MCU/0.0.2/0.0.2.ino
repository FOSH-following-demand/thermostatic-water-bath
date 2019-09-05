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

//Pins
int peltierA = 4 ;  //Digital
int peltierB = 7 ;  //Digital
int enablePeltier = 6 ; //Digital
int pwmPeltier = 5 ;    //Used to control the driver

//Variables
float temperature_read = 0.0;

//IMPORTANT
float set_temperature = 55.5;
//END IMPORTANT

/* For PID Control */
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
int PID_value = 0;
int currentPin = 0 ;

// This is for testing
float porcentage = (set_temperature*96.989)/100; //to 98% of power

//PD constants
int kp = 430 ;  int kd = 100;
int PID_p = 0;   int PID_d = 0;

/* pin to connect the DS18B20 sensor */
const int pinDataDQ = 9;

/* Object creation of Temperature sensor and lcdScreen */

OneWire oneWireObject(pinDataDQ);
DallasTemperature sensorDS18B20(&oneWireObject);
LiquidCrystal_I2C lcd(0x27,16,2);

/* Setup */
void setup() {
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
  lcd.print("TWB 1.2");
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
      delay(1000);
      lcd.clear();
      delay(1000);
  }
}
/* end safe test */
}

/*  main loop */
void loop() {
  sensorDS18B20.requestTemperatures();
  lcd.setCursor(4,0);
  lcd.print(sensorDS18B20.getTempCByIndex(0),2);
  lcd.setCursor(4,1);
  lcd.print(set_temperature,2);

  delay(1000);

/* This part is designed to reach the maximum speed, while approching to the end */
  if (porcentage > sensorDS18B20.getTempCByIndex(0))  //Max poweer
  {
    //please heat/cool to max power
 if (sensorDS18B20.getTempCByIndex(0) < set_temperature){
  heatPlease(1,255);
  lcd.setCursor(14,0);
  lcd.write(1);
  lcd.setCursor(12,1);
  lcd.print("Mx");
 }
}
  else    //please use P-D Control
  {
  /* now we request the temperatures to the DS18B20 */
  sensorDS18B20.requestTemperatures();
  temperature_read = sensorDS18B20.getTempCByIndex(0);
  /*Next we calculate the error between the setpoint and the real value*/
  PID_error = set_temperature - temperature_read;
  /*Calculate the P value*/
  PID_p = kp * PID_error;

  /*For derivative we need real time to calculate speed change rate*/
  timePrev = Time;                            // the previous time is stored before the actual time read
  Time = millis();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000;
  /*Now we can calculate the D calue */
  PID_d = kd*((PID_error - previous_error)/elapsedTime);
  /*Final total PID value is the sum of P + I + D */
  PID_value = PID_p + PID_d; //PID_i is zero

  //We define PWM range between 0 and 255
  if(PID_value < 0)
  {    PID_value = 0;    }
  if(PID_value > 255)
  {    PID_value = 255;  }
  //Now we can write the PWM signal to the driver

  previous_error = PID_error;     //Remember to store the previous error for next loop.
  lcd.setCursor(15,1);
  lcd.print(" ");
  lcd.setCursor(4,0);
  lcd.print(sensorDS18B20.getTempCByIndex(0),2);
  lcd.setCursor(4,1);
  lcd.print(set_temperature,1);
   if (100> PID_value){
    lcd.setCursor(15,1);
    lcd.print(" ");
    }

   lcd.setCursor(12,1);
  lcd.print(PID_value);

 if (sensorDS18B20.getTempCByIndex(0) < set_temperature){

  heatPlease(1,PID_value);  /*Now jump to the function */
  lcd.setCursor(14,0);
  lcd.write(1);
 }
if (sensorDS18B20.getTempCByIndex(0) == (set_temperature) && sensorDS18B20.getTempCByIndex(0) <= (set_temperature + 0.15) )
{
  lcd.setCursor(14,0);
  lcd.write(3);
  heatPlease(1,PID_value); //to maintain the temperature
}
  }  /* end of P-D Control */

/* Comp. Activity blink */
lcd.setCursor(15,1);
lcd.write(4);

/* Monitoring */
Serial.println(sensorDS18B20.getTempCByIndex(0),4);
delay(350);
   if (100> PID_value){
    lcd.setCursor(14,1);
    lcd.print(" ");
    }
}

void heatPlease(bool enable, int pwmSet)
{
  /* One side of the peltier */
  digitalWrite(peltierA,HIGH);
  digitalWrite(peltierB,LOW);
 /* both values are accepted , as much as a 1 or a true */
  if (enable == 1 || enable == true && 0>pwmSet<=255)
  {
    digitalWrite(enablePeltier,HIGH);
    analogWrite(pwmPeltier,pwmSet);
  }
  else
  {
    digitalWrite(enablePeltier,LOW);
  }

}

void coolPlease(bool enable,int pwmSet)
{
  /* Other side of the peltier */
  digitalWrite(peltierA,LOW);
  digitalWrite(peltierB,HIGH);
  /* both values are accepted , as much as a 1 or a true */
  if (enable == 1 || enable == true && 0>pwmSet<=255 )
  {
    digitalWrite(enablePeltier,HIGH);
    analogWrite(pwmPeltier,pwmSet);
  }
  else
  {

    digitalWrite(enablePeltier,LOW);
  }
}
