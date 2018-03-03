#include "motionParameter.h"
#include "motionParameterType.h"

/** The parameters for motion. */
static MotionParameter motionParameters[MOTION_PARAMETERS_COUNT];

MotionParameter* getMotionParameters(enum MotionParameterType motionParameterType) {
    return &motionParameters[motionParameterType];
}
