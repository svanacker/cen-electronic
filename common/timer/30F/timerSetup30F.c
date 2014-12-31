#include "../timerSetup.h"

#include <p30Fxxxx.h>
#include <timer.h>

/**
 * @private
 */
void _initTimers() {
    unsigned int config1;
    unsigned int config2;
    unsigned int period;

    config1 = (T1_ON            // T1ON = 1 Active le TIMER1
            & T1_IDLE_CON       // operate during sleep
            & T1_GATE_OFF       // Timer Gate time accumulation disabled
            & T1_PS_1_256       // T1CKPS = 00 prescaler 1:256
            & T1_SYNC_EXT_OFF   // Do not synch external clk input
            & T1_SOURCE_INT);   // TCS = 0 timer clock source set to internal

    config2 = (T1_INT_PRIOR_4 // Interrupt is priority 4
            & T1_INT_ON);     // Activate the interruption


    /* TCY = TEMPS DE CYCLE : 1/((7372800*16)/4) = 33.9084 nano seconds
       period must be < 65535
       tempo in seconds
       TCY in seconds
       T1_PS diviser : 1 or 4 or 16 or 256
      
       period = Tempo ( TCY * T1_PS)
       57444  = 0.5   ( 0.000000034 * 256 )
     */
    period = 3; // => we must multiply by (period + 1)

    // set to 0 the TIMER1, set the TIMER1 and define incrementation count
    // before interrupt
    OpenTimer1(config1, period);

    // Define the interruption priority and activate interruption
    ConfigIntTimer1(config2);
}
