/* Source: https://lastminuteengineers.com/sim800l-gsm-module-arduino-tutorial/
 */

#include "Config.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

// #if defined(ARDUINO)
SoftwareSerial gsmSerial(GSM_TX, GSM_RX); // 3 -> SIM800L Tx & 2 -> SIM800L Rx
// #elif defined(ESP8266)
// SoftwareSerial gsmSerial(D5, D6); // D5 -> SIM800L Tx & D6 -> SIM800L Rx
// #endif

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    gsmSerial.write(
        Serial.read()); // Forward what Serial received to Software Serial Port
  }
  while (gsmSerial.available()) {
    Serial.write(
        gsmSerial
            .read()); // Forward what Software Serial received to Serial Port
  }
}
void setup() {
  Serial.begin(9600);

  // Start GSM Serial
  gsmSerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  gsmSerial.println(
      "AT"); // Once the handshake test is successful, it will back to OK
  updateSerial();

  gsmSerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  gsmSerial.println(
      "AT+CMGS=\"+917902504188\""); // change ZZ with country code and
                                    // xxxxxxxxxxx with phone number to sms
  updateSerial();
  gsmSerial.print(
      "Last Minute Engineers | lastminuteengineers.com"); // text content
  updateSerial();
  gsmSerial.write(26);
}

void loop() {
  updateSerial();
  delay(1000);
}
