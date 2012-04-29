#include <i2c.h>
#include <p30fxxxx.h>

#include "../../common/delay/delay30F.h"
#include "../../common/pwm/pwmPic.h"
#include "../../common/serial/serial.h"
#include "../../common/serial/serialUtils.h"
#include "../../common/delay/delay30F.h"

_FOSC(CSW_FSCM_OFF & XT_PLL16);  //7Mhz3728 * 16  = 117,9648 MHz /4 = 29,4912 MIPS maxi pour ce pic
_FWDT(WDT_OFF);					
//Watchdog OFF
//_FBORPOR(PBOR_OFF & BORV_27 & PWRT_16 & MCLR_EN);
_FGS(CODE_PROT_OFF);			//Codeprotect OFF

int main(void) {
	Buffer serialBuffer;
	setAndOpenSerialBuffer(&serialBuffer);
	delaymSec(100);
	putString("Mechanical Board OK");
	println();	

	// PWM
	initPwmForMotor (0);

	int i;
	int duty = 1000;

	ADPCFG = 0xFFFF;

	// pull down to 0
	TRISB = 0;
	PORTBbits.RB8 = 0;
	PORTBbits.RB9 = 0;
	PORTBbits.RB10 = 0;
	PORTBbits.RB11 = 0;
	PORTBbits.RB12 = 0;

	TRISB = 0xFFFF;

	TRISD = 0;
	PORTD = 0;
	TRISD = 0;
	PORTDbits.RD8 = 1;
	PORTDbits.RD9 = 1;

	while (1) {
		
		// Test for PWM
		for (i = 1; i <= 4; i++) {
			pwmMotor (i, duty);
			duty++;
			delaymSec(5);
			if (duty > 2000) {
				duty = 1000;
			}
		}
		// Test for I/0
		if (PORTBbits.RB8) {
			putString("RB8");
			println();
			delaymSec(100);
		}	
		if (PORTBbits.RB9) {
			putString("RB9");
			println();
			delaymSec(100);
		}
		if (PORTBbits.RB10) {
			putString("RB10");
			println();
			delaymSec(100);
		}
		if (PORTBbits.RB11) {
			putString("RB11");
			println();
			delaymSec(100);
		}
		if (PORTBbits.RB12) {
			putString("RB12");
			println();
			delaymSec(100);
		}
	}
	return 0;
}