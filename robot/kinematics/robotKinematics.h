#ifndef ROBOT_KINEMATICS_H
#define ROBOT_KINEMATICS_H

#include "../../common/eeprom/eeprom.h"

#define MILLI_TO_NANO_FACTOR                                    1000000.0f
#define MILLI_TO_MICRO_FACTOR                                    1000.0f

/** 
 * Encapsulation of all information needed to manage the Kinematics (Rotation, Forward / Backward) and coders capacities.
 */
typedef struct RobotKinematics {
    /** We don't have left and right, but an average and a + and - arround this value, because it's more easy to update it. */
    float wheelAverageLengthForOnePulse;
    /** How many rotation by seconds the wheels do at full Speed (full PWM). */
    float wheelRotationBySecondsAtFullSpeed;
    /** How many pulse for a rotation in the incremental coder. */
    float pulseByRotation;
    /** The difference in millimeter for a pulse between left and right. Positive value means that left wheel do more millimeter for one pulse than the right. If negative, it's the opposite. */
    float wheelDeltaLengthForOnePulse;
    /** The distance between wheels in Millimeter. Very important to manage rotation and spline. */
    float wheelsDistance;
} RobotKinematics;

/** 
 * Get the Robot Kinematics information.
 * @return Robot Kinematics information
 */
RobotKinematics* getRobotKinematics(void);

/**
 * Returns the wheel left length for One Pulse.
 * We use the average value of both wheels and we use delta value (+ for left, - for right).
 */
float getLeftWheelLengthForOnePulse(RobotKinematics* robotKinematics);

/**
* Returns the wheel right length for One Pulse.
* We use the average value of both wheels and we use delta value (+ for left, - for right).
*/
float getRightWheelLengthForOnePulse(RobotKinematics* robotKinematics);


/**
 * Get the total amount of pulse done by seconds at full speed (number of pulse for one rotation * number rotation at full speed).
 * @param robotKinematics Structure with all parameters
 * @return the total amount of pulse done by seconds at full speed
 */
float getWheelPulseBySecondsAtFullSpeed(RobotKinematics* robotKinematics);

/**
 * Returns the wheels half distance (from center to one wheel).
 * @param robotKinematics Structure with all parameters
 */
float getWheelsDistanceFromCenter(RobotKinematics* robotKinematics);


#endif
