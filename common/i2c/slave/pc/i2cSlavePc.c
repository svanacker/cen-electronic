#include "i2cSlaveSetupPc.h"

#include "../../pc/i2cCommonPc.h"

#include "../i2cSlave.h"
#include "../i2cSlaveSetup.h"
#include "../../i2cConstants.h"
#include "../../i2cDebug.h"

#include "../../../../common/error/error.h"

#include "../../../../common/pc/pipe/pipeClientHelper.h"
#include "../../../../common/pc/pipe/pipeServerHelper.h"

unsigned char portableSlaveReadI2C(I2cBusConnection* i2cBusConnection) {
    I2cBusConnectionPc* i2cBusConnectionPc = getI2cBusConnectionPc(i2cBusConnection);
    if (i2cBusConnectionPc == NULL) {
        writeError(I2C_BUS_CONNECTION_OBJECT_NULL);
        return 0;
    }

    HANDLE masterToSlaveHandle = i2cBusConnectionPc->masterToSlaveHandle;
    if (masterToSlaveHandle == NULL) {
        writeError(I2C_BUS_CONNECTION_MASTER_TO_SLAVE_PIPE_NULL);
        return 0;
    }

    unsigned char result = readCharFromPipe(masterToSlaveHandle);
    return result;
}

void portableSlaveWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char c) {
    I2cBusConnectionPc* i2cBusConnectionPc = getI2cBusConnectionPc(i2cBusConnection);
    if (i2cBusConnectionPc == NULL) {
        writeError(I2C_BUS_CONNECTION_OBJECT_NULL);
        return;
    }
    HANDLE slaveToMasterHandle = i2cBusConnectionPc->slaveToMasterHandle;
    if (slaveToMasterHandle == NULL) {
        writeError(I2C_BUS_CONNECTION_SLAVE_TO_MASTER_PIPE_NULL);
        return;
    }

    writeCharToPipe(slaveToMasterHandle, c);
}
