#define GPS_TX D6 // This should connect to the TX pin of the GPS module
#define GPS_RX D5 // This should connect to the RX pin of the GPS module
#define BAUD_RATE 9600
#define GPS_BAUD_RATE 9600

#if defined(ARDUINO)
#define GSM_TX 3
#define GSM_RX 2
#elif defined(ESP8266)
#define GSM_TX D5 // This should connect to the TX pin of the GPS module
#define GSM_RX D6 // This should connect to the RX pin of the GPS module
#endif
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;

// Create an instance of Software Serial
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);

void setup() {
  // Serial Monitor
  Serial.begin(115200);

  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  gpsSerial.begin(GPS_BAUD_RATE);
  Serial.println("Software Serial started at 9600 baud rate");
}

void loop() {
  // This sketch displays information every time a new sentence is correctly
  // encoded.
  unsigned long start = millis();

  while (millis() - start < 1000) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }
    if (gps.location.isUpdated()) {
      Serial.print("LAT: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("LONG: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("SPEED (km/h) = ");
      Serial.println(gps.speed.kmph());
      Serial.print("ALT (min)= ");
      Serial.println(gps.altitude.meters());
      Serial.print("HDOP = ");
      Serial.println(gps.hdop.value() / 100.0);
      Serial.print("Satellites = ");
      Serial.println(gps.satellites.value());
      Serial.print("Time in UTC: ");
      Serial.println(String(gps.date.year()) + "/" + String(gps.date.month()) +
                     "/" + String(gps.date.day()) + "," +
                     String(gps.time.hour()) + ":" + String(gps.time.minute()) +
                     ":" + String(gps.time.second()));
      Serial.println("");
    }
  }
}
