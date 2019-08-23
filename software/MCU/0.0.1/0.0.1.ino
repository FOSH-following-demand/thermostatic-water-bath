/************************************/
/****This code is DEBUG**************/
/***This is not a release version****/
/***Please don't use it in release***/
/************************************/
/*****Juan Blanc****TECSCI 2019******/
/************************************/


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

byte heat1[8] = {
  0b00101,
  0b00000,
  0b01010,
  0b10000,
  0b00100,
  0b00001,
  0b00100,
  0b10000
};
byte heat2[8] = {
  0b01101,
  0b10000,
  0b00110,
  0b00000,
  0b01001,
  0b10100,
  0b00000,
  0b01010
};
int sensorPin = 1 ;
int currentPin = 0 ;
/* Control part  */

int peltierA = 4 ;  //DIGITAL
int peltierB = 7 ;  //DIGITAL
int enablePeltier = 6 ; //DIGITAL
int pwmPeltier = 5 ;  //DIGITAL


LiquidCrystal_I2C lcd(0x27,16,2);

double kp = 2;
double ki = 5;
double kd = 1;
const int pinDatosDQ = 9;

OneWire oneWire(9);

// declare as sensor referenec by passing oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// declare your device address
// YOUR ADDRESS GOES HERE!!!!
DeviceAddress tempSensor = {0x28, 0xA5, 0x84, 0x01, 0x09, 0x00, 0x00, 0x7C};

// A Variable to hold the temperature you retrieve
float tempC;

void setup(){
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  //sensorDS18B20.begin();
  Serial.begin(9600);

  //sensorDS18B20.setResolution(tempSensor,11);

  //Serial.println(sensorDS18B20.getResolution(tempSensor));
  sensors.setResolution(tempSensor, 12);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  /* this was enable in debug mode */
  //Serial.print("Sensor Resolution: ");
  //Serial.println(sensors.getResolution(tempSensor), DEC);
  //Serial.println();

}

void loop(){
  float current = analogRead(currentPin);
  float sensorValue = analogRead(sensorPin);
  sensors.requestTemperaturesByAddress(tempSensor); // Send the command to get temperatures

  // Get the temperature that you told the sensor to measure
  tempC = sensors.getTempC(tempSensor);
  lcd.setCursor(0,0);
  lcd.print(tempC,4);
 String dataToSend = String(tempC,6);
  Serial.println(dataToSend);
  //Serial.println(tempC,6);
  lcd.setCursor(7,0);
  lcd.print("C");
  lcd.setCursor(0,1);

float mVperAmp = 104.7; // use 100 for 20A Module and 66 for 30A Module
                        // change int for float to get more accurate reading

int RawValue= 0;
int ACSoffset = 2500;
float Voltage = 0; //voltage measuring
float Amps = 0;// Current measuring
 RawValue = analogRead(currentPin);//reading the value from the analog pin
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp) * (-1);
  lcd.print(Amps);
  lcd.setCursor(6,1);
  lcd.print("A");
float  set_temp = 45.00;
 if (tempC < set_temp){

  lcd.setCursor(8,0);
  lcd.print("Heating!");
  lcd.setCursor(8,1);
  lcd.print("Pel.Ext");
  heatPlease(1);
 }
if (tempC > (set_temp + 0.05) && tempC <= (set_temp + 0.10 )){
  heatPlease(0);
  lcd.setCursor(8,0);
  lcd.print("Good!    ");
  lcd.setCursor(8,1);
  lcd.print("Pel.Stop");
}
 if (tempC > (set_temp + 0.10) ){
  lcd.setCursor(8,0);
  lcd.print("Cooling!");
  lcd.setCursor(8,1);
  lcd.print("Pel");
 // coolPlease(1);

  }
  delay(1000);
}




void heatPlease(bool enable)
{
  digitalWrite(peltierA,HIGH);
  digitalWrite(peltierB,LOW);
  if (enable == 1 || enable == true)
  {
    digitalWrite(enablePeltier,HIGH);
    analogWrite(pwmPeltier,255);
  }
  else
  {
    digitalWrite(enablePeltier,LOW);
    analogWrite(pwmPeltier,0);
  }

}
void coolPlease(bool enable)
{
  digitalWrite(peltierA,LOW);
  digitalWrite(peltierB,HIGH);
  if (enable == 1 || enable == true)
  {
    digitalWrite(enablePeltier,HIGH);
    analogWrite(pwmPeltier,255);
  }
  else
  {
    digitalWrite(enablePeltier,LOW);
    analogWrite(pwmPeltier,0);
  }
}
