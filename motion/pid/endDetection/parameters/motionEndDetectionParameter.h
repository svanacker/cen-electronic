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
    /** TODO : explanation. */
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
     * The delay in seconds (but often in milliseconds, we use float)
     * for which we do not try to check the end detection parameter.
     * It avoids that the robot stop immediately the begin of motion, because it analyses 
     * if the robot is blocked or has ended his trajectory
     */
    float noAnalysisAtStartupTimeInSecond;
    
    // FAILED
    /**
     * If we don't detect that we reach after t3 + x seconds, we consider that 
     * the motion was failed
     */
    float failedTimeoutAfterT3InSecond;
    
    // REACHED
    /**
     * How much sample we do in a window to detect that we reached the target
     */
    float reachedWindowCount;
    /**
     * How much in cumulative derivative Error in the window (see previous parameter)
     * must be < to consider that we reach the target
     */
    float reachedDerivativeErrorThreshold;
    
    // SHOCKED
    /**
     * From which value of max acceleration we consider that we consider it 
     * as possibly a problem of "shock"
     */
    float shockedAccelerationMaxForOneValueThreshold;
    /**
     * The Window analysis Count to detect shock
     */
    float shockedAccelerationWindowAnalysisCount;
    /**
     * How many times for the window analysis the acceleration is too much
     */
    float shockedAccelerationWindowsMatchCount;
    
    // FAILED
    /**
     * How much PID must be analysis to detect blocking
     */
    float blockedWindowsAnalysisCount;
    
    /**
     * The percentage (between 0 and 1) so that we could consider that the robot
     * is blocked when 
     */
    float blockedPercentageThreshold;
    
} MotionEndDetectionParameter;

// For Communication Exchange
#define MOTION_END_DETECTION_PARAMETER_DIGIT           3

#endif

