#ifndef PID_TIMER_H
#define PID_TIMER_H

#include "../../common/commons.h"

/**
 * Motors update frequency in number of interruption cycles.
 * For example, if base frequency is 28800, and PID_UPDATE_MOTORS_FRQ = 400
 * we have a pid frequency of 72 Hz
 */
#define PID_UPDATE_MOTORS_FREQUENCY 192

#define TIMER_PID_CODE 		  107

void initPidTimer(void);

void clearPidTime(void);

BOOL mustPidBeRecomputed(void);

long getPidTime(void);

#endif
