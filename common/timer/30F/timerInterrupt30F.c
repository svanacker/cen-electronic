#include "../timerInterrupt.h"
#include "../timerList.h"

#include <p30Fxxxx.h>

/**
 * @private
 * @interrupt
 * Function called by the timer.
 */
void __attribute__((__interrupt__)) __attribute__((no_auto_psv)) _T1Interrupt(void) {
    #ifndef PROG_32
    // Clear the interrupt flag
    _T1IF = 0;

    _internalUpdateTimerListValues();

    // Enable the interrupt
    _T1IE = 1;
    #endif
}
