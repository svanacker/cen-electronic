#include "../../../common/commons.h"

#include <stdlib.h>
#include <plib.h>

#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../serialInputInterrupt.h"
#include "../serial.h"
#include "serial32.h"

static Buffer* serialInputBuffer1;
static Buffer* serialInputBuffer2;
static Buffer* serialInputBuffer3;
static Buffer* serialInputBuffer4;
static Buffer* serialInputBuffer5;
static Buffer* serialInputBuffer6;

static int serialInterruptCounter1;
static int serialInterruptCounter2;
static int serialInterruptCounter3;
static int serialInterruptCounter4;
static int serialInterruptCounter5;
static int serialInterruptCounter6;


void handleUartInterrupt(UART_MODULE uart, Buffer* buffer) {
    // Is this an RX interrupt?
    if (INTGetFlag(INT_SOURCE_UART_RX(uart))) {
        char c = UARTGetDataByte(uart);
        bufferWriteChar(buffer, c);
        // Clear the RX interrupt Flag
        INTClearFlag(INT_SOURCE_UART_RX(uart));
    }
    // We don't care about TX interrupt
    if ( INTGetFlag(INT_SOURCE_UART_TX(uart)) ) {
        INTClearFlag(INT_SOURCE_UART_TX(uart));
    }
}

void printSerialInputBuffers(OutputStream* outputStream) {
    appendString(outputStream, "SERIAL INPUT BUFFER 1:");
    appendStringAndDec(outputStream, "\nCounter1=", serialInterruptCounter1);
    printDebugBuffer(outputStream, serialInputBuffer1);

    appendString(outputStream, "SERIAL INPUT BUFFER 2:");
    appendStringAndDec(outputStream, "\nCounter2=", serialInterruptCounter2);
    printDebugBuffer(outputStream, serialInputBuffer2);

    appendString(outputStream, "SERIAL INPUT BUFFER 3:");
    appendStringAndDec(outputStream, "\nCounter3=", serialInterruptCounter3);
    printDebugBuffer(outputStream, serialInputBuffer3);

    appendString(outputStream, "SERIAL INPUT BUFFER 4:");
    appendStringAndDec(outputStream, "\nCounter4=", serialInterruptCounter4);
    printDebugBuffer(outputStream, serialInputBuffer4);

    appendString(outputStream, "SERIAL INPUT BUFFER 5:");
    appendStringAndDec(outputStream, "\nCounter5=", serialInterruptCounter5);
    printDebugBuffer(outputStream, serialInputBuffer5);

    appendString(outputStream, "SERIAL INPUT BUFFER 6:");
    appendStringAndDec(outputStream, "\nCounter6=", serialInterruptCounter6);
    printDebugBuffer(outputStream, serialInputBuffer6);
}

/**
 * Interrupt on Serial 1
 */
void __ISR(_UART_1_VECTOR, IPL2SOFT) IntUart1Handler(void) {
    handleUartInterrupt(UART1, serialInputBuffer1);
    serialInterruptCounter1++;
}

/**
 * Interrupt on Serial 2
 */
void __ISR(_UART_2_VECTOR, IPL2SOFT) IntUart2Handler(void) {
    handleUartInterrupt(UART2, serialInputBuffer2);
    serialInterruptCounter2++;
}

/**
 * Interrupt on Serial 3
 */
void __ISR(_UART_3_VECTOR, IPL2SOFT) IntUart3Handler(void) {
    handleUartInterrupt(UART3, serialInputBuffer3);
    serialInterruptCounter3++;
}

/**
 * Interrupt on Serial 4
 */
void __ISR(_UART_4_VECTOR, IPL2SOFT) IntUart4Handler(void) {
    handleUartInterrupt(UART4, serialInputBuffer4);
    serialInterruptCounter4++;
}

/**
 * Interrupt on Serial 5
 */
void __ISR(_UART_5_VECTOR, IPL2SOFT) IntUart5Handler(void) {
    handleUartInterrupt(UART5, serialInputBuffer5);
    serialInterruptCounter5++;
}

/**
 * Interrupt on Serial 6
 */
void __ISR(_UART_6_VECTOR, IPL2SOFT) IntUart6Handler(void) {
    handleUartInterrupt(UART6, serialInputBuffer6);
    serialInterruptCounter6++;
}

void initSerialInputBuffer(Buffer* buffer, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        serialInputBuffer1 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_2) {
        serialInputBuffer2 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_3) {
        serialInputBuffer3 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_4) {
        serialInputBuffer4 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_5) {
        serialInputBuffer5 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_6) {
        serialInputBuffer6 = buffer;
    }
}
