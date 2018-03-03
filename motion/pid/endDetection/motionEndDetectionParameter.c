#include "motionEndDetectionParameter.h"

void initMotionEndParameter(MotionEndDetectionParameter* parameter) {
    parameter->absDeltaPositionIntegralFactorThreshold = ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD;
    parameter->maxUIntegralFactorThreshold = MAX_U_INTEGRAL_FACTOR_THRESHOLD;
    parameter->maxUIntegralConstantThreshold = MAX_U_INTEGRAL_CONSTANT_THRESHOLD;
    parameter->timeRangeAnalysis = BLOCKING_OR_REACH_DETECTION_DELAY;
    parameter->noAnalysisAtStartupTime = BLOCKING_OR_REACH_SKIP_DETECTION_DELAY;
}
