#ifndef FORK_ACCELERATOR_2019_H
#define FORK_ACCELERATOR_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"
#include "../../../drivers/tof/tofList.h"

/**
 * Used only for Device to test easily the accelerator.
 * @param servoList
 * @return 
 */
bool accelerator2019FakeInit(ServoList* servoList);

/**
 * Function which must be called before reaching the accelerator Drop.
 * @param servoList
 * @return 
 */
bool accelerator2019PrepareDrop(ServoList* servoList);

bool accelerator2019FakeMoveForward(void);

/**
 * The actions to to release the Puck in Accelerator
 * @param servoList
 */
bool accelerator2019Drop(ServoList* servoList, unsigned int firstLeftRightServoIndex, unsigned int secondLeftRightServoIndex);

// COMPLETE SEQUENCE

bool accelerator2019CompleteSequence(ServoList* servoList, unsigned int firstLeftRightServoIndex, unsigned int secondLeftRightServoIndex);


#endif
