#include <Arduino.h>

#include <cstdint>

#include "OneSecondTimer.h"
#include "TemperatureReader.h"

namespace
{
  OneSecondTimer gptTimer;
  constexpr uint8_t LED_PIN = 13;
  constexpr uint32_t PULSE_MS = 50;
  uint32_t pulseStart = 0;
  bool pulsing = false;

  uint32_t count = 0;

  //temperature
  TemperatureReader temperature;
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // start with pin off

  Serial.begin(115200);

  if (!gptTimer.beginTimer())
  {
    Serial.println("[ERROR] Timer did not start");
  }

  temperature.setup();
}

void loop() {
  uint32_t countNew = gptTimer.getCount();
  if (count != countNew)
  {
    count = countNew;
    digitalWrite(LED_PIN, HIGH);
    pulseStart = millis();
    pulsing = true;

    float degreesF = temperature.readTemperature();
    Serial.print("\n");
    Serial.println(degreesF);
  }

  if (pulsing && (millis() - pulseStart >= PULSE_MS))
  {
      digitalWrite(LED_PIN, LOW);
      pulsing = false;
  }
}