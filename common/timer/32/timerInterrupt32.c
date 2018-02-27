#include "../timerInterrupt.h"
#include "../timerList.h"

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include <sys/attribs.h>     /* For __ISR definition */

/**
 * @private
 * @interrupt
 * Function called by the timer.
 * Example Code inspired from : http://learn.digilentinc.com/Documents/216
 */
void __ISR(_TIMER_1_VECTOR, IPL3SOFT) Timer1Handler(void) {
    _internalUpdateTimerListValues(1);
    
    // clear the interrupt flag
    mT1ClearIntFlag();
}