#include "OneSecondTimer.h"

OneSecondTimer::OneSecondTimer()
{
    beginTimer();
}

bool OneSecondTimer::beginTimer()
{



}

bool OneSecondTimer::setTimerChannel()
{
    // Get autoselected timer
    m_channel = m_timer.get_available_timer(m_type);

    // Force reserved timer if needed
    if (m_channel < 0)
    {
        m_channel = m_timer.get_available_timer(m_type, true);
        m_timer.force_use_of_pwm_reserved_timer();
    }

    if (m_channel < 0)
    {
        return false;
    }

    return true;
}