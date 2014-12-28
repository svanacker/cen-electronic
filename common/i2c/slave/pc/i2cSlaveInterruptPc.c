#include "i2cSlaveInterruptPc.h"
#include "i2cSlaveSetupPc.h"
#include "../i2cSlave.h"
#include "../../i2cConstants.h"
#include "../../i2cDebug.h"

#include "../../../../common/commons.h"
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

#define I2C_SLAVE_INTERRUPT_DELAY_MICRO_SECONDS	100

void sendI2CDataToMaster(void)
{
    if (!i2cReadFlag) {
        return;
    }
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

        // we send it to the master
        portableSlaveWriteI2C(c);

        // To Remove
        printf("%c", c);
    }
    else {
        // In this case, we must NOT add '\0' to the debug buffer (we will not see anything !)
        // In PC, the system is not the same than with interrupt, because we add something in a pipe
        // and on real I2C, value is just read on the fly, but not stored !
        portableSlaveWriteI2C(I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
    }
    // printI2cDebugBuffers();
}

void handleI2CDataFromMaster(void) {
    StreamLink* i2cStreamLink = getI2cStreamLink();

    unsigned char data = portableSlaveReadI2C();
    if (INCORRECT_DATA != data && I2C_SLAVE_FAKE_WRITE != data) {
        // printf("Raw data : %c\r\n", data);
        // printf("Address : %d\r\n", getI2CWriteAddress());
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
        // printf("Real data : %c\r\n", data);
        if (!i2cAddressDefinedFlag) {

            // printf("writeAddress : %c", data);
            // We don't care about write Address or Read address
            if (getI2cWriteAddress() == (data & 0xFE)) {
                
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
        // delay10us(I2C_SLAVE_INTERRUPT_DELAY_MICRO_SECONDS / 10);
        delayUs();
        handleI2CDataFromMaster();
    }
    printf("masterToSlaveCallback exitting.\n");

    return 1;
}

DWORD WINAPI slaveToMasterCallback(LPVOID lpvParam) {
    printf("PC : I2 Slave -> Master listening !\r\n");
    while (true) {
        // delay1us(I2C_SLAVE_INTERRUPT_DELAY_MICRO_SECONDS / 10);
        delayUs();
        sendI2CDataToMaster();
    }
    printf("slaveToMasterCallback exitting.\n");

    return 1;
}
