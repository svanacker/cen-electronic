#include <stdbool.h>

#include "../i2cMasterSetup.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/master/i2cMaster.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"
#include "../../../../common/io/printWriter.h"

#include "../../../../test/main/pipeHelper.h"

#define PIPE_I2C_MASTER_NAME	L"\\\\.\\pipe\\mainBoardPipe"

static HANDLE masterPipeHandle = NULL;

HANDLE getMasterPipeHandle() {
    return masterPipeHandle;
}

void i2cMasterInitialize(void) {
    // Avoid more than one initialization
    if (masterPipeHandle != NULL) {
        appendString(getOutputStreamLogger(DEBUG), "I2C PC Master (Pipe) already initialized\n");
        return;
    }
    masterPipeHandle = initMasterToSlavePipe(PIPE_I2C_MASTER_NAME);
}

void i2cMasterFinalize(void) {
    if (masterPipeHandle != NULL) {
        portableCloseI2C();
        CloseHandle(masterPipeHandle);
    }
}
