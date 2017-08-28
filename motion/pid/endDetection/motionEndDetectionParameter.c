#include "motionEndDetectionParameter.h"

void initMotionEndParameter(MotionEndDetectionParameter* parameter) {
    parameter->absDeltaPositionIntegralFactorThreshold = (unsigned char) ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD;
    parameter->maxUIntegralFactorThreshold = (unsigned char) MAX_U_INTEGRAL_FACTOR_THRESHOLD;
    parameter->maxUIntegralConstantThreshold = (unsigned char) MAX_U_INTEGRAL_CONSTANT_THRESHOLD;
    parameter->timeRangeAnalysis = BLOCKING_OR_REACH_DETECTION_DELAY;
    parameter->noAnalysisAtStartupTime = BLOCKING_OR_REACH_SKIP_DETECTION_DELAY;
}
