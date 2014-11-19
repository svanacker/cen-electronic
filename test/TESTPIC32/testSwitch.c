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

// PORTD
#define SW0 BIT_5
#define SW1 BIT_6
#define SW2 BIT_7
#define SW3 BIT_8

//PORTB
#define SW4 BIT_6
#define SW5 BIT_7
#define SW6 BIT_9
#define SW7 BIT_10
#define SW8 BIT_11
#define SW9 BIT_12
#define SW10 BIT_13
#define SW11 BIT_15

// PORTC
#define SW12 BIT_13

// PORTG
#define SW13 BIT_2


// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************
const char mainMenu[] =
{
    "Welcome to PIC32 UART Peripheral Test Program!\r"
	"Do you want to continue ? (Yes/No)\r\n"
};

static const char* Str1="\rLecture Switch :\n";
static const char* Str2="0\n";
static const char* Str3="1\n";

static const char* Str4="   GO\n";
static const char* Str5="   NOGO\n";

// *****************************************************************************
// void SendDataBuffer(const UARTx, const char *buffer)
// Envoie sur le port serie la chaine de caractère
// @param	: UARTx : choix du port  
//					UART1,UART2,UART3,UART4,UART5,UART6
//			  buffer : chaine de caractère
// *****************************************************************************
void SendDataBuffer(const UARTx, const char *buffer)
{
    while(*buffer != '\n')
    {
        while(!UARTTransmitterIsReady(UARTx));
        UARTSendDataByte(UARTx, *buffer);
        buffer++; 
    }
    while(!UARTTransmissionHasCompleted(UARTx));
}


//******************************************************
// void OpenUart ( const UARTx,long BaudRate)
// Overture  d'un port serie
// @param 	: UARTx : choix du port 
//				UART1,UART2,UART3,UART4,UART5,UART6
//			  BaudeRate : Vitesse du port serie
//				1200,2400,4800,9600,19200,38400,57600,115200
//				
//******************************************************
void OpenUart ( const UARTx,long BaudRate)
{
	UARTConfigure(UARTx, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UARTx, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UARTx, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UARTx, GetPeripheralClock(), BAUDERATE);
    UARTEnable(UARTx, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
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


void testBitSwitch (int IOPORT , int BIT) {

	if  (PORTReadBits(IOPORT, BIT) == 0){
		if (UARTTransmitterIsReady(UARTTEST)){
        	SendDataBuffer(UARTTEST,Str2);
    	}
	}
	else {
		if (UARTTransmitterIsReady(UARTTEST)){
        	SendDataBuffer(UARTTEST,Str3);
  		}
	}
}

int main(void)
{

		OpenUart(UARTTEST,BAUDERATE);
		PORTSetPinsDigitalIn(IOPORT_D,SW0|SW1|SW2|SW3);  
		PORTSetPinsDigitalIn(IOPORT_B,SW4|SW5|SW6|SW7|SW8|SW9|SW10|SW11);  
		PORTSetPinsDigitalIn(IOPORT_C,SW12);  
		PORTSetPinsDigitalIn(IOPORT_G,SW13|BIT_3);

	while (1){

		SendDataBuffer(UARTTEST,Str1);

		testBitSwitch (IOPORT_G , SW13);
		testBitSwitch (IOPORT_C , SW12);
		testBitSwitch (IOPORT_B , SW11);
		testBitSwitch (IOPORT_B , SW10);
		testBitSwitch (IOPORT_B , SW9);
		testBitSwitch (IOPORT_B , SW8);
		testBitSwitch (IOPORT_B , SW7);
		testBitSwitch (IOPORT_B , SW6);
		testBitSwitch (IOPORT_B , SW5);
		testBitSwitch (IOPORT_B , SW4);
		testBitSwitch (IOPORT_D , SW3);
		testBitSwitch (IOPORT_D , SW2);
		testBitSwitch (IOPORT_D , SW1);
		testBitSwitch (IOPORT_D , SW0);


	if  (PORTReadBits(IOPORT_G, BIT_3) == 0){
		if (UARTTransmitterIsReady(UARTTEST)){
        	SendDataBuffer(UARTTEST,Str4);
    	}
	}
	else {
		if (UARTTransmitterIsReady(UARTTEST)){
        	SendDataBuffer(UARTTEST,Str5);
  		}
	}

		delaymSec(400);
	}
	return (0);
}
