#include "Config.h"
#include <Arduino.h>

void IRAM_ATTR theISR() { Serial.println("Button Pressed"); }
void setup() {
  Serial.begin(9600);
  attachInterrupt(PUSH_BUTTON, theISR, FALLING);
}
void loop() { delay(1000); }
