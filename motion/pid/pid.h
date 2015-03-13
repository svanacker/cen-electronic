#ifndef PID_H
#define PID_H

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"
#include "../../common/io/outputStream.h"

#include "../../device/device.h"

#include "../../motion/extended/bspline.h"

#include "../../motion/pid/instructionType.h"
// #include "../../motion/pid/motionInstruction.h"
// #include "../../motion/pid/motionEndDetection.h"
// #include "../../motion/pid/detectedMotionType.h"
// #include "../../motion/pid/pidComputationValues.h"
// #include "../../motion/pid/pidMotion.h"
// #include "../../motion/pid/pidMotionDefinition.h"
// #include "../../motion/pid/pidMotionError.h"
#include "../../motion/pid/pidType.h"
#include "../../motion/pid/pidTimer.h"
// #include "../../motion/pid/profileType.h"

// #include "../../motion/simple/motionParameterType.h"

#include "../../robot/kinematics/robotKinematics.h"

// PID CONSTANT


// -> TEST MODE (to test with a rolling board instead of real motion)

#define TEST_MODE_COUNT 2

/** we use test mode */
#define ROLLING_BOARD_TEST_MODE_OFF 0

/** We use the pid at the adress for test mode. */
#define ROLLING_BOARD_TEST_MODE_ON 1

// NUMBER OF PID

/** The total number of PID values (INSTRUCTION_COUNT * PID_TYPE_COUNT). */
#define PID_COUNT (INSTRUCTION_COUNT * PID_TYPE_COUNT)



/**
 * Limit value to next PID value.
 */
#define PID_NEXT_VALUE_LIMIT 1000.0f

/**
 * Constant to have good PID range.
 */
#define PID_GLOBAL_DIVISER 400.0f

/** 
 The factor which defines by which factor we divide the expected acceleration.
 The real acceleration has for unit : coder count / time_sample^2
 If we want to convert to m / s-2, we use the following formula :

 a = (a_coder_count / count_by_meter) / (time_sample^2)
 Ex : 
  a_coder_count = 10, count_by_meter = 10000, time_sample = 0.005 (200 Hz)
  (10 / 10000) / 0.005Hz = 40 m s-2 which is too much
 If we increase this factor, we must enhanced the acceleration value to have the same acceleration
 */
#define A_FACTOR 0.1f

/**
 * The factor for improving speed.
 */
#define SPEED_FACTOR 10.0f

/**
 * Defines the error for which we apply strong PID and not normal PID.
 */
#define ERROR_FOR_STRONG_PID                     20

/**
 * Defines the number of pid interrupt after the end (t3) to apply strong PID.
 */
#define TIME_PERIOD_AFTER_END_FOR_STRONG_PID     40

/**
 * Defines the structure which is used to store PID values
 */
typedef struct Pid {
    /** The proportional term */
    float p;
    /** The integral term */
    float i;
    /** The derivative term */
    float d;
    /** The maximal term of integral */
    float maxIntegral;
    /** Enable or not the pid. */
    bool enabled;
} Pid;

float getWheelPulseByPidTimeAtFullSpeed();

float getUFactorAtFullSpeed();

/**
 * Returns the Index of Pid which must be chosen in function of pidType.
 * @param instructionIndex THETA_INDEX or ALPHA_MASK
 * @param pidType the type of pid PID_TYPE_GO_INDEX / PID_TYPE_ROTATE_INDEX / PID_TYPE_MAINTAIN_POSITION
 */
unsigned char getIndexOfPid(unsigned char instructionIndex, enum PidType pidType);

/**
 * Enable or disable a PID.
 * @param pidIndex the index of which pid we must change (between 0 and PID_INDEX_COUNT)
 * @param enabled false or true if we want to enabled or not the specified pid
 */
void setEnabledPid(int pidIndex, unsigned char enabled);

/**
 * Sets the PID at the specified index.
 * @param pidIndex the index of the PID to set (between 0 and PID_COUNT)
 * @param p the P parameter
 * @param i the I parameter
 * @param d the D parameter
 * @param maxIntegral the bounds of the I term
 */
void setPID(int pidIndex, float p, float i, float d, float maxIntegral);

/**
 * Returns the PID at the specified index.
 * @param index the index of the PID to set (between 0 and PID_COUNT)
 * @param pidMode ROLLING_BOARD_TEST_MODE_ON or ROLLING_BOARD_TEST_MODE_OFF
 * @return the PID at the given index
 */
Pid* getPID(int index, unsigned int pidMode);

unsigned char getRollingTestMode();

Pid* getRollingTestModePid();

Pid* getEndApproachPid();

/**
 * Returns the time of the PID
 */
long getPidTime(void);

/**
 * Clear to 0 the time of the PID
 */
void clearPidTime(void);

/**
 * Returns the value of the flag which determines if the
 * position must be reached.
 * @return true or false
 */
int getMustReachPosition(void);

/**
 * Sets the flag which determines if the
 * position must be reached.
 * @value the value of the flag, true or false
 */
void setMustReachPosition(int value);

/**
 * Updates the motors values and returns the type of control which is applied to the motors.
 * <ul>
 * <li>NO_POSITION_TO_REACH if we don't have any position to reach</li>
 * <li>POSITION_TO_MAINTAIN if we don't have any position, but we want to maintain the position</li>
 * <li>POSITION_IN_PROGRESS if we progress</li>
 * <li>POSITION_REACHED if we have reached the position</li>
 * <li>POSITION_FAILED if we have failed to reach the position (for example, if we are blocked)</li>
 * </li>
 */
unsigned int updateMotors(void);

/**
* Get the normal voltage value at the speed defined by the parameter
* @param normalSpeed the speed for which we want the normal voltage
* TODO : Must be Test By Experimentation
*/
float getNormalU(float normalSpeed);

/**
 * Initializes the PID.
 */
void initPID(Eeprom* _eeprom);

/**
 * Stop the PID.
 */
void stopPID(void);


#endif
