#ifndef MOTION_END_DETECTION_H
#define MOTION_END_DETECTION_H

#include <stdbool.h>

/**
 * Structure to store flags about end detection for each pid time and for each instruction type.
 * This helps the different detectors (blocked, reached, shocked) to rely on same precomputed data.
 */
typedef struct MotionEndDetectionStatusRegister {
    /**
     * Abs value of acceleration (so deceleration which is a negative acceleration) is too high than expected.
     * This is often the case when the robot hurts something (table or object). It has a more direct impact on 
     * acceleration than on the speed
     */
    bool absAccelerationTooHighThanExpected : 1;
    /**
     * Abs value of speed (even if we go backward).
     * We detect it when we fabsf(currentSpeed) / fabsf(normalSpeed) > factor
     * This often say that we are blocked
     */
    bool absSpeedTooLowThanExpected : 1;
    /**
     * Abs value of tension (U) is too high than expected.
     * We detect it when we fabsf(currentU) / fabsf(normalU) > factor
     * This often means than the robot is blocked and try to fix a growing error
     */
    bool absUTooHighThanExpected : 1;
} MotionEndDetectionStatusRegister;

#endif
