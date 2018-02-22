#include "i2cMasterPc.h"

#include "i2cMasterSetupPc.h"
#include "../i2cMaster.h"

#include "../../../../common/error/error.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/pc/i2cCommonPc.h"

#include "../../../../common/pc/pipe/pipeServerHelper.h"
#include "../../../../common/pc/pipe/pipeClientHelper.h"

#include <Windows.h>

void portableMasterStartI2C(I2cBusConnection* i2cBusConnection) {
    // Use Common Function and Send STX special code (see ASCII table)
    portableMasterWriteI2C(i2cBusConnection, ASCII_STX);
}

void portableMasterStopI2C(I2cBusConnection* i2cBusConnection) {
    // Use Common Function and Send ETX special code (see ASCII table)
    portableMasterWriteI2C(i2cBusConnection, ASCII_ETX);
}

void portableMasterAckI2C(I2cBusConnection* i2cBusConnection) {
    // portableMasterWriteI2C(i2cBusConnection, ASCII_ACK);
}

void portableMasterNackI2C(I2cBusConnection* i2cBusConnection) {
    // TODO
}

unsigned int portableMasterWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char data) {
    if (i2cBusConnection == NULL) {
        writeError(I2C_BUS_CONNECTION_NULL);
        return 0;
    }
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        writeError(I2C_BUS_NULL);
        return 0;
    }
    I2cBusConnectionPc* i2cBusConnectionPc = getI2cBusConnectionPc(i2cBusConnection);
    if (i2cBusConnectionPc == NULL) {
        writeError(I2C_BUS_CONNECTION_OBJECT_NULL);
        return 0;
    }
    HANDLE pipe = i2cBusConnectionPc->masterToSlaveHandle;
    if (pipe == NULL) {
        writeError(I2C_BUS_CONNECTION_MASTER_TO_SLAVE_PIPE_NULL);
        return 0;
    }

    writeCharToPipe(pipe, data);
    return data;
}

unsigned char portableMasterReadI2C(I2cBusConnection* i2cBusConnection) {
    if (i2cBusConnection == NULL) {
        writeError(I2C_BUS_CONNECTION_NULL);
        return 0;
    }
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus == NULL) {
        writeError(I2C_BUS_NULL);
        return 0;
    }
    I2cBusConnectionPc* i2cBusConnectionPc = getI2cBusConnectionPc(i2cBusConnection);
    if (i2cBusConnectionPc == NULL) {
        writeError(I2C_BUS_CONNECTION_OBJECT_NULL);
        return '?';
    }

    HANDLE pipe = i2cBusConnectionPc->slaveToMasterHandle;
    if (pipe == NULL) {
        writeError(I2C_BUS_CONNECTION_SLAVE_TO_MASTER_PIPE_NULL);
        return '?';
    }

    unsigned char result = readCharFromPipe(pipe);
    
    return result;
}

void portableMasterWaitSendI2C(I2cBusConnection* i2cBusConnection) {
    // No Wait
}

void portableMasterCloseI2C(I2cBus* i2cBus) {

}
