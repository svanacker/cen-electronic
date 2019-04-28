#include "../../../common/commons.h"

#include <stdlib.h>
#define _SUPPRESS_PLIB_WARNING
#include <plib.h>

#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../serialInputInterrupt.h"
#include "../serial.h"
#include "serial32.h"

static Buffer* serialInputBuffer1;
static Buffer* serialInputBuffer2;
static Buffer* serialInputBuffer3;
static Buffer* serialInputBuffer4;
static Buffer* serialInputBuffer5;
static Buffer* serialInputBuffer6;

void handleUartInterrupt(UART_MODULE uart, Buffer* buffer) {
    // Is this an RX interrupt?
    if (INTGetFlag(INT_SOURCE_UART_RX(uart))) {
        if (UARTReceivedDataIsAvailable(uart)) {
            unsigned char c = UARTGetDataByte(uart);
            // BUG2018, BUG2019 (255 / 254 value) when Motor Power is too strong
            if (c != 'ÿ' && c != 'þ') {
                bufferWriteChar(buffer, c);
            }
            // Clear the RX interrupt Flag
            INTClearFlag(INT_SOURCE_UART_RX(uart));
        }
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
    handleUartInterrupt(UART1, serialInputBuffer1);
}

/**
 * Interrupt on Serial 2
 */
void __ISR(_UART_2_VECTOR, IPL2SOFT) IntUart2Handler(void) {
    handleUartInterrupt(UART2, serialInputBuffer2);
}

/**
 * Interrupt on Serial 3
 */
void __ISR(_UART_3_VECTOR, IPL2SOFT) IntUart3Handler(void) {
    handleUartInterrupt(UART3, serialInputBuffer3);
}

/**
 * Interrupt on Serial 4
 */
void __ISR(_UART_4_VECTOR, IPL2SOFT) IntUart4Handler(void) {
    handleUartInterrupt(UART4, serialInputBuffer4);
}

/**
 * Interrupt on Serial 5
 */
void __ISR(_UART_5_VECTOR, IPL2SOFT) IntUart5Handler(void) {
    handleUartInterrupt(UART5, serialInputBuffer5);
}

/**
 * Interrupt on Serial 6
 */
void __ISR(_UART_6_VECTOR, IPL2SOFT) IntUart6Handler(void) {
    handleUartInterrupt(UART6, serialInputBuffer6);
}

void initSerialInputBuffer(Buffer* buffer, enum SerialPort serialPort) {
    if (serialPort == SERIAL_PORT_1) {
        serialInputBuffer1 = buffer;
    } else if (serialPort == SERIAL_PORT_2) {
        serialInputBuffer2 = buffer;
    } else if (serialPort == SERIAL_PORT_3) {
        serialInputBuffer3 = buffer;
    } else if (serialPort == SERIAL_PORT_4) {
        serialInputBuffer4 = buffer;
    } else if (serialPort == SERIAL_PORT_5) {
        serialInputBuffer5 = buffer;
    } else if (serialPort == SERIAL_PORT_6) {
        serialInputBuffer6 = buffer;
    }
}
