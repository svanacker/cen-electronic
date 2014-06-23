#include <stdlib.h>

#include "../../common/commons.h"

#include <timer.h>

#ifndef PROG_32
    #include <delay.h>
#endif

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "timerList.h"
#include "cenTimer.h"

// We use singleton pattern
static TimerList timerList;

TimerList* getTimerList() {
    return &timerList;
}

void initTimerList(Timer (*timerListArray)[], unsigned char timerListSize) {
    timerList.timers = timerListArray;
    timerList.maxSize = timerListSize;
}

Timer* addTimer(int timerCode,
                unsigned long timeDiviser,
                interruptTimerCallbackFunc* callback) {
    unsigned char size = timerList.size;
    if (size < timerList.maxSize) {
        Timer* result = (Timer*) timerList.timers;
         result += size;
        result->time = 0;
        result->markTime = 0;
        result->timerCode = timerCode;
        result->timeDiviser = timeDiviser;
        result->callback = callback;
        result->enabled = false;
        result->lock = false;
        result->working = false;

        timerList.size++;
        return result;
    }
    else {
        writeError(TOO_MUCH_TIMERS);
        return NULL;
    }
}

Timer* getTimerByIndex(int index) {
    Timer* result = (Timer*) timerList.timers;
    result += index;
    return result;
}

Timer* getTimerByCode(int timerCode) {
    int i;
    for (i = 0; i < timerList.size; i++) {
        Timer* timer = getTimerByIndex(i);
        if (timer->timerCode == timerCode) {
            return timer;
        }
    }
    return 0;
}

int getTimerCount() {
    return timerList.size;
}

/**
 * @private
 */
void initTimers() {
    unsigned int config1;
    unsigned int config2;
    unsigned int period;

    #ifndef PROG_32
    config1 = (T1_ON //T1ON = 1 Active le TIMER1
            & T1_IDLE_CON //operate during sleep
            & T1_GATE_OFF //Timer Gate time accumulation disabled
            & T1_PS_1_256 //T1CKPS = 00 prescaler 1:256
            & T1_SYNC_EXT_OFF //Do not synch external clk input
            & T1_SOURCE_INT); //TCS = 0 timer clock source set to internal

    config2 = (T1_INT_PRIOR_4 //Interrupt is priority 4
            & T1_INT_ON); //Active l'interruption;


    /* TCY = TEMPS DE CYCLE : 1/((7372800*16)/4) = 33.9084 nanosec
       period must be < 65535
       tempo in seconds
       TCY in seconds
       T1_PS diviseur : 1 or 4 or 16 or 256
      
       period = Tempo ( TCY * T1_PS)
       57444  = 0.5   ( 0.000000034 * 256 )
     */
    period = 3; // => we must multiply by (period + 1)

    // met a 0 le TIMER1 , set the TIMER1 and define incrementation count
    // avnt interruption
    OpenTimer1(config1, period);

    // Define the interruption priority and activate interruption
    ConfigIntTimer1(config2);

    #endif
}

void startTimerList() {
    initTimers();
    int i;
    for (i = 0; i < timerList.size; i++) {
        Timer* timer = getTimerByIndex(i);
        startTimer(timer);
    }
}

void stopTimerList() {
    int i;
    for (i = 0; i < timerList.size; i++) {
        Timer* timer = getTimerByIndex(i);
        stopTimer(timer);
    }
}

/**
 * @private
 * @interrupt
 * Function called by the timer.
 */
void __attribute__((__interrupt__)) __attribute__((no_auto_psv)) _T1Interrupt(void) {
    #ifndef PROG_32
    // Clear the interrupt flag
    _T1IF = 0;

    if (timerList.size) {
        int i = 0;
        for (i = 0; i < timerList.size; i++) {
            Timer* currentTimer = getTimerByIndex(i);
            bool enabled = currentTimer->enabled;
            if (!enabled) {
                continue;
            }
            // increments the counter and test if it is > to the timeDiviser
            if (++(currentTimer->timeInternalCounter) > currentTimer->timeDiviser) {
                // block the timer if we wait for
                bool lock = currentTimer->lock;
                if (lock) {
                    continue;
                }

                // we only substract and not clear to 0, so that, if the timer is locked, we will not forget
                // any firing
                currentTimer->timeInternalCounter -= (currentTimer->timeDiviser + 1);
                currentTimer->time++;

                // lock the timer to avoid concurrence problem
                currentTimer->working = true;
                if (currentTimer->callback) {
                    currentTimer->callback(currentTimer);
                }
                // indicates the timer is not working
                currentTimer->working = false;
            }
        }
    }
    // Enable the interrupt
    _T1IE = 1;
    #endif
}
