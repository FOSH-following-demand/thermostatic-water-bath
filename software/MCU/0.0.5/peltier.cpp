 #include "peltier.h"
 #include "Arduino.h"
/*    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

/* We are going to use a vector to store the pins
   where the cell is connected, so if you are using multiple peltier
   cells, you can connect more without loosing program memory
*/

/* First we declare the two functions to use the internal adc */
void analogWrite(int pin, uint8_t val);
void setupPWM(int pin);


void peltier::createPeltier(uint8_t A,uint8_t B,uint8_t E, uint8_t pwm)
  {
   vectorPin[0] = A, vectorPin[1] = B, vectorPin[2] = E, vectorPin[3] = pwm ;
   pinMode(vectorPin[0],OUTPUT);
   pinMode(vectorPin[1],OUTPUT);
   pinMode(vectorPin[2],OUTPUT);
   pinMode(vectorPin[3],OUTPUT);
   setupPWM(vectorPin[3]);

  }

bool peltier::cool(bool activate, uint8_t pwmValue){
    /* SIDE A*/
    digitalWrite(vectorPin[0],LOW);
    digitalWrite(vectorPin[1],HIGH);

    /* This is Just to ensure than the PWM Value is in range
       and the enable is activated */
  if ((activate == 1) || (activate == true) && (0>pwmValue<=255) ){
    digitalWrite(vectorPin[2],HIGH);
    analogWrite(vectorPin[3],pwmValue);
    return 1;
  }
  else{
    digitalWrite(vectorPin[2],LOW);
    return 0;
  }}

bool peltier::heat(bool activate, uint8_t pwmValue)
  {
    /* SIDE B with PWM to control the driver */
    digitalWrite(vectorPin[0],HIGH);
    digitalWrite(vectorPin[1],LOW);

    /* This is Just to ensure than the PWM Value is in range
       and the enable is activated */
    if ((activate == 1) || (activate == true) && (0>pwmValue<=255) ){
    digitalWrite(vectorPin[2],HIGH);
    analogWrite(vectorPin[3],pwmValue);
    return 1;}
  else{
    digitalWrite(vectorPin[2],LOW);
    return 0;
  }}


bool peltier::powerOff(bool confirm)
  {
    /* Power ALL OFF */
    digitalWrite(vectorPin[0],LOW);
     digitalWrite(vectorPin[1],LOW);
     if((confirm == 1) || (confirm == true))
      digitalWrite(vectorPin[2],LOW);

       analogWrite(vectorPin[3],0);
  }

void peltier::heatFast()
  {
    /* In case than you can't use PWM with drivers, you can use this function and the PWM output as watchdog */
    digitalWrite(vectorPin[0],HIGH); // SIDE A
     digitalWrite(vectorPin[1],LOW);  // SIDE A
      digitalWrite(vectorPin[2],HIGH); // ENABLE NOW
       analogWrite(vectorPin[3],255);   // MAX PWM

  }

void peltier::coolFast()
  {
  /* In case than you can't use PWM with drivers, you can use this function and the PWM output as watchdog */
   digitalWrite(vectorPin[0],LOW);  // SIDE B
    digitalWrite(vectorPin[1],HIGH); // SIDE B
     digitalWrite(vectorPin[2],HIGH); // ENABLE NOW
      analogWrite(vectorPin[3],255);   // MAX PWM

  }



  int _adc = 0;
  int ADC_MAP[48]={
  -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1
  };

  #define PWM_FREQ 32000
  //change this to set PWM output resolution. 8--> 0~255 values
  #define PWM_RESOLUTION 8
  //#define USE_SIGMADELTA

  void setupPWM(int pin)
  {
  pinMode(pin, OUTPUT);
  #ifdef USE_SIGMADELTA
  sigmaDeltaSetup(_adc, PWM_FREQ);
  sigmaDeltaAttachPin(pin, _adc);
  #else

  ledcSetup(_adc, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(pin, _adc);
  #endif
  ADC_MAP[pin] = _adc;

  _adc = _adc + 1;
  }

  void analogWrite(int pin, uint8_t val)
  {
  if(ADC_MAP[pin]==-1)
  setupPWM(pin);
  #ifndef USE_SIGMADELTA
  ledcWrite(ADC_MAP[pin], val);
  #else
  sigmaDeltaWrite(ADC_MAP[pin], val);
  #endif
  }
