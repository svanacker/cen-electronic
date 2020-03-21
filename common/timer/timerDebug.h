#ifndef TIMER_DEBUG_H
#define TIMER_DEBUG_H

#include "cenTimer.h"
#include "timerList.h"

#include "../../common/io/outputStream.h"

/**
 * Print the content of Timer.
 * @param outputStream the stream in which we write information.
 * @param timer the timer for which we write the content.
 */
void printTimer(OutputStream* outputStream, Timer* timer);

/**
 * Print the timer List loaded in the system.
 * @param outputStream the stream in which we write information.
 * @param timerList the timer list for which we write the content.
 */
void printTimerList(OutputStream* outputStream, TimerList* timerList);

#endif

