#ifndef PID_TIMER_H
#define PID_TIMER_H

#include <stdbool.h>

/**
 * Motors update frequency in number of interruption cycles.
 * For example, if base frequency is 28800, and PID_UPDATE_MOTORS_FRQ = 400
 * we have a pid frequency of 72 Hz
 */
#define PID_UPDATE_MOTORS_FREQUENCY 192

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
 * Get the pid time, used to compare where the robot has to be at a specific pid Time, with the real position at the same specific pidTime.
 */
long getPidTime(void);

#endif
