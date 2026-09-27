#pragma once

#include <cstdint>

class Counter
{
    private:
        static constexpr uint32_t COUNT_INTERVAL = 10;
        uint32_t m_countPrev = 0;
    public:
        bool checkCount(uint32_t);
};