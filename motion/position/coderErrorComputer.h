#ifndef CODER_ERROR_COMPUTER_H
#define CODER_ERROR_COMPUTER_H

#include "../../motion/pid/pidMotion.h"

/**
 * Compute current position using coders (and not absolute position).
 */
void computeCurrentPositionUsingCoders(PidMotion* pidMotion);

/**
 * Compute errors using coders (and not absolute position).
 * This information is useful only to manage final Approach.
 */
void computeErrorsWithNextPositionUsingCoders(PidMotion* pidMotion);

#endif
