#include <timer.h>
#include <delay.h>

#include "../../common/commons.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "timerList.h"
#include "cenTimer.h"

// We use singleton pattern
static TimerList instance;

void addTimer(Timer* timer) {
    unsigned char size = instance.size;
    instance.timers[size] = timer;
    instance.size++;
}

Timer* getTimerByIndex(int index) {
    return instance.timers[index];
}

Timer* getTimerByCode(int timerCode) {
    int i;
    for (i = 0; i < instance.size; i++) {
        Timer* timer = instance.timers[i];
        if (timer->timerCode == timerCode) {
            return timer;
        }
    }
    return 0;
}

int getTimerCount() {
    return instance.size;
}

/**
 * @private
 */
void initTimers() {
    unsigned int config1;
    unsigned int config2;
    unsigned int period;

    config1 = (T1_ON //T1ON = 1 Active le TIMER1
            & T1_IDLE_CON //operate during sleep
            & T1_GATE_OFF //Timer Gate time accumulation disabled
            & T1_PS_1_256 //T1CKPS = 00 prescaler 1:256
            & T1_SYNC_EXT_OFF //Do not synch external clk input
            & T1_SOURCE_INT); //TCS = 0 timer clock source set to internal

    config2 = (T1_INT_PRIOR_4 //Interrupt is priority 4
            & T1_INT_ON); //Active l'interruption;


    /* TCY = TEMPS DE CYCLE : 1/((7372800*16)/4) = 33.9084 nanosec
       period doit etre inferieur � 65535
       tempo en seconde
       TCY en seconde
       T1_PS diviseur : 1 ou 4 ou 16 ou 256
	  
       period = Tempo ( TCY * T1_PS)
       57444  = 0.5   ( 0.000000034 * 256 )
     */
    period = 3; // => we must multiply by (period + 1)

    // met � 0 le TIMER1 , Configure le TIMER1 et definie le nombre d'incrementation
    // avnt interruption
    OpenTimer1(config1, period);

    // Definit la priorit�e de l'interruption, Active l'interruption
    ConfigIntTimer1(config2);
}

void startTimerList() {
    initTimers();
    int i;
    for (i = 0; i < instance.size; i++) {
        Timer* timer = instance.timers[i];
        startTimer(timer);
    }
}

void stopTimerList() {
    int i;
    for (i = 0; i < instance.size; i++) {
        Timer* timer = instance.timers[i];
        stopTimer(timer);
    }
}

/**
 * @private
 * @interrupt
 * Function called by the timer.
 */
void __attribute__((__interrupt__)) __attribute__((no_auto_psv)) _T1Interrupt(void) {
    // Clear the interrupt flag
    _T1IF = 0;

    if (instance.size) {
        int i = 0;
        for (i = 0; i < instance.size; i++) {
            Timer * currentTimer = instance.timers[i];
            BOOL enabled = currentTimer->enabled;
            if (!enabled) {
                continue;
            }
            // increments the counter and test if it is > to the timeDiviser
            if (++(currentTimer->timeInternalCounter) > currentTimer->timeDiviser) {
                // block the timer if we wait for
                BOOL lock = currentTimer->lock;
                if (lock) {
                    continue;
                }

                // we only substract and not clear to 0, so that, if the timer is locked, we will not forget
                // any firing
                currentTimer->timeInternalCounter -= (currentTimer->timeDiviser + 1);
                currentTimer->time++;

                // lock the timer to avoid concurrence problem
                currentTimer->working = TRUE;
                if (currentTimer->callback) {
                    currentTimer->callback();
                }
                // indicates the timer is not working
                currentTimer->working = FALSE;
            }
        }
    }
    // Enable the interrupt
    _T1IE = 1;
}
