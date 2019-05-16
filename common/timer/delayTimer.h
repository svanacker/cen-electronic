#ifndef DELAY_TIMER_H
#define DELAY_TIMER_H

#include <stdlib.h>
#include <stdbool.h>

#include "cenTimer.h"

Timer* timerDelayMark(void);

void timerDelayWaitMark(Timer* delayTimer, unsigned long delayMilliSeconds);

bool timerDelayTimeout(Timer* delayTimer, unsigned long delayMilliSeconds);

/**
 * WARNING : This method MUST NOT be used inside a method raised by an interruption itself.
 * If we would like to do something frequently, use State Machine, and only use this method 
 * inside the main method.
 * Do a delay of milli Seconds based on a system delay timer which tends 
 * to be more precise than the cenDelay.h which raises some problem when some 
 * interruptions are raised because it longers and leads to an anormal delay
 * @param delayMilliSeconds how much milliSeconds we wait
 */
void timerDelayMilliSeconds(unsigned long delayMilliSeconds);

/**
 * Initialize a system delay timer used to be more precise than the
 * cenDelay.h which raises some problem when some interruptions are raised 
 * because it longers and leads to an anormal delay.
 * @return true if the delay is initialized properly, false else
 */
bool initSystemDelayTimer(void);

#endif
