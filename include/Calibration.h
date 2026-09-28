#pragma once

/*
Calibration
Corrects the sensor's raw Fahrenheit reading using a two-point linear fit
*/
class Calibration
{
    private:
        // reference point A: a known temperature and the error measured there
        static constexpr float DEG_A = 71.6f;
        static constexpr float ERROR_DEG_A = 12.49f;

        // reference point B: a second known temperature and its measured error
        static constexpr float DEG_B = 31.1f;
        static constexpr float ERROR_DEG_B = 11.49f;

        // slope of the line through the two error points above
        static constexpr float SLOPE =
            (DEG_A >= DEG_B)
                ? (ERROR_DEG_A - ERROR_DEG_B) / (DEG_A - DEG_B)
                : (ERROR_DEG_B - ERROR_DEG_A) / (DEG_B - DEG_A);

        // y-intercept of line
        static constexpr float Y_INTERCEPT = ERROR_DEG_A - SLOPE * DEG_A;

    public:
        // apply the fitted correction to a raw Fahrenheit reading
        static float getCorrectedDegreesF(float deg);
};
