

/* Task "Alarm", to fetch if the sensor is plugged in */
void alarmTask(void *parameter)
{
  Serial.println("Starting alarms");
/* Safe test, is the sensor plugged in?  */
for(;;){
  delay(100);
   
 vTaskDelay(10);
}
/* END ---> Task "Alarm", to fetch if the sensor is plugged in */
}
