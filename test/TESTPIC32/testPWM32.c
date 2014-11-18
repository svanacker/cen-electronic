#include <p32xxxx.h>
#include <string.h>
#include <plib.h>



// definition des bits de configuration.
// Quartz externe, PLL x 10
// Watchdog OFF

#pragma config FNOSC = PRIPLL, POSCMOD = HS, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPBDIV = DIV_2, FPLLODIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN=OFF




int main(void)
{
	/* Open Timer2 with Period register value */
	OpenTimer2(T2_ON|T2_PS_1_64, 0x30D4);

	OpenOC1( OC_ON | OC_TIMER_MODE32 | OC_TIMER2_SRC | OC_CONTINUE_PULSE | OC_LOW_HIGH , 0x30D4, 0x3A9 );
	OpenOC2( OC_ON | OC_TIMER_MODE32 | OC_TIMER2_SRC | OC_CONTINUE_PULSE | OC_LOW_HIGH , 0x30D4, 0x3a9 );
	OpenOC5( OC_ON | OC_TIMER_MODE32 | OC_TIMER2_SRC | OC_CONTINUE_PULSE | OC_LOW_HIGH , 0x30D4, 0x3a9 );

while (1)
{
}
	return (0);
}
