#ifndef PID_H
#define PID_H

#include <stdlib.h>
#include <stdbool.h>

#include "pidConstants.h"

// NUMBER OF PID

#include "../../motion/pid/instructionType.h"
#include "../../motion/pid/pidType.h"


#include "../../common/eeprom/eeprom.h"
#include "../../common/io/outputStream.h"

#include "../../device/device.h"

#include "../../motion/extended/bspline.h"


#include "../../motion/pid/pidMotion.h"
#include "../../motion/pid/parameters/pidParameter.h"
#include "../../motion/pid/pidTimer.h"

#include "../../robot/kinematics/robotKinematics.h"

// We manage a precision of time to the millisecond
#define PID_TIME_SECOND_DIGIT_PRECISION 3

// We manage a precision for the PID of 1 digits
#define PID_VALUE_DIGIT_PRECISION       1

/**
 * Returns the Index of Pid which must be chosen in function of pidType.
 * @param instructionType THETA_INDEX or ALPHA_MASK
 * @param pidType the type of pid PID_TYPE_GO_INDEX / PID_TYPE_ROTATE_INDEX / PID_TYPE_MAINTAIN_POSITION
 */
unsigned char getIndexOfPid(enum InstructionType instructionType, enum PidType pidType);

/**
 * Enable or disable a PID.
 * @param pidIndex the index of which pid we must change (between 0 and PID_INDEX_COUNT)
 * @param enabled false or true if we want to enabled or not the specified pid
 */
void setEnabledPid(PidMotion* pidMotion, int pidIndex, unsigned char enabled);

/**
* Sets the PID at the specified index.
* @param pidIndex the index of the PID to set (between 0 and PID_COUNT)
* @param p the P parameter
* @param i the I parameter
* @param d the D parameter
* @param maxIntegral the bounds of the I term
*/
void setPidParameter(PidMotion* pidMotion, int pidIndex, float p, float i, float d, float maxIntegral);

/**
 * Returns the PID at the specified index.
 * @param index the index of the PID to set (between 0 and PID_COUNT)
 * @param pidMode ROLLING_BOARD_TEST_MODE_ON or ROLLING_BOARD_TEST_MODE_OFF
 * @return the PID at the given index
 */
PidParameter* getPidParameter(PidMotion* pidMotion, int index, unsigned int pidMode);

bool getRollingTestMode(PidMotion* pidMotion);

/**
 * Updates the motors values and set the type of control which is applied to the motors.
 * <ul>
 * <li>NO_POSITION_TO_REACH if we don't have any position to reach</li>
 * <li>POSITION_TO_MAINTAIN if we don't have any position, but we want to maintain the position</li>
 * <li>POSITION_IN_PROGRESS if we progress</li>
 * <li>POSITION_REACHED if we have reached the position</li>
 * <li>POSITION_FAILED if we have failed to reach the position (for example, if we are blocked)</li>
 * </li>
 */
void updateMotorsAndDetectedMotionType(PidMotion* pidMotion);

#endif
