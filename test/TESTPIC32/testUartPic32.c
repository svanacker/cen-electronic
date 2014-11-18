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

// Définition des 6 UART
//#define UART1 UART1A
//#define UART2 UART3A
//#define UART3 UART2A
//#define UART4 UART1B
//#define UART5 UART3B
//#define UART6 UART2B
		
// DEFINITION DU PORT A TESTER
#define UARTTEST UART2 

// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************
const char mainMenu[] =
{
    "Welcome to PIC32 UART Peripheral Test Program!\r"
	"Do you want to continue ? ( (y)es / (n)o )\r\n"
};

static const char* myHelloStr1="PIC32...on UART1\r\n";
static const char* myHelloStr2="PIC32...on UART2\r\n";
static const char* myHelloStr3="PIC32...on UART3\r\n";
static const char* myHelloStr4="PIC32...on UART4\r\n";
static const char* myHelloStr5="PIC32...on UART5\r\n";
static const char* myHelloStr6="PIC32...on UART6\r\n";
static const char* goodbye="\r\rTest UART terminé\r\n";

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


// *****************************************************************************
// UINT32 GetMenuChoice(void)
// *****************************************************************************
UINT32 GetMenuChoice(void)
{
    UINT8  menu_item;

    while(!UARTReceivedDataIsAvailable(UARTTEST));
    menu_item = UARTGetDataByte(UARTTEST);


    return (UINT32)menu_item;
}
int main(void)
{
 	UINT32  menu_choice;
	
	menu_choice = 'y';
		OpenUart(UART1,BAUDERATE);
		OpenUart(UART2,BAUDERATE);
//		OpenUart(UART3,BAUDERATE);
//		OpenUart(UART4,BAUDERATE);
		OpenUart(UART5,BAUDERATE);
		OpenUart(UART6,BAUDERATE);

//IMPORTANT POUR ACTIVER LE RX UART5. INFO TROUVEE SUR LE NET
		PORTSetPinsDigitalIn(IOPORT_B,BIT_8);  

	while (1)
	{

		if (menu_choice=='n')
		{

			SendDataBuffer(UARTTEST,goodbye);
			
			return(0);
		}
		if (menu_choice=='y')
		{

		menu_choice = 'n';
		

		SendDataBuffer(UART1,myHelloStr1);
	    SendDataBuffer(UART1,mainMenu);		

		SendDataBuffer(UART2,myHelloStr2);
	    SendDataBuffer(UART2,mainMenu);		


//		SendDataBuffer(UART3,myHelloStr3);
//		SendDataBuffer(UART3,mainMenu);


//		SendDataBuffer(UART4,myHelloStr4);
//		SendDataBuffer(UART4,mainMenu);


		SendDataBuffer(UART5,myHelloStr5);
	    SendDataBuffer(UART5,mainMenu);


		SendDataBuffer(UART6,myHelloStr6);
	    SendDataBuffer(UART6,mainMenu);





		menu_choice = GetMenuChoice();
		}
	}
	return (0);
}
