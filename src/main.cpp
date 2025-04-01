#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include "watch.h"
#include <Arduino.h>
#include <Config.hpp>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial gsmSerial(GSM_TX, GSM_RX);
TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);

// This flag is used to indicate that the SOS button is pressed
bool sendSMS = false;
Numbers number = {"6300347998", "6300347998"};

// +5:30 hours for india
const long utcOffsetInSeconds = 19800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

char daysOfTheWeek[7][12] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    gsmSerial.write(Serial.read());
  }
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}

void send_sos(const char *theNumber, const String &coordinates) {
  gsmSerial.println("AT"); // Returns OK if handshake successful
  updateSerial();

  gsmSerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  gsmSerial.println("AT+CMGS=\"+91" + String(theNumber) + "\"");
  updateSerial();
  gsmSerial.print("Emergency! Location: " + coordinates);
  updateSerial();
  gsmSerial.write(26);
}

void initiate_sms() { sendSMS = true; }

void IRAM_ATTR theISR() {
  Serial.println("Button Pressed");
  initiate_sms();
}

void setup() {
  Serial.begin(BAUD_RATE);
  gsmSerial.begin(9600);
  gpsSerial.begin(GPS_BAUD_RATE);
  attachInterrupt(D5, theISR, FALLING);
  attachInterrupt(D8, theISR, RISING);

  WiFi.begin(SSID, PASSWORD);
  timeClient.begin();
  lcd_initialize(lcd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(HALD_SECOND);
    Serial.print(".");
  }
  lcd.clear();
}

void loop() {
  update_time(lcd, timeClient, daysOfTheWeek);

  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (sendSMS && gps.location.isUpdated()) {
    String coordinates = "Lat: " + String(gps.location.lat(), 6) + 
                         ", Lon: " + String(gps.location.lng(), 6);
    send_sos(number.parent, coordinates);
    send_sos(number.police,coordinates);
    sendSMS = false;
  }
}
