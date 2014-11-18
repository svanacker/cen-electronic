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

// Définition de la vitesse du port serie
#define BAUDERATE 115200

// DEFINITION DU PORT A TESTER
#define UARTTEST UART1 

// Définition LCD
#define RW BIT_3
#define RS BIT_1
#define E  BIT_0
#define D0 BIT_0
#define D1 BIT_1
#define D2 BIT_2
#define D3 BIT_3
#define D4 BIT_4
#define D5 BIT_5
#define D6 BIT_6
#define D7 BIT_7


// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************


static const char* myHelloStr1="   PIC32...on LCD   Cybernetique en Nord        With              By Jerome    \n";




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

void w_com (char com){
	PORTClearBits(IOPORT_F,RS|RW); 
	PORTSetBits(IOPORT_F,E); 
	PORTE = com;
	delay100us(10);
	PORTClearBits(IOPORT_F,E); 
	PORTSetBits(IOPORT_F,E);
}

void w_data (char data){
	PORTClearBits(IOPORT_F,RW); 
	PORTSetBits(IOPORT_F,RS); 
	PORTE = data;
	delay100us(10);
	PORTClearBits(IOPORT_F,E); 
	PORTSetBits(IOPORT_F,E);
}


void w_text(const char *buffer)
{
    while(*buffer != '\n')
    {
        w_data( *buffer);
        buffer++; 
    }
  
}


int main(void)
{ 	
	PORTSetPinsDigitalOut(IOPORT_F,E|RS|RW);
	PORTSetPinsDigitalOut(IOPORT_E,D0|D1|D2|D3|D4|D5|D6|D7);


	PORTClearBits(IOPORT_F, E|RS|RW);



	delaymSec(1000);

	w_com(0b00111000);
	delaymSec(100);
	w_com(0b00111000);
	delaymSec(100);
	w_com(0b00111000);
	delaymSec(100);

	w_com(0b00001110);
	delaymSec(100);
	w_com(0b00000110);
	delaymSec(100);


	w_com(0b00000110);
	w_text(myHelloStr1);
	delaymSec(5000);

	return (0);
}
