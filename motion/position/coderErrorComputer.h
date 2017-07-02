#ifndef CODER_ERROR_COMPUTER_H
#define CODER_ERROR_COMPUTER_H

#include "../../motion/pid/pidMotion.h"

/**
 * Compute current position using coders (and not absolute position).
 * @param pidMotion all parameters about motion.
 * @param motionDefinition the current Motion Definition which is applied
 */
void computeCurrentPositionUsingCoders(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

/**
 * Compute errors using coders (and not absolute position).
 * This information is useful only to manage final Approach.
 * @param pidMotion all parameters about motion.
 * @param motionDefinition the current Motion Definition which is applied
 */
void computeErrorsWithNextPositionUsingCoders(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
