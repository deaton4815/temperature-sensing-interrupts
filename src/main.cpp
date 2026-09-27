#include <Arduino.h>

#include <cstdint>

#include "OneSecondTimer.h"
#include "TemperatureReader.h"
#include "TimerLED.h"

#include "Counter.h"

namespace
{
  OneSecondTimer gptTimer;

  uint32_t count = 0;

  //temperature
  TemperatureReader temperature;

  //timer LED signal
  TimerLED timerLED;

  // Counter
  Counter counter;
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
  bool flag = counter.checkCount(gptTimer.getCount());
  if (flag)
  {
    float degreesF = temperature.readTemperature();
    float time = gptTimer.getTime();
    Serial.print("\n");
    Serial.println(degreesF);
    Serial.println(time);
  }
  timerLED.checkPulse();
}