#include <Arduino.h>
#include <Config.h>
#include <SoftwareSerial.h>

Numbers number = {"7907489077","7907489077"};


SoftwareSerial gsmSerial(GSM_TX, GSM_RX);
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
void send_sos(const char *theNumber){
  gsmSerial.println(
      "AT"); // Returns OK if handshake successful
  updateSerial();

  gsmSerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  gsmSerial.println(
      "AT+CMGS=\"+91"+String(theNumber)+"\""); 
  updateSerial();
  gsmSerial.print(
      "HI"); 
  updateSerial();
  gsmSerial.write(26);
}

void setup() {
  Serial.begin(9600);

  // Start GSM Serial
  gsmSerial.begin(9600);

  
}

void loop() {
  Serial.println("Initializing...");
  send_sos(number.police);

  delay(5000);
}
