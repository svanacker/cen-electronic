#include "../../../../common/commons.h"

#include <i2c.h>
#include <stdlib.h>
#include <plib.h>

#include "../../i2cConstants.h"
#include "../../i2cDebug.h"
#include "../i2cSlave.h"
#include "../i2cSlaveSetup.h"

#include "../../../../common/delay/cenDelay.h"

#include "../../../../common/io/inputStream.h"
#include "../../../../common/io/outputStream.h"
#include "../../../../common/io/buffer.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/ioUtils.h"

#include "../../../../common/log/logger.h"

/** The I2C link used by the interrupt routine. */
static StreamLink* i2cStreamLink;

void setI2cStreamLink(StreamLink* streamLink) {
    i2cStreamLink = streamLink;
}

StreamLink* getI2cStreamLink() {
    return i2cStreamLink;
}

/**
 * Function Name: SI2C1Interrupt
 * Description : This is the ISR for I2C1 Slave interrupt.
 */
void __ISR(_I2C_1_VECTOR, ipl3) _SlaveI2CHandler(void)
{
    // last byte received is address and not data
    char isData = I2C1STATbits.D_A;
    char read = I2C1STATbits.R_W;

    // We must read first and not only if we read or write

    // Master want to READ
    if (read) {
        SlaveReadI2C1();
        // The buffer which must be send to the master
        Buffer* i2cSlaveOutputBuffer = i2cStreamLink->outputBuffer;
        // Get an inputStream to read the buffer to send to the master
        InputStream* i2cInputStream = getInputStream(i2cSlaveOutputBuffer);
        // For debug
        Buffer* debugI2cOutputBuffer = getDebugI2cOutputBuffer();
        // There is available data
        if (i2cInputStream->availableData(i2cInputStream)) {
            char c = i2cInputStream->readChar(i2cInputStream);
            // for debug support
            if (debugI2cOutputBuffer != NULL) {
                bufferWriteChar(debugI2cOutputBuffer, c);
            }
            // we send it to the master
            SlaveWriteI2C1(c);
        } else {
            // There is no data, we send it to the master
            // We send 0 (end of buffer)
            if (debugI2cOutputBuffer != NULL) {
                bufferWriteChar(debugI2cOutputBuffer, I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
            }
            SlaveWriteI2C1(I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
        }
        while (I2C1STATbits.TBF);
    }        // Master want to WRITE (InputStream)
    else {
        if (!isData) {
            SlaveReadI2C1();
            //clear I2C1 Slave interrupt flag
            mI2C1SClearIntFlag();
            return;
        }
        int data = SlaveReadI2C1();
        if (data != INCORRECT_DATA && data != I2C_SLAVE_FAKE_WRITE) {
            Buffer* i2cSlaveInputBuffer = i2cStreamLink->inputBuffer;
            OutputStream* outputStream = getOutputStream(i2cSlaveInputBuffer);
            // Read data from the Master
            append(outputStream, data);
            Buffer* debugI2cInputBuffer = getDebugI2cInputBuffer();
            if (debugI2cInputBuffer != NULL) {
                bufferWriteChar(debugI2cInputBuffer, data);
            }
        }

        I2C1CONbits.SCLREL = 1;
    }

    // clear I2C1 Slave interrupt flag
    IFS0bits.I2C1MIF = 0;
}

