#ifndef FORK_ACCELERATOR_2019_H
#define FORK_ACCELERATOR_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"
#include "../../../drivers/tof/tofList.h"


/**
 * The actions to to release the Puck in Accelerator
 * @param servoList
 */
bool fork2019AcceleratorDrop(ServoList* servoList, unsigned int firstLeftRightServoIndex, unsigned int secondLeftRightServoIndex);

#endif
