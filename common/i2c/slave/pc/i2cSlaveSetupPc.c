#include "i2cSlaveSetupPc.h"
#include "i2cSlavePc.h"
#include "../../../../common/commons.h"
#include "../../../../common/delay/cenDelay.h"

#include "../../../../common/error/error.h"

#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"
#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../i2cSlaveSetup.h"
#include "../../../../test/main/pipeHelper.h"

#include <Windows.h>

static HANDLE masterToSlaveHandle;
static HANDLE threadHandle;
static DWORD  threadId = 0;

// Callback function forward declaration
DWORD WINAPI InstanceThread(LPVOID lpvParam);

static bool initialized = false;

HANDLE getI2CMasterToSlaveHandle() {
    return masterToSlaveHandle;
}

void i2cSlaveInitialize(char writeAddress) {
    // Avoid more than one initialization
    if (initialized) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
    masterToSlaveHandle = initSlaveToMasterPipe(L"\\\\.\\pipe\\mainBoardPipe");
    initialized = true;
    getI2CSlaveToMasterPcBuffer();

    appendString(getOutputStreamLogger(DEBUG), "I2C Slave Write Address=");
    appendHex2(getOutputStreamLogger(DEBUG), writeAddress);
    appendCRLF(getOutputStreamLogger(DEBUG));

    // Create a thread for this client. 
    threadHandle = CreateThread(
        NULL,              // no security attribute 
        0,                 // default stack size 
        InstanceThread,    // thread proc
        (LPVOID)masterToSlaveHandle,    // thread parameter 
        0,                 // not suspended 
        &threadId);      // returns thread ID 

    if (threadHandle == NULL)
    {
        printf("CreateThread failed, lastError=%d.\n", GetLastError());
    }
    else
    {
        // CloseHandle(threadHandle);
    }
}

DWORD WINAPI InstanceThread(LPVOID lpvParam) {
    printf("InstanceThread execute !");
    while (true) {
        delaymSec(500);
        sendI2CDataToMaster();
    }
    printf("InstanceThread exitting.\n");

    return 1;
}
