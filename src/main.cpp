#include "ESP8266WiFi.h"
#include "NTPClient.h"
#include "WiFiUdp.h"
#include <Arduino.h>
#include <Config.hpp>
#include <LiquidCrystal_I2C.h>

// +5:30 hours for india
const long utcOffsetInSeconds = 19800;

char daysOfTheWeek[7][12] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  timeClient.begin();

  lcd.init();
  lcd.clear();
  lcd.backlight(); // Make sure backlight is on

  lcd.setCursor(0, 0); // Set cursor to character 2 on line 0
  lcd.print("Setting UP!");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  lcd.clear();
}

void loop() {

  timeClient.update();
  lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
  lcd.print("Smart Watch");

  lcd.setCursor(0, 1); // Move cursor to character 0 on line 1

  lcd.print(daysOfTheWeek[timeClient.getDay()]);
  lcd.print(" ");
  lcd.print(timeClient.getHours());
  lcd.print(":");
  lcd.print(timeClient.getMinutes());
  lcd.print(":");
  lcd.print(timeClient.getSeconds());
  Serial.println(timeClient.getFormattedTime());
  delay(1000);
  lcd.clear();
}
