#include "TemperatureReader.h"

void TemperatureReader::setup()
{
    analogReference(AR_INTERNAL);
    analogReadResolution(10);
}

float TemperatureReader::readTemperature() const
{
    return Calibration::getCorrectedDegreesF(celsius2Fahrenheit(mV2Celsius(analog2mV(getAveragedAnalogReading()))));
}

float TemperatureReader::getAveragedAnalogReading() const
{
    long sum = 0;
    for (int i = 0; i < m_numSamples; i++)
    {
        sum += analogRead(m_sensorPin);
    }
    return static_cast<float>(sum) / m_numSamples;
}

float TemperatureReader::analog2mV(float a) const
{
    return a * m_aRef_voltage / m_maxReading * 1000.0f;
}

float TemperatureReader::mV2Celsius(float mv) const
{
    return (mv - 500) / 10;
}

float TemperatureReader::celsius2Fahrenheit(float c) const
{
    return (c * 9 / 5) + 32;
}