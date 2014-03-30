#ifndef ARM_DRIVER_2012_H
#define ARM_DRIVER_2012_H

#include "../../common/commons.h"

/**
 * Ask the remote servo which handle the arm 2012 to go down.
 */
bool armDriver2012Down(int index);

/**
 * Ask the remote servo which handle the arm 2012 to go up.
 */
bool armDriver2012Up(int index);

#endif
