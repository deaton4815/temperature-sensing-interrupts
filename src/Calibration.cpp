#include "Calibration.h"

float Calibration::getCorrectedDegreesF(float deg)
{
    float error = SLOPE * deg + Y_INTERCEPT;
    return deg - error;
}