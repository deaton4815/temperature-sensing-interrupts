#pragma once

#include <cstdint>

/*
Counter
Flags every 10th timer tick
*/
class Counter
{
    private:
        static constexpr uint32_t COUNT_INTERVAL = 10;
        uint32_t m_countPrev = 0;

    public:
        // call every loop() pass with the current tick count.
        // returns true once per new multiple of COUNT_INTERVAL
        bool checkCount(uint32_t);
};
