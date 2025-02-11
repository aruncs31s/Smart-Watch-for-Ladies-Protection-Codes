#include "NTPClient.h"
#include <LiquidCrystal_I2C.h>
void lcd_initialize(LiquidCrystal_I2C &_lcd);

void update_time(LiquidCrystal_I2C &_lcd, NTPClient &_timeClient,
                 char daysOfTheWeek[7][12]);
