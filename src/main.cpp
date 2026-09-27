#include <Arduino.h>

#include <cstdint>

#include "OneSecondTimer.h"
#include "TemperatureReader.h"
#include "TimerLED.h"

namespace
{
  OneSecondTimer gptTimer;

  uint32_t count = 0;

  //temperature
  TemperatureReader temperature;

  //timer LED signal
  TimerLED timerLED;
}

void setup() {
  Serial.begin(115200);

  temperature.setup();
  timerLED.setup();

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

    float degreesF = temperature.readTemperature();
    Serial.print("\n");
    Serial.println(degreesF);
  }

  timerLED.checkPulse();
}