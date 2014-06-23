#include <stdlib.h>

#include "../../../common/commons.h"

#include <p30Fxxxx.h>

#include "../serialInputInterrupt.h"
#include "../serial.h"

#include "../../../common/io/buffer.h"

static Buffer* buffer1;
static Buffer* buffer2;

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

void initSerialInputBuffer(Buffer* buffer, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        buffer1 = buffer;
    } else if (serialPortIndex == SERIAL_PORT_2) {
        buffer2 = buffer;
    }
}
