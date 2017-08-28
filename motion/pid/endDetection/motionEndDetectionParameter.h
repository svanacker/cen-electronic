#ifndef MOTION_END_DETECTION_PARAMETER_H
#define MOTION_END_DETECTION_PARAMETER_H

// BLOCKING DETECTION

/** Defines the delta position integral for which we consider that below this value the robot don't move */
#define ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD 1.0f

/**
* Defines the u integral factor integral for which we consider that there is a blocking.
* For example, if the value is equal to 4, it indicates that if the average integral of U is more than
* the normal value of u (with no load), we must consider it as a blocking
*/
#define MAX_U_INTEGRAL_FACTOR_THRESHOLD 3.0f

/**
* When the robot is very low, the answer of the motor is not linear, and we can thing that the robot is blocked, because,
* the consign is very high compared to the normal value
*/
#define MAX_U_INTEGRAL_CONSTANT_THRESHOLD 10.0f

/**
* The delay for which we consider that we are blocked or if we have reached if we don't go anymore
*/
#define BLOCKING_OR_REACH_DETECTION_DELAY 10

/**
* The delay for which we do not try to know if the robot is rolling or blocked
*/
#define BLOCKING_OR_REACH_SKIP_DETECTION_DELAY 60

/**
 * Define a structure which is able to detect either blocking or either end of trajectory.
 */
typedef struct MotionEndDetectionParameter {
    /**
    * Defines the delta position integral for which we consider that below this value the robot don't move
    */
    float absDeltaPositionIntegralFactorThreshold;
    /**
    * Defines the u integral factor integral for which we consider that there is a blocking.
     * For example, if the value is equal to 4, it indicates that if the average integral of U is more than 4x
     * the normal value of u (with no load), we must consider it as a blocking
    */
    float maxUIntegralFactorThreshold;
    /** 
    * When the robot is very low, the answer of the motor is not linear, and we can thing that the robot is blocked, because,
     * the consign is very high compared to the normal value. So this value is 
    */
    float maxUIntegralConstantThreshold;
    /**
    * TimeRangeAnalysis. It's important to detect on a small range to determine if the robot is blocked or not (to avoid problems with motors). But too short 
    * range time analysis give sometimes bad analysis. It's also important to detect on a small range to have a decision of end detection (to continue on next instruction). But too short 
    * range time analysis give sometimes bad analysis.
    */
    unsigned int timeRangeAnalysis;
    /** 
     * The delay in milliseconds for which we do not try to check the end detection parameter.
     * It avoids that the robot stop immediately the begin of motion, because it consideres 
     * that the robot is blocked or has ended his trajectory
    */
    unsigned int noAnalysisAtStartupTime;
} MotionEndDetectionParameter;

/**
* Initialize the parameters for the detection of end or blocking of motion.
*/
void initMotionEndParameter(MotionEndDetectionParameter* parameter);

#endif

