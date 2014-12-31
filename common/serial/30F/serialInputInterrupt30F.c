#include <stdlib.h>

#include <p30Fxxxx.h>

#include "../serialInputInterrupt.h"
#include "../serial.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

static Buffer* serialInputBuffer1;
static Buffer* serialInputBuffer2;

static int serialInterruptCounter1;
static int serialInterruptCounter2;

/**
 * Interrupt on Serial 1
 */
void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void) {
    char c;
    serialInterruptCounter1++;
    if (serialInputBuffer1 != NULL) {
        while (U1STAbits.URXDA) {
            c = U1RXREG;
            bufferWriteChar(serialInputBuffer1, c);
        }
    }

    // clear interruption flag
    IFS0bits.U1RXIF = 0;
}

/**
 * Interrupt on Serial 2
 */
void __attribute__((__interrupt__, auto_psv)) _U2RXInterrupt(void) {
    char c;
    serialInterruptCounter2++;
    if (serialInputBuffer2 != NULL) {
        while (U2STAbits.URXDA) {
            c = U2RXREG;
            bufferWriteChar(serialInputBuffer2, c);
        }
    }

    // clear interruption flag
    IFS1bits.U2RXIF = 0;
}

void initSerialInputBuffer(Buffer* buffer, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        serialInputBuffer1 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_2) {
        serialInputBuffer2 = buffer;
    }
}

void printSerialInputBuffers(OutputStream* outputStream) {
    if (serialInputBuffer1 != NULL) {
        appendString(outputStream, "SERIAL INPUT BUFFER 1:");
        appendStringAndDec(outputStream, "\nCounter1=", serialInterruptCounter1);
        printDebugBuffer(outputStream, serialInputBuffer1);
    }
    if (serialInputBuffer2 != NULL) {
        appendString(outputStream, "SERIAL INPUT BUFFER 2:");
        appendStringAndDec(outputStream, "\nCounter2=", serialInterruptCounter2);
        printDebugBuffer(outputStream, serialInputBuffer2);
    }
}
