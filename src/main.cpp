/*
Philip Deaton

Project 2 -- Serial Transmission of Temperature
Round-robin loop: the timer ISR only counts ticks, and loop() polls that
count to decide when to sample the sensor, pulse the LED, and print a
CSV row (time_s,temp_F) over serial.
*/

#include <Arduino.h>

#include <cstdint>

#include "OneSecondTimer.h"
#include "TemperatureReader.h"
#include "TimerLED.h"

#include "Counter.h"

namespace
{
  OneSecondTimer gptTimer;   // 1 Hz interrupt / elapsed-time source

  uint32_t count = 0;

  //temperature
  TemperatureReader temperature;

  //timer LED signal
  TimerLED timerLED;

  // Counter
  Counter counter;

  bool firstFlag = true;   // print the CSV header once, before the first row
}

void setup() {
  Serial.begin(115200);

  temperature.setup();
  timerLED.setup();

  // start the 1 Hz interrupt everything else is timed against
  if (!gptTimer.beginTimer())
  {
    Serial.println("[ERROR] Timer did not start");
  }
}

void loop() {
  // has ~10 seconds passed since the last sample?
  bool flag = counter.checkCount(gptTimer.getCount());
  if (flag)
  {
    // print the CSV header once, right before the first data row
    if (firstFlag){
      Serial.println("time_s,temp_F");
      firstFlag = false;
    }

    timerLED.startPulse();                        // visual sampling indicator
    float degreesF = temperature.readTemperature();
    float elapsedSeconds = gptTimer.getTime();

    // one CSV row: elapsed time, calibrated temperature
    Serial.print(elapsedSeconds);
    Serial.print(",");
    Serial.println(degreesF);
  }

  // non-blocking: turns the LED back off once its pulse has elapsed
  timerLED.checkPulse();
}
