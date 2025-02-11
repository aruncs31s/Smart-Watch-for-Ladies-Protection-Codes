#include "watch.h"

void lcd_initialize(LiquidCrystal_I2C &_lcd) {
  _lcd.init();
  _lcd.clear();
  _lcd.backlight();     // Make sure backlight is on
  _lcd.setCursor(0, 0); // Set cursor to character 2 on line 0
  _lcd.print("Setting UP!");
  _lcd.setCursor(0, 1); // Set cursor to character 2 on line 1
  _lcd.print("Please Wait...");
}
void update_time(LiquidCrystal_I2C &_lcd, NTPClient &_timeClient,
                 char daysOfTheWeek[7][12]) {
  _timeClient.update();
  _lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
  _lcd.print("Smart Watch");

  _lcd.setCursor(0, 1); // Move cursor to character 0 on line 1

  _lcd.print(daysOfTheWeek[_timeClient.getDay()]);
  _lcd.print(" ");
  _lcd.print(_timeClient.getHours());
  _lcd.print(":");
  _lcd.print(_timeClient.getMinutes());
  _lcd.print(":");
  _lcd.print(_timeClient.getSeconds());
  Serial.println(_timeClient.getFormattedTime());
  delay(1000);
  _lcd.clear();
}
