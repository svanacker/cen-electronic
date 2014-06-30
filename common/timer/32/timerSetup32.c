#include "../timerSetup.h"
#include "../cenTimer.h"

#include <p32xxxx.h>
#include <timer.h>


/**
 * @private
 */
void _initTimers() {
/*
    unsigned int config1;
    unsigned int config2;
    unsigned int period;

    config1 = (T1_ON            // T1ON = 1 Active le TIMER1
            & T1_IDLE_CON       // operate during sleep
            & T1_GATE_OFF       // Timer Gate time accumulation disabled
            & T1_PS_1_256       // T1CKPS = 00 prescaler 1:256
            & T1_SYNC_EXT_OFF   // Do not synch external clk input
            & T1_SOURCE_INT);   // TCS = 0 timer clock source set to internal

    config2 = (T1_INT_PRIOR_2   // Interrupt is priority 4
            & T1_INT_ON);       // Active interrupt;

*/
    /* TCY = TEMPS DE CYCLE : 1/((7372800*16)/4) = 33.9084 nanosec
       period must be < 65535
       tempo in seconds
       TCY in seconds
       T1_PS diviseur : 1 or 4 or 16 or 256
      
       period = Tempo ( TCY * T1_PS)
       57444  = 0.5   ( 0.000000034 * 256 )
     */
/*
    period = 3; // => we must multiply by (period + 1)

    // set to 0 the TIMER1, set the TIMER1 and define incrementation count
    // before interrupt
    OpenTimer1(config1, period);

    // Define the interruption priority and activate interruption
    ConfigIntTimer1(config2);

    // Enable the Interrupt
    mT1IntEnable(1);

    

    // enable interrupts
    INTEnableInterrupts();
*/

/* code to set up IO ports */ 
 
 /* The following instruction sets up Timer 1 to set the T1 Flag at a rate of 
 1000 Hz assumming that the PBCLK is running at 10 MHz. This instruction 
sets the PR1 value to 1250. */ 
 
 OpenTimer1((T1_ON | T1_SOURCE_INT | T1_PS_1_8), 1250); 
 
 /* The following enables the Timer 1 interrupt priority for 3 and the 
interrupt sub priority for 1.*/ 
 
 ConfigIntTimer1((T1_INT_ON | T1_INT_PRIOR_3 | T1_INT_SUB_PRIOR_1)); 
 
 /* code to for additional interrupt initializations */ 
 INTEnableSystemMultiVectoredInt(); // Required to enable all interrupts }


/**
 * @private
 * @interrupt
 * Function called by the timer.
 * Example Code inspired from : http://learn.digilentinc.com/Documents/216
 */
void __ISR(_TIMER_1_VECTOR, IPL3SOFT) Timer1Handler(void) {
    _internalUpdateTimerListValues();
    
    // clear the interrupt flag
    mT1ClearIntFlag();
}
