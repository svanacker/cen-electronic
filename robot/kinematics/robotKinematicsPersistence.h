#ifndef ROBOT_KINEMATICS_PERSISTENCE_H
#define ROBOT_KINEMATICS_PERSISTENCE_H

#include "../robotType.h"

// EEPROM INDEX

// CODERS PART
#define EEPROM_CODER_WHEEL_AVERAGE_DIAMETER_INDEX                     EEPROM_KINEMATICS_START_INDEX
#define EEPROM_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_INDEX               EEPROM_KINEMATICS_START_INDEX + 4
#define EEPROM_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX              EEPROM_KINEMATICS_START_INDEX + 8
#define EEPROM_CODER_WHEEL_PULSE_BY_ROTATION_INDEX                    EEPROM_KINEMATICS_START_INDEX + 12

// MOTORS PART
#define EEPROM_MOTOR_WHEEL_AVERAGE_DIAMETER_INDEX                     EEPROM_KINEMATICS_START_INDEX + 16
#define EEPROM_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX              EEPROM_KINEMATICS_START_INDEX + 20
#define EEPROM_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_INDEX    EEPROM_KINEMATICS_START_INDEX + 24
#define EEPROM_MOTOR_MAX_TORQUE_MILLI_NEWTON_INDEX                    EEPROM_KINEMATICS_START_INDEX + 28
#define EEPROM_MOTOR_REDUCTOR_RATIO_INDEX                             EEPROM_KINEMATICS_START_INDEX + 32

// ROBOT PART
#define EEPROM_ROBOT_WEIGHT_GRAMS_INDEX                               EEPROM_KINEMATICS_START_INDEX + 36
#define EEPROM_ROBOT_TYPE_INDEX                                       EEPROM_KINEMATICS_START_INDEX + 40


// DEFAULT VALUES FOR BIG ROBOT

// -> CODER WHEEL

/** Average coder wheel diameter (mm). */
#define BIG_ROBOT_KINEMATICS_CODER_WHEEL_AVERAGE_DIAMETER_MM_DEFAULT_VALUE                       31.410f
#define SMALL_ROBOT_KINEMATICS_CODER_WHEEL_AVERAGE_DIAMETER_MM_DEFAULT_VALUE                     29.420f

// To compensate difference between Coder Wheels Diameter (mm)
#define BIG_ROBOT_KINEMATICS_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM_DEFAULT_VALUE                 0.096f 
#define SMALL_ROBOT_KINEMATICS_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM_DEFAULT_VALUE               0.096f  

/** Default wheels distance (mm)). */
#define BIG_ROBOT_KINEMATICS_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_MM_DEFAULT_VALUE                282.60f
#define SMALL_ROBOT_KINEMATICS_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_MM_DEFAULT_VALUE              268.00f


// FOR 7500 x 4 (quadratic) = 30 000
#define BIG_ROBOT_KINEMATICS_CODER_WHEEL_PULSE_BY_ROTATION_DEFAULT_VALUE                         20000.0f
#define SMALL_ROBOT_KINEMATICS_CODER_WHEEL_PULSE_BY_ROTATION_DEFAULT_VALUE                       20000.0f

// -> MOTOR WHEEL

// The average diameter of the motor wheel
#define BIG_ROBOT_KINEMATICS_MOTOR_WHEEL_AVERAGE_DIAMETER_MM_DEFAULT_VALUE                         62.0f
#define SMALL_ROBOT_KINEMATICS_MOTOR_WHEEL_AVERAGE_DIAMETER_MM_DEFAULT_VALUE                       62.0f


// The average distance between motor wheel. It could be needed when we do some rotation, between the must apply 
// a factor between the distance of motor and the distance of coder wheel. This is not the case when we go forward
#define BIG_ROBOT_KINEMATICS_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_MM_DEFAULT_VALUE                240.00f
#define SMALL_ROBOT_KINEMATICS_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_MM_DEFAULT_VALUE              185.00f

// How many rotation the motor do by second at full speed (full PWM) with nominal input tension
#define BIG_ROBOT_KINEMATICS_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_DEFAULT_VALUE           7.0f
#define SMALL_ROBOT_KINEMATICS_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_DEFAULT_VALUE         7.0f

// The max torque at nominal input tension : default value for 2642W012CXR (Faulhaber)
#define BIG_ROBOT_KINEMATICS_MOTOR_MAX_TORQUE_MILLI_NEWTON_DEFAULT_VALUE                          25.0f
#define SMALL_ROBOT_KINEMATICS_MOTOR_MAX_TORQUE_MILLI_NEWTON_DEFAULT_VALUE                        25.0f

// The reductor ratio default value for Planetary Gearheads 32/1
#define BIG_ROBOT_KINEMATICS_MOTOR_REDUCTOR_RATIO_DEFAULT_VALUE                                   14.0f
#define SMALL_ROBOT_KINEMATICS_MOTOR_REDUCTOR_RATIO_DEFAULT_VALUE                                 14.0f

// -> ROBOT

// The weight of the robot
#define BIG_ROBOT_KINEMATICS_ROBOT_WEIGHT_GRAMS                                                 6000.0f
#define SMALL_ROBOT_KINEMATICS_ROBOT_WEIGHT_GRAMS                                               5000.0f



/**
 * Load the Kinematics parameters from the eeprom_ to the structure given in parameter. It can be used to load Default Values when nothing is in the eeprom.
 * @param robotKinematics Structure with all parameters
 * @param eeprom_ the eeprom object to store long term values
 * @param loadDefaultValues if we load the default values (Focus Robotique bot).
 */
void loadRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_, bool loadDefaultValues);

/**
* Save the Kinematics parameters to the eeprom_ from the structure given in parameter.
* @param robotKinematics Structure with all parameters
* @param eeprom_ the eeprom object to store long term values
*/
void saveRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_);

#endif
