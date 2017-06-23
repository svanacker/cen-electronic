#include "../../../../common/commons.h"
#include <stdlib.h>

#define _SUPPRESS_PLIB_WARNING
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
#include "../../../../common/io/streamLink.h"
#include "../../../../common/log/logger.h"

/**
 * Function Name: SI2C1Interrupt
 * Description : This is the ISR for I2C1 Slave interrupt.
 */
void __ISR(_I2C_1_VECTOR, ipl3) _SlaveI2CHandler(void)
{
    // TODO : Find the right i2cBusConnection
    I2cBusConnection* i2cBusConnection = NULL;

    // last byte received is address and not data
    char isData = I2C1STATbits.D_A;
    char read = I2C1STATbits.R_W;
    char isStart = I2C1STATbits.S;
    char isSclRelease = I2C1CONbits.SCLREL;
    char readBufferFull = I2C1STATbits.RBF;

    // check for MASTER and Bus events and respond accordingly
    if (IFS0bits.I2C1MIF == 1) {
        mI2C1MClearIntFlag();
        return;
    }
    if (IFS0bits.I2C1BIF == 1) {
        mI2C1BClearIntFlag();
        return;
    }
    StreamLink* i2cStreamLink = getI2cStreamLink();

    // handle the incoming message

    // Master want to write and send the address
    if (isStart && !read && !isData && readBufferFull) {
        // R/W bit = 0 --> indicates data transfer is input to slave
        // D/A bit = 0 --> indicates last byte was address

        // reset any state variables needed by a message sequence
        // perform a dummy read of the address
        portableSlaveReadI2C(i2cBusConnection);
        
        // release the clock to restart I2C
        portableSlaveClockRelease(i2cBusConnection);
    }
    // Master WRITE (InputStream)
    else if (isStart && !read && isData && readBufferFull) {
        // R/W bit = 0 --> indicates data transfer is input to slave
        // D/A bit = 1 --> indicates last byte was data
        int data = portableSlaveReadI2C(i2cBusConnection);
        Buffer* i2cSlaveInputBuffer = i2cStreamLink->inputBuffer;
        OutputStream* outputStream = getOutputStream(i2cSlaveInputBuffer);
        // Read data from the Master
        append(outputStream, data);
        // for debug support
        appendI2cDebugInputChar(data);
  
        // release the clock to restart I2C
        portableSlaveClockRelease(i2cBusConnection);
    }
    // Master send the address and want to read
    else if (isStart && read && !isData) {
        // R/W bit = 1 --> indicates data transfer is output from slave
        // D/A bit = 0 --> indicates last byte was address
        portableSlaveReadI2C(i2cBusConnection);
        
        Buffer* i2cSlaveOutputBuffer = i2cStreamLink->outputBuffer;
        // Get an inputStream to read the buffer to send to the master
        InputStream* i2cInputStream = getInputStream(i2cSlaveOutputBuffer);

        // There is available data
        if (i2cInputStream->availableData(i2cInputStream)) {
            char c = i2cInputStream->readChar(i2cInputStream);
            // for debug support
            appendI2cDebugOutputChar(c);
            portableSlaveWriteI2C(i2cBusConnection, c);
        } else {
            portableSlaveWriteI2C(i2cBusConnection, I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
        } 
    }
    // Master want to read
    else if (isStart && read && isData && !isSclRelease) {

        // R/W bit = 1 --> indicates data transfer is output from slave
        // D/A bit = 1 --> indicates last byte was data
        Buffer* i2cSlaveOutputBuffer = i2cStreamLink->outputBuffer;
        // Get an inputStream to read the buffer to send to the master
        InputStream* i2cInputStream = getInputStream(i2cSlaveOutputBuffer);

        // There is available data
        if (i2cInputStream->availableData(i2cInputStream)) {
            char c = i2cInputStream->readChar(i2cInputStream);
            // for debug support
            appendI2cDebugInputChar(c);
            // we send it to the master
            portableSlaveWriteI2C(i2cBusConnection, c);
        } else {
            // There is no data, we send it to the master
            portableSlaveWriteI2C(i2cBusConnection, I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
        }
    }
    // finally clear the slave interrupt flag
    mI2C1SClearIntFlag();
}
