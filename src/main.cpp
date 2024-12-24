/*
 * Source:
 * https://randomnerdtutorials.com/esp8266-nodemcu-neo-6m-gps-module-arduino/
 */

#include "Arduino.h"
#include "Config.h"
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// All Global Object and variable declerations
TinyGPSPlus gps;
bool isEmergency;
Location location = {0, 0, 0};
Numbers number = {"7902340086", "7902504188"}; // Police and Parent

// Create an instance of Software Serial
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);

// This will continue to execute if there is no signal to the GPS module
void getLocation() {
  while (!location._gps_status) {
    if (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
      location._gps_status ^= 1;
    }
  }
  location._lat = gps.location.lat();
  location._long = gps.location.lng();
  location._gps_status ^= 1;
}
bool send_SOS() {
  /*
   * @param none
   * @return -> used to indicate a sucessful SOS
   */
  getLocation();

  return 1;
}

void setup() {
  Serial.begin(115200);
  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  gpsSerial.begin(GPS_BAUD_RATE);
  // Make the ISR quick
  attachInterrupt(PUSH_BUTTON, send_SOS, FALLING);
}

void loop() {

  unsigned long start = millis();
  while (millis() - start < 1000) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }

    location = getLocation();
    //   if (gps.location.isUpdated()) {
    //     Serial.print("LAT: ");
    //     Serial.println(gps.location.lat(), 6);
    //     Serial.print("LONG: ");
    //     Serial.println(gps.location.lng(), 6);
    //   }
  }
}
