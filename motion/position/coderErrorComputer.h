#ifndef CODER_ERROR_COMPUTER_H
#define CODER_ERROR_COMPUTER_H

#include "../../motion/pid/pidMotion.h"

/**
 * Compute current position using coders (and not absolute position).
 * @param pidMotion all parameters about motion.
 */
void computeCurrentPositionUsingCoders(PidMotion* pidMotion);

#endif
