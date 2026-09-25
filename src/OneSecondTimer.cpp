#include "OneSecondTimer.h"

void OneSecondTimer::timerCallback(timer_callback_args_t *p_args)
{
    OneSecondTimer *self =
        static_cast<OneSecondTimer *>(const_cast<void *>(p_args->p_context));
    self->m_count++;
}

bool OneSecondTimer::beginTimer()
{
    if (!setTimerChannel())
    {
        return false;
    }

    if (!m_timer.begin(m_mode, m_type, m_channel, m_rate_Hz, m_duty, timerCallback, this))
    {
        return false;
    }

}

bool OneSecondTimer::setTimerChannel()
{
    // Get autoselected timer
    m_channel = FspTimer::get_available_timer(m_type);

    // Force reserved timer if needed
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