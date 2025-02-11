#include "ESP8266WiFi.h"
#include "NTPClient.h"
#include "WiFiUdp.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const char *ssid = "pi_wifi";
const char *password = "12345678";

const long utcOffsetInSeconds = 19800;

char daysOfTheWeek[7][12] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

LiquidCrystal_I2C
    lcd(0x27, 16,
        2); // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight(); // Make sure backlight is on

  // Print a message on both lines of the LCD.
  lcd.setCursor(2, 0); // Set cursor to character 2 on line 0
  lcd.print("Setting UP!");

  lcd.setCursor(2, 1); // Move cursor to character 2 on line 1
  // lcd.print("LCD Tutorial");
  // delay(100);
  // lcd.clear();
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
  // lcd.println(" ");

  // lcd.println(timeClient.getFormattedTime());
  //
  // Serial.print(daysOfTheWeek[timeClient.getDay()]);
  //
  // Serial.print(", ");
  // Serial.print(timeClient.getHours());
  // Serial.print(":");
  // Serial.print(timeClient.getMinutes());
  // Serial.print(":");
  // Serial.println(timeClient.getSeconds());
  Serial.println(timeClient.getFormattedTime());
  //
  delay(1000);
  lcd.clear();
}
