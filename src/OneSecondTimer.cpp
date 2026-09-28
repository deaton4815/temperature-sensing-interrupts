#include "OneSecondTimer.h"

void OneSecondTimer::timerCallback(timer_callback_args_t *p_args)
{
    // recover the owning object from the context pointer
    OneSecondTimer *self =
        static_cast<OneSecondTimer *>(const_cast<void *>(p_args->p_context));
    self->m_count++;
}

bool OneSecondTimer::beginTimer()
{
    // already running
    if (m_started)
    {
        return true;
    }

    // claim a hardware timer channel
    if (!setTimerChannel())
    {
        return false;
    }

    // configure a periodic 1 Hz timer with timerCallback as the ISR
    if (!m_timer.begin(m_mode, m_type, m_channel, m_rate_Hz, 0.0f, timerCallback, this))
    {
        return false;
    }

    // enable the overflow interrupt, then open and start the timer
    if (!m_timer.setup_overflow_irq() || !m_timer.open() || !m_timer.start())
    {
        m_timer.end();   // release the channel
        return false;
    }

    m_started = true;
    return m_started;
}

bool OneSecondTimer::setTimerChannel()
{
    m_channel = FspTimer::get_available_timer(m_type);

    // fall back to a reserved PWM timer if none are free
    if (m_channel < 0)
    {
        m_channel = FspTimer::get_available_timer(m_type, true);
        FspTimer::force_use_of_pwm_reserved_timer();
    }

    if (m_channel < 0)
    {
        return false;
    }
    return true;
}

uint32_t OneSecondTimer::getCount(){ return m_count; }
uint32_t OneSecondTimer::getTime(){ return m_count / m_rate_Hz; }
