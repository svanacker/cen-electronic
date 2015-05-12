#include "../../../../common/commons.h"

#include <i2c.h>
#include <stdlib.h>
#include <p30Fxxxx.h>

#include "../i2cSlave.h"
#include "../i2cSlaveSetup.h"
#include "../../i2cConstants.h"
#include "../../i2cDebug.h"

#include "../../../../common/delay/cenDelay.h"

#include "../../../../common/io/inputStream.h"
#include "../../../../common/io/outputStream.h"
#include "../../../../common/io/buffer.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/ioUtils.h"

#include "../../../../common/log/logger.h"

/**
 * Function Name: SI2C1Interrupt
 * Description : This is the ISR for I2C1 Slave interrupt.
 */
void __attribute__((__interrupt__)) __attribute__((no_auto_psv)) _SI2CInterrupt(void) {
    // last byte received is address and not data
    char isData = I2CSTATbits.D_A;
    char read = I2CSTATbits.R_W;

    StreamLink* i2cStreamLink = getI2cStreamLink();
    // We must read first and not only if we read or write
    
    // Master want to READ
    if (read) {
        SlaveReadI2C();
        // The buffer which must be send to the master
        Buffer* i2cSlaveOutputBuffer = i2cStreamLink->outputBuffer;
        // Get an inputStream to read the buffer to send to the master
        InputStream* i2cInputStream = getInputStream(i2cSlaveOutputBuffer);
        // There is available data
        if (i2cInputStream->availableData(i2cInputStream)) {
            char c = i2cInputStream->readChar(i2cInputStream);
            // for debug support
            appendI2cDebugInputChar(c);
            // we send it to the master
            SlaveWriteI2C(c);
        } else {
            // There is no data, we send it to the master
            // We send 0 (end of buffer)
            SlaveWriteI2C(I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
        }
        while (I2CSTATbits.TBF) {
        
        }
    }
    // Master want to WRITE (InputStream)
    else {
        if (!isData) {
            SlaveReadI2C();
            //clear I2C1 Slave interrupt flag
            IFS0bits.SI2CIF = 0;
            return;
        }
        int data = SlaveReadI2C();
        if (data != INCORRECT_DATA && data != I2C_SLAVE_FAKE_WRITE) {
            Buffer* i2cSlaveInputBuffer = i2cStreamLink->inputBuffer;
            OutputStream* outputStream = getOutputStream(i2cSlaveInputBuffer);
            // Read data from the Master
            append(outputStream, data);

            appendI2cDebugInputChar(data);
        }
        I2CCONbits.SCLREL = 1;
    }

    //clear I2C1 Slave interrupt flag
    IFS0bits.SI2CIF = 0;
}
