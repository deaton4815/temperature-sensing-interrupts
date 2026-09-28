#pragma once

#include <cstdint>
#include <FspTimer.h>

/*
OneSecondTimer
Fires a 1 Hz hardware interrupt on the RA timer. The ISR only counts
ticks; the main loop polls that count to decide when to act.
*/
class OneSecondTimer
{
    private:

        // timer setup
        FspTimer m_timer;
        timer_mode_t m_mode = TIMER_MODE_PERIODIC;   // repeats forever
        uint8_t m_type = GPT_TIMER;                  // general PWM timer channel
        int8_t m_channel = -1;                       
        float m_rate_Hz = 1.0;                       // fire once per second                       

        // status
        bool m_started = false;

        // tick count, updated in the ISR
        volatile uint32_t m_count = 0;

        // runs in interrupt context on every timer overflow
        static void timerCallback(timer_callback_args_t *p_args);

        bool setTimerChannel();

    public:

        OneSecondTimer() = default;
        OneSecondTimer(const OneSecondTimer &) = delete;
        OneSecondTimer &operator=(const OneSecondTimer &) = delete;

        bool beginTimer();
        uint32_t getCount();
        uint32_t getTime();
};
