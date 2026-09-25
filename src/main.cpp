#include <Arduino.h>

#include <cstdint>

#include "OneSecondTimer.h"

namespace
{
  OneSecondTimer gptTimer;
  constexpr uint8_t LED_PIN = 13;
  constexpr uint32_t PULSE_MS = 50;
  uint32_t pulseStart = 0;
  bool pulsing = false;

  uint32_t count = 0;
  static uint32_t lastPrint = 0;
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // start with pin off

  Serial.begin(115200);

  if (!gptTimer.beginTimer())
  {
    Serial.println("[ERROR] Timer did not start");
  }
}

void loop() {
  uint32_t countNew = gptTimer.getCount();
  if (count != countNew)
  {
    count = countNew;
    digitalWrite(LED_PIN, HIGH);
    pulseStart = millis();
    pulsing = true;
  }

  if (pulsing && (millis() - pulseStart >= PULSE_MS))
  {
      digitalWrite(LED_PIN, LOW);
      pulsing = false;
  }

if (millis() - lastPrint >= 1000)
{
    lastPrint = millis();
    Serial.print("count=");
    Serial.println(gptTimer.getCount());
}  

}