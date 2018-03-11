#ifndef PID_TIMER_H
#define PID_TIMER_H

#include "../../common/timer/cenTimer.h"

#include <stdbool.h>

// We try to raise as often we could, but we launch real Pid only every 312 cycle
#define PID_BASE_DIVISER                           1

// The frequency that we would like
#define PID_UPDATE_MOTORS_FREQUENCY_HERZ         100

// The diviser that it implies
#define PID_UPDATE_MOTOR_TIMER_INTERVAL          (TIME_DIVIDER_1_HERTZ / PID_UPDATE_MOTORS_FREQUENCY_HERZ)

/**
 * Random Code to be sure there is no conflict with other TIMER Code.
 */
#define TIMER_PID_CODE           107

/**
 * Init the timer used by the PID system.
 */
void initPidTimer(void);

/** 
 * Clear the PID system.
 */
void clearPidTime(void);

/**
 * Determine 
 */
bool mustPidBeRecomputed(void);

/**
 * Get the pid Timer frequency in hertz.
 */
float getPidTimerFrequencyHertz(void);
/**
 * Get the pid time, used to compare where the robot has to be at a specific pid Time, with the real position at the same specific pidTime.
 */
float getPidTimeInSecond(void);

#endif
