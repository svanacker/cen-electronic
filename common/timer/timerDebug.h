#ifndef CEN_TIMER_DEBUG_H
#define CEN_TIMER_DEBUG_H

#include "cenTimer.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"


/**
* Print the content of Timer.
*/
void printTimer(OutputStream* outputStream, Timer* timer);

/**
* Print the timer List loaded in the system.
*/
void printTimerList(OutputStream* outputStream, TimerList* timerList);

#endif

