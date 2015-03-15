#include <stdbool.h>
#include <stdlib.h>

#include "i2cSlaveInterruptPc.h"
#include "i2cSlaveSetupPc.h"
#include "../i2cSlave.h"
#include "../../i2cConstants.h"
#include "../../i2cDebug.h"

#include "../../../../common/delay/cenDelay.h"

#include "../../../../common/error/error.h"

#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"
#include "../../../../common/io/streamLink.h"
#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../../../../common/pc/pipe/pipeClientHelper.h"
#include "../../../../common/pc/pipe/pipeServerHelper.h"

static bool i2cStartFlag = false;
static bool i2cAddressDefinedFlag = false;
static bool i2cReadFlag = false;

void sendI2CDataToMaster(void) {
    if (!i2cReadFlag) {
        return;
    }
    // TODO : Find the right I2CBus
    I2cBus* i2cBus = NULL;

    StreamLink* i2cStreamLink = getI2cStreamLink();

    // The buffer which must be send to the master
    Buffer* i2cSlaveOutputBuffer = i2cStreamLink->outputBuffer;
    // Get an inputStream to read the buffer to send to the master
    InputStream* i2cInputStream = getInputStream(i2cSlaveOutputBuffer);
    // There is available data
    if (i2cInputStream->availableData(i2cInputStream)) {
        char c = i2cInputStream->readChar(i2cInputStream);

        // for debug support
        appendI2cDebugOutputChar(c);

        // TODO : Find the right i2cBus
        I2cBus* i2cBus = NULL;

        // we send it to the master
        portableSlaveWriteI2C(i2cBus, c);

        // To Remove
        printf("%c", c);
    }
    else {
        // In this case, we must NOT add '\0' to the debug buffer (we will not see anything !)
        // In PC, the system is not the same than with interrupt, because we add something in a pipe
        // and on real I2C, value is just read on the fly, but not stored !
        portableSlaveWriteI2C(i2cBus, I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
    }
}

void handleI2CDataFromMaster(void) {
    StreamLink* i2cStreamLink = getI2cStreamLink();

    // TODO : Find the right I2CBus
    I2cBus* i2cBus = NULL;

    unsigned char data = portableSlaveReadI2C(i2cBus);
    if (INCORRECT_DATA != data && I2C_SLAVE_FAKE_WRITE != data) {
        if (ASCII_STX == data) {
            i2cStartFlag = true;
            i2cAddressDefinedFlag = false;
            i2cReadFlag = false;
            return;
        }
        else if (ASCII_ETX == data) {
            i2cStartFlag = false;
            i2cAddressDefinedFlag = false;
            i2cReadFlag = false;
            return;
        }
        if (!i2cStartFlag) {
            return;
        }
        
        // Data here are real data (not start / stop or the address)
        if (!i2cAddressDefinedFlag) {

            // We don't care about write Address or Read address
            if (getI2cWriteAddress(NULL) == (data & 0xFE)) {
                
                i2cAddressDefinedFlag = true;
                // Read I2C Flag is activated when the last bit is activated
                i2cReadFlag = data & 0x01;
            }
            return;
        }
        printf("%c", data);

        Buffer* i2cSlaveInputBuffer = i2cStreamLink->inputBuffer;
        OutputStream* outputStream = getOutputStream(i2cSlaveInputBuffer);
        // Read data from the Master
        append(outputStream, data);

        appendI2cDebugInputChar(data);
    }
}

DWORD WINAPI masterToSlaveCallback(LPVOID lpvParam) {
    printf("PC : I2C Master -> Slave listening !\r\n");
    while (true) {
        delayUs();
        handleI2CDataFromMaster();
    }
    printf("masterToSlaveCallback exiting.\n");

    return 1;
}

DWORD WINAPI slaveToMasterCallback(LPVOID lpvParam) {
    printf("PC : I2 Slave -> Master listening !\r\n");
    while (true) {
        delayUs();
        sendI2CDataToMaster();
    }
    printf("slaveToMasterCallback exiting.\n");

    return 1;
}
