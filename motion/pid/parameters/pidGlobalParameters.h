#ifndef PID_GLOBAL_PARAMETERS_H
#define PID_GLOBAL_PARAMETERS_H

#include "pidParameter.h"

#include "../pidConstants.h"
#include "../pidType.h"
#include "../endDetection/parameters/motionEndDetectionParameter.h"

/**
 * All parameters about pid motion. Don't changed by PidMotion. Are normally constants
 * or set only for a match.
 */
typedef struct PidGlobalParameters {
    // Parameters about PID
    PidParameter pidParameters[PID_TYPE_COUNT];
    // Parameters about end motion detection (avoid rotation of wheels in case of no move => Avoid BURN OUT)
    MotionEndDetectionParameter motionEndDetectionParameter;
} PidGlobalParameters;


#endif

