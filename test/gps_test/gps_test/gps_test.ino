#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define GPS_TX D6  // Connects to TX pin of GPS module
#define GPS_RX D7  // Connects to RX pin of GPS module

TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);  

void setup() {
  Serial.begin(9600);       
  gpsSerial.begin(9600);   
}

void loop() {
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
      Serial.print("SPEED (km/h): ");
      Serial.println(gps.speed.kmph());
      Serial.print("ALT (m): ");
      Serial.println(gps.altitude.meters());
      Serial.print("HDOP: ");
      Serial.println(gps.hdop.value() / 10.0);  
      Serial.print("Satellites: ");
      Serial.println(gps.satellites.value());

      char buffer[30];
      sprintf(buffer, "%04d/%02d/%02d, %02d:%02d:%02d", gps.date.year(), gps.date.month(),
              gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());
      Serial.print("Time in UTC: ");
      Serial.println(buffer);
      Serial.println();
    }
  }
}
