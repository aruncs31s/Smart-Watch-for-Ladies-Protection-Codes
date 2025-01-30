#include <Arduino.h>
#include <Config.h>
#include <SoftwareSerial.h>

Numbers number = {"7907489077","7907489077"};
bool sendSMS = false;


SoftwareSerial gsmSerial(GSM_TX, GSM_RX);
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    gsmSerial.write(
        Serial.read()); 
  }
  while (gsmSerial.available()) {
    Serial.write(
        gsmSerial
            .read()); 
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


void initiate_sms(){
  sendSMS = true;
}

void IRAM_ATTR theISR(){
  Serial.println("Button Pressed");
  initiate_sms();
}

void setup() {
  Serial.begin(9600);
  // Start GSM Serial
  gsmSerial.begin(9600);
  attachInterrupt(D1,theISR,FALLING);
}

void loop() {
  Serial.println("Initializing...");
  if(sendSMS){
    send_sos(number.parent);
    send_sos(number.police);
    sendSMS ^=1;;
  }
  delay(5000);
}
