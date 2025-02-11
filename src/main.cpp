#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include "watch.h"
#include <Arduino.h>
#include <Config.hpp>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// SoftwareSerial gsmSerial(GSM_TX, GSM_RX);

// This flag is used to indicate that the SOS button is pressed
// bool sendSMS = false;
// Numbers number = {"7907489077", "7907489077"};

// +5:30 hours for india
const long utcOffsetInSeconds = 19800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

char daysOfTheWeek[7][12] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time

void setup() {
  Serial.begin(BAUD_RATE);
  WiFi.begin(SSID, PASSWORD);
  timeClient.begin();
  lcd_initialize(lcd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(HALD_SECOND);
    Serial.print(".");
  }
  lcd.clear();
}

void loop() { update_time(lcd, timeClient, daysOfTheWeek); }
