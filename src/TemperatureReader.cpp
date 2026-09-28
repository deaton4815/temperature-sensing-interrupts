#include "TemperatureReader.h"

void TemperatureReader::setup()
{
    // use the internal reference voltage for finer resolution
    analogReference(AR_INTERNAL);
    analogReadResolution(10);
}

float TemperatureReader::readTemperature() const
{
    // read -> mV -> Celsius -> Fahrenheit -> calibrated
    return Calibration::getCorrectedDegreesF(celsius2Fahrenheit(mV2Celsius(analog2mV(getAveragedAnalogReading()))));
}

float TemperatureReader::getAveragedAnalogReading() const
{
    long sum = 0;
    // average multiple samples to smooth out noise
    for (int i = 0; i < m_numSamples; i++)
    {
        sum += analogRead(m_sensorPin);
    }
    return static_cast<float>(sum) / m_numSamples;
}

float TemperatureReader::analog2mV(float a) const
{
    // scale a raw ADC count to a voltage in millivolts
    return a * m_aRef_voltage / m_maxReading * 1000.0f;
}

float TemperatureReader::mV2Celsius(float mv) const
{
    // TMP36: 500 mV at 0C, rising 10 mV per degree
    return (mv - 500) / 10;
}

float TemperatureReader::celsius2Fahrenheit(float c) const
{
    return (c * 9 / 5) + 32;
}
