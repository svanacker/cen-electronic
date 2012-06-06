#include "../../common/commons.h"

#include <uart.h>

#include "serial.h"

#include "../../common/setup/clockConstants32.h"

// Map between SERIAL_PORT_X and UARTX
static UART_MODULE 	UART_MODULES[] = { UART1, UART2, UART3, UART4, UART5, UART6 };

UART_MODULE getUartModule(unsigned char serialPortIndex) {
	return UART_MODULES[serialPortIndex - 1];
}

void openSerial(unsigned char serialPortIndex, unsigned long baudRate) {
	UART_MODULE uart = getUartModule(serialPortIndex);
	UARTConfigure(uart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(uart, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(uart, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(uart, GetPeripheralClock(), baudRate);
    UARTEnable(uart, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
}

void openSerialAtDefaultSpeed(unsigned char serialPortIndex) {
    openSerial(serialPortIndex, DEFAULT_SERIAL_SPEED);
}

void closeSerial(unsigned char serialPortIndex) {
	// TODO : Test it ! 
	UART_MODULE uart = getUartModule(serialPortIndex);
	UARTEnable(uart, UART_DISABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
}

int kbhit(unsigned char serialPortIndex) {
	UART_MODULE uart = getUartModule(serialPortIndex);
	return UARTReceivedDataIsAvailable(uart);
}

char serialGetc(unsigned char serialPortIndex) {
	UART_MODULE uart = getUartModule(serialPortIndex);
	return UARTGetDataByte(uart);
}

#ifdef MPLAB_SIMULATION

void simulateDelay() {
    int i = 1000;
    while (i > 0) {
        Nop();
        Nop();
        --i;
    }
}
#endif

void serialPutc(unsigned char serialPortIndex, char c) {
	#ifdef MPLAB_SIMULATION
	        simulateDelay();
	#endif
	UART_MODULE uart = getUartModule(serialPortIndex);

	while (!UARTTransmitterIsReady(uart));
	UARTSendDataByte(uart, c);
	while (!UARTTransmissionHasCompleted(uart));

}

