#ifndef CODER_ERROR_COMPUTER_H
#define CODER_ERROR_COMPUTER_H

#include "../../motion/pid/pid.h"

/**
 * Compute errors using coders (and not absolute position).
 */
void computeErrorsUsingCoders(PidMotion* pidMotion);

#endif
