#pragma once

class Calibration
{
    private:
        static constexpr float DEG_A = 32.0f;
        static constexpr float ERROR_DEG_A = 0.0f;
        static constexpr float DEG_B = 212.0f;
        static constexpr float ERROR_DEG_B = 0.0f;

        static constexpr float SLOPE =
            (DEG_A >= DEG_B)
                ? (ERROR_DEG_A - ERROR_DEG_B) / (DEG_A - DEG_B)
                : (ERROR_DEG_B - ERROR_DEG_A) / (DEG_B - DEG_A);

        static constexpr float Y_INTERCEPT = ERROR_DEG_A - SLOPE * DEG_A;

    public:
        static float getCorrectedDegreesF(float deg);
};