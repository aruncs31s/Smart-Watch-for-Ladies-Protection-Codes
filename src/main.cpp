#include "Config.h"
#include <Arduino.h>

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(MIC_PIN, INPUT);
}
void loop() {
  while (1) {
    Serial.println(analogRead(MIC_PIN));
  }
}
