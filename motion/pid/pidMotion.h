#ifndef PID_MOTION_H
#define PID_MOTION_H

#include "pidGlobalParameters.h"
#include "pidMotionDefinition.h"
#include "pidComputationValues.h"

// NUMBER OF NEXT_MOTION_DEFINITION_COUNT

#define NEXT_MOTION_DEFINITION_COUNT 2

/**
 * Global struct to make links between all structures and variables to achieve
 * motion with PID.
 */
typedef struct PidMotion {
    // Parameters for all motions => INVARIANT.
    PidGlobalParameters globalParameters;
    // The current motion definition => CHANGE FOR EACH MOTION.
    PidMotionDefinition currentMotionDefinition;
    // Contains the next Motion Definition;
    PidMotionDefinition nextMotionDefinition[NEXT_MOTION_DEFINITION_COUNT];
    // All current values (must be reset after each new move) => CHANGE EVERY TIME COMPUTATION
    PidComputationValues computationValues;
} PidMotion;

/**
 * Returns the current pidMotion.
 */
PidMotion* getPidMotion();

void initPidMotion(void);

#endif

