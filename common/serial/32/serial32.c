#include <plib.h>

#include "../../../common/commons.h"

#include "../serial.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/setup/32/clockConstants32.h"

// Map between SERIAL_PORT_X and UARTX
static UART_MODULE     UART_MODULES[] = { UART1, UART2, UART3, UART4, UART5, UART6 };

UART_MODULE getUartModule(unsigned char serialPortIndex) {
    return UART_MODULES[serialPortIndex - 1];
}

void openSerial(unsigned char serialPortIndex, unsigned long baudRate) {
    // important to activate the RX for UART5. Information found on the net
    if (serialPortIndex == SERIAL_PORT_5) {
        PORTSetPinsDigitalIn(IOPORT_B, BIT_8);
    }
    UART_MODULE uart = getUartModule(serialPortIndex);
    UARTConfigure(uart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(uart, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(uart, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(uart, GetPeripheralClock(), baudRate);
    UARTEnable(uart, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    INTEnable(INT_SOURCE_UART_RX(uart), INT_ENABLED);
    INTSetVectorPriority(INT_VECTOR_UART(uart), INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_VECTOR_UART(uart), INT_SUB_PRIORITY_LEVEL_0);

    // TODO : Move this code to Global Setup !

    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // enable interrupts
    INTEnableInterrupts();
}

void openSerialAtDefaultSpeed(unsigned char serialPortIndex) {
    openSerial(serialPortIndex, DEFAULT_SERIAL_SPEED);
}

void closeSerial(unsigned char serialPortIndex) {
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

void simulateSerialDelay() {
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
        simulateSerialDelay();
    #endif

    UART_MODULE uart = getUartModule(serialPortIndex);

    while (!UARTTransmitterIsReady(uart));
    UARTSendDataByte(uart, c);
    while (!UARTTransmissionHasCompleted(uart));
}

