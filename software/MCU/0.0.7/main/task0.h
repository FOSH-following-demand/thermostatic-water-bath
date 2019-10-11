


void controlTask( void * parameter ){
  Serial.println("Starting PID...");

//Define Variables we'll be connecting to
double Input, Output;
float temperature_read = 0;
double Setpoint = 0;
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
Setpoint = 32;

  for(;;){
    Input = 0 ;   
    double gap = abs(Setpoint-Input); //distance away from setpoint

  if (gap < 10)
  {  //we're close to setpoint, use CONSERVATIVE tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use AGGRESIVE tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
   }

  myPID.Compute();
  if(Output<30){
//   lcd.setCursor(12,1);
 ////  lcd.print(Output);
 //  lcd.setCursor(15,0);
 //  lcd.print(" ");
   thePeltier.heat(1, Output);
  }
  else
  {
 //    lcd.setCursor(14,0);

 //     lcd.print("nada");
  }
/* Monitoring */
//Serial.println(sensorDS18B20.getTempCByIndex(0),4);

delay(150);
Serial.println("Calculate PID good");
  }
   vTaskDelay(10);
  }
/* END -- > Task "Control" used to set the pwm in order to heat */
