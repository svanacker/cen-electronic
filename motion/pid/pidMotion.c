#include "pidMotion.h"

// Contains all information about current motion (singleton)
static PidMotion pidMotion;

PidMotion* getPidMotion(void) {
    return &pidMotion;
}

/**
 * Init global variable storing information about motion.
 */
void initPidMotion(void) {
    initMotionEndParameter(getMotionEndDetectionParameter());
    initFirstTimeBSplineCurve(&(pidMotion.currentMotionDefinition.curve));
}