#ifndef PID_H
#define PID_H

#include "../../common/commons.h"

#include "../../common/io/outputStream.h"

#include "../../device/device.h"

#include "../../motion/extended/bspline.h"

#include "../../motion/pid/motionEndDetection.h"
#include "../../motion/pid/pidTimer.h"

#include "../../robot/robotConstants.h"

#define WHEEL_PULSE_BY_PID_TIME_AT_FULL_SPEED		(WHEEL_PULSE_BY_SECONDS_AT_FULL_SPEED / PID_UPDATE_MOTORS_FREQUENCY)
#define U_FACTOR_AT_FULL_SPEED								128.0f	/ WHEEL_PULSE_BY_PID_TIME_AT_FULL_SPEED

// PID CONSTANT

// -> PID TO CONTROL

// Number of PID to control
#define INSTRUCTION_COUNT 2

// The index of theta & alpha instruction
#define INSTRUCTION_THETA_INDEX 0
#define INSTRUCTION_ALPHA_INDEX 1

// -> TYPES OF PID

// different types of PID_TYPE
#define PID_TYPE_COUNT 5

/** The mask used to indicate that we want to use value of PID to go forward and backward. */
#define PID_TYPE_GO_INDEX 0

/** The mask used to indicate that we want to use value of PID to rotate. */
#define PID_TYPE_ROTATE_INDEX 1

/** The mask used to indicate that we want to use value of PID to maintain very strongly the position. */
#define PID_TYPE_MAINTAIN_POSITION_INDEX 2

/** The mask used to indicate that we want to adjust the robot to the border of board. */
#define PID_TYPE_ADJUST_DIRECTION 3

/** The pid for final approach. */
#define PID_TYPE_FINAL_APPROACH_INDEX 4

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
 The real acceleration has for unit : coder count / time_sample�
 If we want to convert to m / s-�, we use the following formula :

 a = (a_coder_count / count_by_meter) / (time_sample�)
 Ex : 
  a_coder_count = 10, count_by_meter = 10000, time_sample = 0.005 (200 Hz)
  (10 / 10000) / 0.005� = 40 m s-� which is too much
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
#define ERROR_FOR_STRONG_PID 					20

/**
 * Defines the number of pid interrupt after the end (t3) to apply strong PID.
 */
#define TIME_PERIOD_AFTER_END_FOR_STRONG_PID	 40

// MOTION

/** No position to reach. */
#define NO_POSITION_TO_REACH 0

/** No position to reach, but a position to maintain. */
#define POSITION_TO_MAINTAIN 1

/** The trajectory is in progress. */
#define POSITION_IN_PROGRESS 2

/** The robot reach the position. */
#define POSITION_REACHED 3

/** The robot is directly blocked to move. */
#define POSITION_BLOCKED_WHEELS 4

/** The robot will hurt something (detection by RobotDetector). */
#define POSITION_OBSTACLE 5

/**
 * Defines the structure which is used to store PID values
 */
typedef struct {
    /** The proportionnal term */
    float p;
    /** The integral term */
    float i;
    /** The derivative term */
    float d;
    /** The maximal term of integral */
    float maxIntegral;
    /** Enable or not the pid. */
    unsigned char enabled;
} Pid;

/**
 * Defines the structs which stores the errors.
 */
typedef struct {
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
typedef struct {
    /** current position values. */
    float position;
    /** Old Position values. */
    float oldPosition;
	/** Speed. */
	float currentSpeed;
    /** U (voltage) values. */
    float u;
} Motion;

// forward declaration;
struct MotionInstruction;
typedef struct MotionInstruction MotionInstruction;

/**
 * Define the function used to compute Errors.
 * @param thetaError output param : the error (distance) which will be computed
 * @param alphaError output param : the error (angle) which will be computed
 */
typedef void ComputeUFunction(	MotionInstruction* thetaInst,
                                    MotionInstruction* alphaInst,
                                    Motion* thetaMotion,
                                    Motion* alphaMotion,
									float pidTime);

/**
 * Defines the structs which stores the instruction.
 */
struct MotionInstruction {
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
    /** The first position after accceleration time */
    float p1;
    /** The first position after speed constant */
    float p2;
    /** The type of the trajectory (TRAPEZE / TRIANGLE) */
    char profileType;
    /** The type of motion (GO, ROTATION, MAINTAIN_POSITION). */
    char motionType;
    /** The type of pid which must be used. */
    char pidType;
    /** The method which will compute the errors (by using coders or absolute positions) .*/
    ComputeUFunction* computeU;
};

/**
 * Global struct to make links between all structures and variables.
 */
typedef struct PidMotion {
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

    Pid * pid[PID_COUNT];
    MotionError * err[INSTRUCTION_COUNT];
    MotionInstruction * inst[INSTRUCTION_COUNT];
    Motion * motion[INSTRUCTION_COUNT];

    // Detection of end of trajectory
    MotionEndDetectionParameter* motionEndDetectionParameter;
	MotionEndInfo* motionEnd[INSTRUCTION_COUNT];
} PidMotion;

/**
 * Returns the motion curve.
 */
BSplineCurve* getMotionCurve();

/**
 * Returns the Index of Pid which must be choosen in function of pidType.
 * @param instructionIndex THETA_INDEX or ALPHA_MASK
 * @param pidType the type of pid PID_TYPE_GO_INDEX / PID_TYPE_ROTATE_INDEX / PID_TYPE_MAINTAIN_POSITION
 */
unsigned char getIndexOfPid(unsigned char instructionIndex, unsigned char pidType);

/**
 * Enable or disable a PID.
 * @param pidIndex the index of which pid we must change (between 0 and PID_INDEX_COUNT)
 * @param enabled FALSE or TRUE if we want to enabled or not the specified pid
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

MotionError* getMotionError(int index);

MotionInstruction* getMotionInstruction(int index);

Motion* getMotion(int index);

MotionEndInfo* getMotionEnd(int index);

/**
* Returns the parameter which are used to do the detection in the motion.
*/
MotionEndDetectionParameter* getMotionEndDetectionParameter();

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
 * Returns the instruction structure at the given index.
 * @param index the index of the instruction
 * @return the instruction structure at the given index
 */
MotionInstruction* getInst(int instructionIndex);

/**
 * Returns the value of the flag which determines if the
 * position must be reached.
 * @return TRUE or FALSE
 */
int getMustReachPosition(void);

/**
 * Sets the flag which determines if the
 * position must be reached.
 * @value the value of the flag, TRUE or FALSE
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
void initPID(void);

/**
 * Stop the PID.
 */
void stopPID(void);


#endif
