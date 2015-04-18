#include "motionParameter.h"
#include "motionParameterType.h"

/** The parameters for motion. */
static MotionParameter defaultMotionParameters[MOTION_PARAMETERS_COUNT];

MotionParameter* getDefaultMotionParameters(enum MotionParameterType motionParameterType) {
    return &defaultMotionParameters[motionParameterType];
}
