#pragma once

#include <Arduino.h>
#include "Calibration.h"

class TemperatureReader
{
    private:

        // setup
        const int m_sensorPin = A0;
        const float m_maxReading = 1023.0f;
        const float m_aRef_voltage = 1.5f;
        static constexpr int m_numSamples = 16;

        float getAveragedAnalogReading() const;
        float analog2mV(float) const;
        float mV2Celsius(float) const;
        float celsius2Fahrenheit(float) const;

    public:
        void setup();
        float readTemperature()  const;
};