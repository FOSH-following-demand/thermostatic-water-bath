

/* Task "Alarm", to fetch if the sensor is plugged in */
void alarmTask(void *parameters)
{
  Serial.println("Starting alarms");
/* Safe test, is the sensor plugged in?  */
while (true)/*
  { sensorDS18B20.requestTemperatures();
    if (sensorDS18B20.getTempCByIndex(0) < (-4))
    {
      lcd.setCursor(0,0);
      lcd.print("ALARM!!");
      lcd.setCursor(0,1);
      lcd.print("S1-chk n' reboot");
      Serial.println("SensorDS18B20Error");
      lcd.clear();
      vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
      }
      vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
      
}*/
/* end safe test */
vTaskDelay(10);
}
/* END ---> Task "Alarm", to fetch if the sensor is plugged in */
