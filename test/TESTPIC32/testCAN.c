#include <p32xxxx.h>
#include <string.h>
#include <plib.h>

// definition des bits de configuration.
// Quartz externe, PLL x 10
// Watchdog OFF
#pragma config FNOSC = PRIPLL, POSCMOD = HS, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPBDIV = DIV_2, FPLLODIV = DIV_1
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
	PORTSetPinsDigitalOut(IOPORT_C,BIT_14); 
	PORTSetPinsDigitalOut(IOPORT_D,BIT_11);
	PORTSetPinsDigitalIn(IOPORT_B,BIT_2|BIT_3|BIT_4|BIT_5);
while (1)
{

	if ((PORTBbits.RB2)>0)  
	{
		PORTSetBits(IOPORT_C, BIT_14);
		PORTClearBits(IOPORT_D, BIT_11);
		PORTClearBits(IOPORT_F,BIT_3);
	}
	else {
		PORTClearBits(IOPORT_C, BIT_14);
		PORTClearBits(IOPORT_D, BIT_11);
		PORTClearBits(IOPORT_F,BIT_3);
	}

	if ((PORTBbits.RB3)>0)  
	{
		PORTClearBits(IOPORT_C, BIT_14);
		PORTSetBits(IOPORT_D, BIT_11);
		PORTClearBits(IOPORT_F,BIT_3);
	}
	else {
		PORTClearBits(IOPORT_C, BIT_14);
		PORTClearBits(IOPORT_D, BIT_11);
		PORTClearBits(IOPORT_F,BIT_3);
	}

	if ((PORTBbits.RB4)>0)  
	{
		PORTClearBits(IOPORT_C, BIT_14);
		PORTClearBits(IOPORT_D, BIT_11);
		PORTSetBits(IOPORT_F,BIT_3);
	}
	else {
		PORTClearBits(IOPORT_C, BIT_14);
		PORTClearBits(IOPORT_D, BIT_11);
		PORTClearBits(IOPORT_F,BIT_3);
	}

	if ((PORTBbits.RB5)>0)  
	{
		PORTSetBits(IOPORT_C, BIT_14);
		PORTSetBits(IOPORT_D, BIT_11);
		PORTSetBits(IOPORT_F,BIT_3);
	}
	else {
		PORTClearBits(IOPORT_C, BIT_14);
		PORTClearBits(IOPORT_D, BIT_11);
		PORTClearBits(IOPORT_F,BIT_3);
	}

	}	
	return (0);

}
