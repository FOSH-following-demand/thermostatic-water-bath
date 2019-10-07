#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
//TIME FOR DRAW!
byte UsingPID[] = {0x06,0x05,0x06,0x15,0x01,0x13,0x15,0x13};
byte notUsingPID[] = {0x04,0x0E,0x15,0x15,0x04,0x0E,0x1F,0x1F};
byte bigP[] = {0x1E,0x11,0x11,0x1E,0x18,0x18,0x18,0x19};
byte bigH[] = {0x14,0x1C,0x14,0x06,0x09,0x0E,0x08,0x07};
byte steadySign[] = {0x0C,0x10,0x08,0x04,0x18,0x07,0x02,0x02};
byte microActivity[] = {0x0C,0x10,0x10,0x0C,0x02,0x05,0x07,0x05};


void lcdTask(void *parameters)
{
Serial.println("Starting LCD");

  lcd.init();
    lcd.backlight();
      lcd.createChar(0, bigP);
         lcd.createChar(1, bigH);
          lcd.createChar(2, UsingPID);
           lcd.createChar(3, steadySign);
            lcd.createChar(4, microActivity);
            lcd.clear();
    /*First message lcd and string constants */
  lcd.setCursor(9,0);
  lcd.print("TWB 1.5");
  vTaskDelay(1500);
  lcd.setCursor(9,0);
  lcd.print("       ");
  lcd.setCursor(0,0);
  lcd.print("Act:");
  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.setCursor(10,1);
  lcd.print("P:");
for(;;)
{
  lcd.setCursor(4,1);
  lcd.setCursor(4,0);
  double temp;
  TEMP_ACT.get(0,temp);
  lcd.print(temp);
  vTaskDelay(100);

}
vTaskDelay(10);
  
}
