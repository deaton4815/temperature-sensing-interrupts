#include <cstdint>
#include <FspTimer.h>

class OneSecondTimer
{
    private:

        // timer setup
        FspTimer m_timer;
        timer_mode_t m_mode = TIMER_MODE_PERIODIC;
        uint8_t m_type = GPT_TIMER;
        int8_t m_channel;
        float m_rate_Hz = 1.0;
        float m_duty = 0.0;
        
        const int m_ledPin = LED_BUILTIN;

        // callback
        volatile uint32_t m_count = 0;

        static void timerCallback(timer_callback_args_t *p_args);

        bool setTimerChannel();

    public:

        OneSecondTimer() = default;

        bool beginTimer();        

};
