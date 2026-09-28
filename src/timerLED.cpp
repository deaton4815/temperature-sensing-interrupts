#include "TimerLED.h"

void TimerLED::setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // start with pin off
}

void TimerLED::startPulse()
{
    // turn the LED on and remember when the pulse started
    digitalWrite(LED_PIN, HIGH);
    m_pulseStart = millis();
    m_pulsing = true;
}

void TimerLED::checkPulse()
{
    // non-blocking. turn the LED back off once PULSE_MS has passed
    if (m_pulsing && (millis() - m_pulseStart >= PULSE_MS))
    {
        digitalWrite(LED_PIN, LOW);
        m_pulsing = false;
    }
}
