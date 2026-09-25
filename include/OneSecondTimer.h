#include <cstdint>
#include <FspTimer.h>

class OneSecondTimer
{
    private:

        FspTimer m_timer;
        uint8_t m_type = GPT_TIMER;
        int8_t m_channel;

        const float m_rate_MHz = 1.0;

        const int m_ledPin = LED_BUILTIN;

        volatile bool m_tickFlag = false;

        bool beginTimer();
        bool setTimerChannel();

    public:

        OneSecondTimer();

};
