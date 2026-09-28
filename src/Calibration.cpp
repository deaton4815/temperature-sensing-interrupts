#include "Calibration.h"

float Calibration::getCorrectedDegreesF(float deg)
{
    // predicted error at temperature from the fitted line
    float error = SLOPE * deg + Y_INTERCEPT;
    // remove the predicted error from the raw reading
    return deg - error;
}
