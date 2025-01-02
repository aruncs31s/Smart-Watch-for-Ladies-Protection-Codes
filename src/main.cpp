
#include "Arduino.h"
#include "Config.h"
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// All Global Object and variable declerations
TinyGPSPlus gps;
bool isEmergency;
Location location = {0, 0, 0};
Numbers number = {"7902340086", "7902504188"}; // Police and Parent

// Create an instances of Software Serial

SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
SoftwareSerial gsmSerial(GSM_TX, GSM_RX);

void updateSerial(short _delay = SMALL_DELAY) {
  delay(500);
  while (Serial.available()) {
    gsmSerial.write(Serial.read());
  }
  while (gsmSerial.available()) {
    Serial.write(
        gsmSerial
            .read()); // Forward what Software Serial received to Serial Port
  }
}
void sendText(char *number) {
  // Once the handshake test is successful, it will back to OK
  gsmSerial.println("AT");
  updateSerial();
  // Configuring TEXT mode
  gsmSerial.println("AT+CMGF=1");
  updateSerial();
  gsmSerial.println("AT+CMGS=\"+91" + String(number) + "\"");
  updateSerial();
  gsmSerial.print("Lat: " + String(location._lat) +
                  " Lon: " + String(location._long)); // text content
  updateSerial();
  gsmSerial.write(MSG_TERMINATOR);
}

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
void sendSOS() {
  /*
   * @param none
   * @return -> used to indicate a sucessful SOS
   */
  getLocation();
  sendText();
}

void setup() {
  Serial.begin(BAUD_RATE);
  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  gpsSerial.begin(GPS_BAUD_RATE);
  // Start GSM Serial
  gsmSerial.begin(GSM_BAUD_RATE);

  // TODO: Make the ISR quick
  attachInterrupt(PUSH_BUTTON, sendSOS, FALLING);
}

void loop() {

  unsigned long start = millis();
  while (millis() - start < 1000) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }

    getLocation();
  }
}
