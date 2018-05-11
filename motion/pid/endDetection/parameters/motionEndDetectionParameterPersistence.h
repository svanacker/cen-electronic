#ifndef MOTION_END_DETECTION_PARAMETER_PERSISTENCE_H
#define MOTION_END_DETECTION_PARAMETER_PERSISTENCE_H

#include <stdbool.h>

#include "../../../../common/eeprom/eeprom.h"

#include "motionEndDetectionParameter.h"

// BASIC STATUS PARAMETER PHASE DETECTION

#define ACCELERATION_TOO_HIGH_THRESHOLD_FACTOR_DEFAULT_VALUE    20.0f
#define SPEED_TOO_LOW_THRESHOLD_FACTOR_DEFAULT_VALUE            5.0f
#define U_TOO_HIGH_THRESHOLD_FACTOR_DEFAULT_VALUE               5.0f
// In mm / sec
#define SPEED_MIN_THRESHOLD_DEFAULT_VALUE                       20.0f
// U is between 0 and 255 (or superior, but corresponding to max value)
#define U_MIN_THRESHOLD_DEFAULT_VALUE                           20.0f

// PARAMETERS USED IN AGGREGATION PHASE DETECTION

/** Defines the delta position integral for which we consider that below this value the robot don't move */
#define ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD_DEFAULT_VALUE 1.0f

/**
* Defines the u integral factor integral for which we consider that there is a blocking.
* For example, if the value is equal to 4, it indicates that if the average integral of U is more than
* the normal value of u (with no load), we must consider it as a blocking
*/
#define MAX_U_INTEGRAL_FACTOR_THRESHOLD_DEFAULT_VALUE              3.0f

/**
* When the robot is very low, the answer of the motor is not linear, and we can thing that the robot is blocked, because,
* the consign is very high compared to the normal value
*/
#define MAX_U_INTEGRAL_CONSTANT_THRESHOLD_DEFAULT_VALUE          10.0f

/**
* The delay in seconds for which we consider that we are blocked or if we have reached if we don't go anymore
*/
#define BLOCKING_OR_REACH_DETECTION_DELAY_DEFAULT_VALUE           0.1f

/**
* The delay for which we do not try to know if the robot is rolling or blocked
*/
#define BLOCKING_OR_REACH_SKIP_DETECTION_DELAY_DEFAULT_VALUE      0.3f

void loadMotionEndDetectionParameters(MotionEndDetectionParameter* motionEndDetectionParameter, Eeprom* motionEndDetectionParametersEeprom, bool loadDefaultValues);

void saveMotionEndDetectionParameters(MotionEndDetectionParameter* motionEndDetectionParameter, Eeprom* motionEndDetectionParametersEeprom);

#endif
