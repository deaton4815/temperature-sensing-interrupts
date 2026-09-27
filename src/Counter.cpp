#include "Counter.h"

bool Counter::checkCount(uint32_t count)
{
   if (count != m_countPrev && count % COUNT_INTERVAL == 0)
   {
    m_countPrev = count;
    return true;
   }
   return false;
}