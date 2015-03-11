#ifndef PID_H
#define PID_H

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"
#include "../../common/io/outputStream.h"

#include "../../device/device.h"

#include "../../motion/extended/bspline.h"

#include "../../motion/pid/instructionType.h"
#include "../../motion/pid/motionEndDetection.h"
#include "../../motion/pid/detectedMotionType.h"
#include "../../motion/pid/pidType.h"
#include "../../motion/pid/pidTimer.h"
#include "../../motion/pid/profileType.h"

#include "../../motion/simple/motionParameterType.h"

#include "../../robot/robotConstants.h"

#define WHEEL_PULSE_BY_PID_TIME_AT_FULL_SPEED        (WHEEL_PULSE_BY_SECONDS_AT_FULL_SPEED / PID_UPDATE_MOTORS_FREQUENCY)
#define U_FACTOR_AT_FULL_SPEED                                128.0f    / WHEEL_PULSE_BY_PID_TIME_AT_FULL_SPEED

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

// NUMBER OF NEXT_MOTION_DEFINITION_COUNT

#define NEXT_MOTION_DEFINITION_COUNT 2

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

/**
 * Defines the structs which stores the errors.
 */
typedef struct MotionError {
    /** Stores the previous error */
    float previousError;
    /** The error between normal speed and real speed */
    float error;
    /** The derivative error between normal speed and real speed */
    float derivativeError;
    /** The integral error between normal speed and real speed */
    float integralError;
} MotionError;


/**
 * Defines a struct which stores current and old Values of position, and voltage supplied to the motor.
 */
typedef struct Motion {
    /** current position values. */
    float position;
    /** Old Position values. */
    float oldPosition;
    /** Speed. */
    float currentSpeed;
    /** U (voltage) values. */
    float u;
} Motion;

/**
 * Defines the structs which stores the instruction.
 */
typedef struct MotionInstruction {
    /** the position which must be reached when using classic implementation */
    float nextPosition;
    /** The acceleration which is asked : > 0 */
    float a;
    /** The initial speed. */
    float initialSpeed;
    /** The maximal speed which is asked : > 0 */
    float speed;
    /** The maximal speed which can be reached : negative or positive */
    float speedMax;
    /** The target end Speed (decelerationTime). */
    float endSpeed;
    /** The acceleration time > 0 */
    float t1;
    /** The time before deceleration > 0 */
    float t2;
    /** The time after deceleration > 0 */
    float t3;
    /** The first position after acceleration time */
    float p1;
    /** The first position after speed constant */
    float p2;
    /** The type of the trajectory (TRAPEZE / TRIANGLE) */
    enum ProfileType profileType;
    /** The type of MotionParameterType (GO, ROTATION, MAINTAIN_POSITION). */
    enum MotionParameterType motionParameterType;
    /** The type of pid which must be used. */
    enum PidType pidType;
} MotionInstruction;

/**
 * Define the function used to compute Errors.
 */
typedef void ComputeUFunction();

/**
 * All current values about the current motion in progress.
 */
typedef struct PidComputationValues {
    // ONLY ONE VALUE AT A TIME
    // theta error (distance for normal trajectory, and along Y axis for Spline Curve)
    float thetaError;
    // angle error
    float alphaError;
    // theta error (only for Curve implementation)
    // determine the distance between normal trajectory tangent line
    // and real trajectory tangent line (=> X Axis)
    float thetaXAxisError;
    // store the time of the pid timer
    float pidTime;
    // Store error of each motion
    MotionError err[INSTRUCTION_COUNT];
    // store tension / position / current speed
    Motion motion[INSTRUCTION_COUNT];
    // Store Detection of end of trajectory
    MotionEndInfo motionEnd[INSTRUCTION_COUNT];
} PidComputationValues;

/**
 * Definition of motion. There can be more than one PidMotionDefinition, but only one active
 * at a time.
 */
typedef struct PidMotionDefinition {
    // Alpha / Theta
    MotionInstruction inst[INSTRUCTION_COUNT];
    // When using BSPline
    BSplineCurve curve;
    /** The method which will compute the errors (by using coders or absolute positions) .*/
    ComputeUFunction* computeU;
} PidMotionDefinition;

/**
 * All parameters about pid motion. Don't change by PidMotion. Are normally constants
 * or set only for a match.
 */
typedef struct PidGlobalParameters {
    // Parameters about PID
    Pid pid[PID_COUNT];
    // Parameters about end motion detection (avoid rotation of wheels in case of no move => Avoid BURN OUT)
    MotionEndDetectionParameter motionEndDetectionParameter;
} PidGlobalParameters;

/**
 * Global struct to make links between all structures and variables to achieve
 * motion with PID.
 */
typedef struct PidMotion {
    // Parameters for all motions => INVARIANT.
    PidGlobalParameters globalParameters;
    // The current motion definition => CHANGE FOR EACH MOTION.
    PidMotionDefinition currentMotionDefinition;
    // Contains the next Motion Definition;
    PidMotionDefinition nextMotionDefinition[NEXT_MOTION_DEFINITION_COUNT];
    // All current values (must be reset after each new move) => CHANGE EVERY TIME COMPUTATION
    PidComputationValues computationValues;
} PidMotion;

/**
 * Returns the current pidMotion.
 */
PidMotion* getPidMotion();

/**
 * Returns the parameters of the end motion.
 */
MotionEndDetectionParameter* getMotionEndDetectionParameter();

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
