#ifndef MOTION_END_DETECTION_PARAMETER_H
#define MOTION_END_DETECTION_PARAMETER_H

#include <stdbool.h>

// TO SET THE STATUS BEFORE COMPUTE THE INTEGRAL


/**
 * Define a structure which is able to detect either blocking or either end of trajectory.
 */
typedef struct MotionEndDetectionParameter {
    // BEFORE AGGREGATION PHASE
    /** For example : abs(acceleration) > accelerationTooHighTresholdFactor * normalAcceleration => detected as abnormal. */
    float accelerationTooHighTresholdFactor;
    /** Example : speed < speedTooLowThresholdFactor * normalSpeed => detected as abnormal. */
    float speedTooLowThresholdFactor;
    /** Example : U > uTooHighTresholdFactor * normalU => detected as abnormal. */
    float uTooHighTresholdFactor;
    /** We do not detect end detection when we are too slow */
    float speedMinThreshold;
    /** We do not detect end detection when u is too slow */
    float uMinThresholdValue;
    
    // FOR AGGREGATION PHASE
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
    float timeRangeAnalysisInSecond;
    /** 
     * The delay in milliseconds for which we do not try to check the end detection parameter.
     * It avoids that the robot stop immediately the begin of motion, because it analyses 
     * if the robot is blocked or has ended his trajectory
    */
    float noAnalysisAtStartupTimeInSecond;
} MotionEndDetectionParameter;

// For Communication Exchange
#define MOTION_END_DETECTION_PARAMETER_DIGIT           3

#endif

