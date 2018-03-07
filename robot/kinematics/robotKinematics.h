#ifndef ROBOT_KINEMATICS_H
#define ROBOT_KINEMATICS_H

#include "../../common/eeprom/eeprom.h"

#define MILLI_TO_MICRO_FACTOR                                    1000.0f
#define MILLI_TO_NANO_FACTOR                                     1000000.0f
/** 
 * Encapsulation of all information needed to manage the Kinematics (Rotation, Forward / Backward) and coders capacities.
 */
typedef struct RobotKinematics {
    // CODER WHEEL VALUES
    /** Average coder wheel diameter (mm). */
    float coderWheelAverageDiameterMM;
    /** To compensate difference between Coder Wheels Diameter (mm). */
    float coderWheelAverageDeltaDiameterMM;
    /** Default wheels distance (mm)). */
    float coderWheelDistanceBetweenWheelsMM;
    /** Coder Wheel pulse by rotation. Ex ! FOR 5000 x 4 (quadratic) = 20 000. */
    float coderWheelPulseByRotation;

    // MOTOR WHEEL VALUES
    /** The average diameter of the motor wheel. We don't need to be so accurate than for coder wheel, this is the reason why we don't introduce Delta correction for Motor Wheel diameter */
    float motorWheelAverageDiameterMM;
    /** The average distance between The average distance between motor wheel. It could be needed when we do some rotation, between the must apply 
     * a factor between the distance of motor and the distance of coder wheel. This is not the case when we go forward
     */
    float motorWheelDistanceBetweenWheelsMM;
    /** How many rotation the motor do by second at full speed (full PWM). */
    float motorWheelRotationBySecondAtFullSpeed;
} RobotKinematics;

/** 
 * Get the Robot Kinematics information.
 * @return Robot Kinematics information
 */
RobotKinematics* getRobotKinematics(void);

// CODER VALUE

/**
 * Returns the average diameter for the coder wheel In mm.
 */
float getCoderWheelAverageDiameterMM(RobotKinematics* robotKinematics);

void setCoderWheelAverageDiameterMM(RobotKinematics* robotKinematics, float value);


float getCoderWheelAverageDeltaDiameterMM(RobotKinematics* robotKinematics);

void setCoderWheelAverageDeltaDiameterMM(RobotKinematics* robotKinematics, float value);


float getCoderWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics);

void setCoderWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics, float value);


float getCoderWheelPulseByRotation(RobotKinematics* robotKinematics);

void setCoderWheelPulseByRotation(RobotKinematics* robotKinematics, float value);

// MOTOR WHEEL VALUES

/**
 * The average diameter of the motor wheel.
 */
float getMotorWheelAverageDiameterMM(RobotKinematics* robotKinematics);

void setMotorWheelAverageDiameterMM(RobotKinematics* robotKinematics, float value);

/**
*  The average distance between The average distance between motor wheel. It could be needed when we do some rotation, between the must apply
 * a factor between the distance of motor and the distance of coder wheel. This is not the case when we go forward
*/
float getMotorWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics);

void setMotorWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics, float value);

/** How many rotation the motor do by second at full speed (full PWM). */
float getMotorWheelRotationBySecondAtFullSpeed(RobotKinematics* robotKinematics);

void setMotorWheelRotationBySecondAtFullSpeed(RobotKinematics* robotKinematics, float value);

// COMPUTED VALUES

// 

float getCoderLeftWheelDiameter(RobotKinematics* robotKinematics);

float getCoderRightWheelDiameter(RobotKinematics* robotKinematics);

float getCoderWheelsDistanceFromCenter(RobotKinematics* robotKinematics);


/**
* Returns the wheels half distance (from center to one coder wheel).
* @param robotKinematics Structure with all parameters
*/
float getCoderWheelsDistanceFromCenter(RobotKinematics* robotKinematics);


// DIFFERENT LENGTH FOR ONE PULSE (left, right, average)

/**
 * Returns the wheel left length for One Pulse.
 * We use the average value of both wheels and we use delta value (+ for left, - for right).
 */
float getCoderLeftWheelLengthForOnePulse(RobotKinematics* robotKinematics);

/**
* Returns the wheel right length for One Pulse.
* We use the average value of both wheels and we use delta value (+ for left, - for right).
*/
float getCoderRightWheelLengthForOnePulse(RobotKinematics* robotKinematics);

/**
 * Returns the average wheel length distance in mm for One Pulse in coder 
 * We use the average value of both wheels and we use delta value (+ for left, - for right).
 */
float getCoderAverageWheelLengthForOnePulse(RobotKinematics* robotKinematics);

// COMPUTE INVOLVING MOTOR AND CODERS

float getCoderWheelAndMotorWheelAverageDiameterFactor(RobotKinematics* robotKinematics);

/**
 * Get the total amount of pulse done by the coer by seconds at full speed.
 * We must consider that there is a factor between motor wheel diameter and coder wheel diameter
 * @param robotKinematics Structure with all parameters
 * @param rotationMode if we rotate, we must introduce a new factor depending on the geometry of the motor wheel / coder wheel distance. If we are in forward / backward mode
 * we only need to manage the factor between motor wheel diameter and coder wheel diameter
 * @return the total amount of pulse done by seconds at full speed
 */
float getCoderWheelPulseBySecondsAtFullSpeed(RobotKinematics* robotKinematics, bool rotationMode);

/**
* Convert for a rotation around center (both left and right wheel) the distance to do
* for the left Wheel to reach an angle of angleDeciDegree (unit = 1/10 degree)
* @param robotKinematics
* @param angleDeciDegree the rotation
* @return the number of left pulse to do to accomplish the rotation
*/
float rotationInDeciDegreeToRealDistanceForLeftWheel(RobotKinematics* robotKinematics, float angleDeciDegree);

/**
* Convert for a rotation around center (both left and right wheel) the distance to do
* for the right Wheel to reach an angle of angleDeciDegree (unit = 1/10 degree)
* @param robotKinematics
* @param angleDeciDegree the rotation
* @return the number of right pulse to do to accomplish the rotation
*/
float rotationInDeciDegreeToRealDistanceForRightWheel(RobotKinematics* robotKinematics, float angleDeciDegree);

#endif
