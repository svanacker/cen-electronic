#include <p32xxxx.h>
#include <string.h>
#include <plib.h>

// definition des bits de configuration.
// Quartz externe, PLL x 10
// Watchdog OFF
#pragma config FNOSC = PRIPLL, POSCMOD = XT, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPBDIV = DIV_2, FPLLODIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN=OFF

// calcul de la fréquence du bus
#define	GetSystemClock() 			(80000000ul)
#define	GetPeripheralClock()		(GetSystemClock()/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(GetSystemClock())


void delayUs(void) {
       
}

void delay100us(char uSecond) {
    unsigned int i;
    while (uSecond != 0) {
        i = 137;
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --uSecond;
    }
}

void delaymSec(unsigned int mSecond) {
    unsigned int i;
    while (mSecond != 0) {
        i = 1590;
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --mSecond;
    }
}

int main(void)
	{

	PORTSetPinsDigitalOut(IOPORT_F,BIT_3);
	PORTClearBits(IOPORT_F, BIT_3);


	PORTSetPinsDigitalOut(IOPORT_C,BIT_14); 
	PORTClearBits(IOPORT_C, BIT_14);

	PORTSetPinsDigitalOut(IOPORT_D,BIT_11);
	PORTClearBits(IOPORT_D, BIT_11);


	while (1)
		{
		delaymSec(1000);
	
		PORTToggleBits(IOPORT_C, BIT_14);

		delaymSec(1000);

		PORTToggleBits(IOPORT_D, BIT_11);

		delaymSec(1000);

		PORTToggleBits(IOPORT_F, BIT_3);
		}
	return (0);
}
