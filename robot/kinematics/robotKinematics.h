#ifndef ROBOT_KINEMATICS_H
#define ROBOT_KINEMATICS_H

#include "../../common/eeprom/eeprom.h"

#define MILLI_TO_NANO_FACTOR                                    1000000.0f
#define MILLI_TO_MICRO_FACTOR                                    1000.0f

// EEPROM INDEX

#define EEPROM_WHEEL_AVERAGE_LENGTH_FOR_ONE_PULSE_INDEX            EEPROM_KINETICS_START_INDEX
#define EEPROM_WHEEL_ROTATION_BY_SECOND_AT_FULL_SPEED_INDEX        EEPROM_WHEEL_AVERAGE_LENGTH_FOR_ONE_PULSE_INDEX + 4
#define EEPROM_PULSE_BY_ROTATION_INDEX                            EEPROM_WHEEL_ROTATION_BY_SECOND_AT_FULL_SPEED_INDEX + 4
#define EEPROM_WHEEL_DELTA_LENGTH_INDEX                            EEPROM_PULSE_BY_ROTATION_INDEX + 4
#define EEPROM_WHEELS_DISTANCE_INDEX                            EEPROM_WHEEL_DELTA_LENGTH_INDEX + 4

// DEFAULT VALUES

/** Average wheel length in mm for 1 impulsion. */
// Change for a wheel of an average 30 mm
#define KINEMATICS_WHEEL_AVERAGE_LENGTH_DEFAULT_VALUE                        0.004776f

#define KINEMATICS_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_DEFAULT_VALUE    7.0f
// FOR 7500 x 4 (quadratic) = 30 000
#define KINEMATICS_WHEEL_PULSE_BY_ROTATION_DEFAULT_VALUE                    20000.0f

// To compensate difference between WHEELS
#define KINEMATICS_WHEEL_DELTA_LENGTH_DEFAULT_VALUE                            0.0f            

/** Default wheels distance (micrometer)). */
// #define WHEELS_DISTANCE 226.70f
#define KINEMATICS_WHEELS_DISTANCE_DEFAULT_VALUE                            240.80f

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
 * Load the Kinematics parameters from the eeprom_ to the structure given in parameter. It can be used to load Default Values when nothing is in the eeprom.
 * @param robotKinematics Structure with all parameters
 * @param eeprom_ the eeprom object to store long term values
 * @param loadDefaultValues if we load the default values (Cybernetique en Nord bot).
 */
void loadRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_, bool loadDefaultValues);

/**
* Save the Kinematics parameters to the eeprom_ from the structure given in parameter.
* @param robotKinematics Structure with all parameters
* @param eeprom_ the eeprom object to store long term values
*/
void saveRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_);

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

// DEBUG

/**
 * Output a table with all values.
*/
void printRobotKinematicsTable(OutputStream* outputStream, RobotKinematics* robotKinematics);

#endif
