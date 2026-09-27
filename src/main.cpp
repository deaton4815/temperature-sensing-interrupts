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
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // start with pin off

  Serial.begin(115200);

  analogReference(AR_INTERNAL);

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

    int reading = analogRead(A0);
    float volts = reading * 1.5 / 1023.0;
    float mv = 1000 * volts;
    float degreesC = (mv - 500)/10;
    float degreesF = (degreesC * 9/5) + 32;
    Serial.print("\n");
    Serial.println(degreesF);
  }

  if (pulsing && (millis() - pulseStart >= PULSE_MS))
  {
      digitalWrite(LED_PIN, LOW);
      pulsing = false;
  }
}