#pragma once

#include <Arduino.h>

class TemperatureReader
{
    private:

        // setup
        const int m_sensorPin = A0;
        const float m_maxReading = 1023.0f;
        const float m_aRef_voltage = 1.5f;

        int getAnalogReading();
        float analog2mV(int a);
        float mV2Celsius(float mv);
        float celsius2Farenheit(float c);

    public:
        
        void setup();
        float readTemperature();

};