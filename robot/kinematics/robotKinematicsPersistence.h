#ifndef ROBOT_KINEMATICS_PERSISTENCE_H
#define ROBOT_KINEMATICS_PERSISTENCE_H

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
#define KINEMATICS_WHEELS_DISTANCE_DEFAULT_VALUE                            283.00f

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

#endif
