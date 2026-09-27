#include "TimerLED.h"

void TimerLED::setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // start with pin off
}

void TimerLED::startPulse()
{
    digitalWrite(LED_PIN, HIGH);
    m_pulseStart = millis();
    m_pulsing = true;
}

void TimerLED::checkPulse()
{
    if (m_pulsing && (millis() - m_pulseStart >= PULSE_MS))
    {
        digitalWrite(LED_PIN, LOW);
        m_pulsing = false;
    }
}