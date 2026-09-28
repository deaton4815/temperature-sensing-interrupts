#pragma once

#include <cstdint>
#include <Arduino.h>

/*
TimerLED
Pulses the onboard LED briefly to mark each temperature sample, without
using delay()
*/
class TimerLED
{
    private:
        static constexpr uint8_t LED_PIN = 13;    
        static constexpr uint32_t PULSE_MS = 50; 

        uint32_t m_pulseStart = 0;  
        bool m_pulsing = false;    

    public:

        void setup();
        void startPulse();
        // call every loop() pass; turns the LED off once PULSE_MS has elapsed
        void checkPulse();
};
