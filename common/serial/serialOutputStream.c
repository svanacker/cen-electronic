#include <stdlib.h>
#include <p30fxxxx.h>

#include "serialOutputStream.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

static Buffer* buffer1;
static Buffer* buffer2;

// ----------------------------------- OUTPUT STREAM INTERFACE ------------------------------------

void flushSerial(OutputStream* outputStream) {
    // don't do anything
}

// -> SERIAL PORT 1

void openOutputStreamSerial1(OutputStream* outputStream, int param1) {
    openSerialAtDefaultSpeed(SERIAL_PORT_1);
}

void closeOutputStreamSerial1(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_1);
}

void writeChar1(OutputStream* outputStream, char c) {
    putc(SERIAL_PORT_1, c);
}

void initSerialOutputStream1(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial1;
    outputStream->closeOutputStream = closeOutputStreamSerial1;
    outputStream->writeChar = writeChar1;
    outputStream->flush = flushSerial;
}

// -> SERIAL PORT 2

void openOutputStreamSerial2(OutputStream* outputStream, int param1) {
    openSerialAtDefaultSpeed(SERIAL_PORT_2);
}

void closeOutputStreamSerial2(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_2);
}

void writeChar2(OutputStream* outputStream, char c) {
    putc(SERIAL_PORT_2, c);
}

void initSerialOutputStream2(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial2;
    outputStream->closeOutputStream = closeOutputStreamSerial2;
    outputStream->writeChar = writeChar2;
    outputStream->flush = flushSerial;
}

/**
 * Interrupt on Serial 1
 */
void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void) {
    char c;
    if (buffer1 != NULL) {
        while (U1STAbits.URXDA) {
            c = U1RXREG;
            bufferWriteChar(buffer1, c);
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

    if (buffer2 != NULL) {
        while (U2STAbits.URXDA) {
            c = U2RXREG;
            bufferWriteChar(buffer2, c);
        }
    }

    // clear interruption flag
    IFS1bits.U2RXIF = 0;
}




// PUBLIC INTERFACE

void initSerialOutputStream(OutputStream* outputStream, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        initSerialOutputStream1(outputStream);
    } else if (serialPortIndex == SERIAL_PORT_2) {
        initSerialOutputStream2(outputStream);
    }
}

void initSerialInputBuffer(Buffer* buffer, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        buffer1 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_2) {
        buffer2 = buffer;
    }
}
