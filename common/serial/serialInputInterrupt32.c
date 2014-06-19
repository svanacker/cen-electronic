#include <stdlib.h>

#include "../../common/commons.h"

#include <plib.h>

#include "serialInputInterrupt.h"
#include "serial.h"
#include "serial32.h"

#include "../../common/io/buffer.h"

static Buffer* buffer1;
static Buffer* buffer2;
static Buffer* buffer3;
static Buffer* buffer4;
static Buffer* buffer5;
static Buffer* buffer6;

void putCharacter(UART_MODULE uartModule, const char c) {
  while (!UARTTransmitterIsReady(uartModule));
  UARTSendDataByte(uartModule, c);
  while (!UARTTransmissionHasCompleted(uartModule));
}

inline void handleUartInterrupt(UART_MODULE uart, Buffer* buffer) {
    // Is this an RX interrupt?
    if (INTGetFlag(INT_SOURCE_UART_RX(uart))) {
        char c = UARTGetDataByte(uart);
        bufferWriteChar(buffer, c);
        // putCharacter(uart, c);
        // Clear the RX interrupt Flag
        INTClearFlag(INT_SOURCE_UART_RX(uart));
    }
    // We don't care about TX interrupt
    if ( INTGetFlag(INT_SOURCE_UART_TX(uart)) ) {
        INTClearFlag(INT_SOURCE_UART_TX(uart));
    }
}

/**
 * Interrupt on Serial 1
 */
void __ISR(_UART_1_VECTOR, IPL2SOFT) IntUart1Handler(void) {
    handleUartInterrupt(UART1, buffer1);
}

/**
 * Interrupt on Serial 2
 */
void __ISR(_UART_2_VECTOR, IPL2SOFT) IntUart2Handler(void) {
    handleUartInterrupt(UART2, buffer2);
}

/**
 * Interrupt on Serial 3
 */
void __ISR(_UART_3_VECTOR, IPL2SOFT) IntUart3Handler(void) {
    handleUartInterrupt(UART3, buffer3);
}

/**
 * Interrupt on Serial 4
 */
void __ISR(_UART_4_VECTOR, IPL2SOFT) IntUart4Handler(void) {
    handleUartInterrupt(UART4, buffer4);
}

/**
 * Interrupt on Serial 5
 */
void __ISR(_UART_5_VECTOR, IPL2SOFT) IntUart5Handler(void) {
    handleUartInterrupt(UART5, buffer5);
}

/**
 * Interrupt on Serial 6
 */
void __ISR(_UART_6_VECTOR, IPL2SOFT) IntUart6Handler(void) {
    handleUartInterrupt(UART6, buffer6);
}

void initSerialInputBuffer(Buffer* buffer, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        buffer1 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_2) {
        buffer2 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_3) {
        buffer3 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_4) {
        buffer4 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_5) {
        buffer5 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_6) {
        buffer6 = buffer;
    }
}
