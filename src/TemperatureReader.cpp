#include "TemperatureReader.h"

void TemperatureReader::setup()
{
    analogReference(AR_INTERNAL);
    analogReadResolution(10); 
}

float TemperatureReader::readTemperature()
{
    return celsius2Farenheit(mV2Celsius(analog2mV(getAnalogReading())));
}

int TemperatureReader::getAnalogReading()
{
    return analogRead(m_sensorPin);
}

float TemperatureReader::analog2mV(int a)
{
    return a * m_aRef_voltage / m_maxReading * 1000.0f;
}

float TemperatureReader::mV2Celsius(float mv)
{
    return (mv - 500) / 10;
}

float TemperatureReader::celsius2Farenheit(float c)
{
    return (c * 9 / 5) + 32;
}