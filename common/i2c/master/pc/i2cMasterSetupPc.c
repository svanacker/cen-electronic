#include <stdbool.h>

#include "../i2cMasterSetup.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/delay/cenDelay.h"
#include "../../../../common/i2c/master/i2cMaster.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"
#include "../../../../common/io/printWriter.h"

#include "../../../../test/main/pipeServerHelper.h"

#include <Windows.h>

#define PIPE_I2C_MASTER_NAME	L"\\\\.\\pipe\\mainBoardPipe"
#define PIPE_I2C_SLAVE_NAME	L"\\\\.\\pipe\\motorBoardPipe"

static HANDLE masterPipeHandle = NULL;
static HANDLE slavePipeHandle = NULL;

HANDLE getMasterPipeHandle() {
    return masterPipeHandle;
}

HANDLE getSlavePipeHandle(unsigned char writeAddress) {
	// TODO : Handle Address !
	return slavePipeHandle;
}

void i2cMasterInitialize(void) {
    // Avoid more than one initialization
    if (masterPipeHandle != NULL) {
        appendString(getOutputStreamLogger(DEBUG), "I2C PC Master (Pipe) already initialized\n");
        return;
    }
    appendString(getOutputStreamLogger(DEBUG), "I2C Master Initialize\r\n");
    masterPipeHandle = initServerPipe(PIPE_I2C_MASTER_NAME);
    delaymSec(600);
    slavePipeHandle = initClientPipe(PIPE_I2C_SLAVE_NAME);
}

void i2cMasterFinalize(void) {
    if (masterPipeHandle != NULL) {
        portableCloseI2C();
        CloseHandle(masterPipeHandle);
    }
    if (slavePipeHandle != NULL) {
        CloseHandle(slavePipeHandle);
    }
}
