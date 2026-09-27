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

  bool firstFlag = true;
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
    if (firstFlag){
      Serial.println("time_s,temp_F");
      firstFlag = false;
    }

    timerLED.startPulse();
    float degreesF = temperature.readTemperature();
    float elapsedSeconds = gptTimer.getTime();

    Serial.print(elapsedSeconds);
    Serial.print(",");
    Serial.println(degreesF);
  }
  timerLED.checkPulse();
}