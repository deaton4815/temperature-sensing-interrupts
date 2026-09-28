#pragma once

#include <Arduino.h>
#include "Calibration.h"

/*
TemperatureReader
Reads the analog sensor on A0 and converts it to a calibrated Fahrenheit deg.
ADC counts -> millivolts -> Celsius -> Fahrenheit -> corrected.
*/
class TemperatureReader
{
    private:

        // sensor setup
        const int m_sensorPin = A0;
        const float m_maxReading = 1023.0f;   // max value from a 10-bit ADC
        const float m_aRef_voltage = 1.5f;    // internal reference voltage
        static constexpr int m_numSamples = 16;  // samples averaged per reading

        // average several analog reads to cut down on noise
        float getAveragedAnalogReading() const;
        float analog2mV(float) const;
        // millivolts to Celsius (TMP36: 500 mV at 0C, 10 mV per degree)
        float mV2Celsius(float) const;
        float celsius2Fahrenheit(float) const;

    public:
        void setup();
        float readTemperature()  const;
};
