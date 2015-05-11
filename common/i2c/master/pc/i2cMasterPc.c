#include "i2cMasterPc.h"

#include "i2cMasterSetupPc.h"
#include "../i2cMaster.h"

#include "../../../../common/i2c/i2cCommon.h"

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
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    I2cMasterBusPc* masterBusPc = getMasterI2cBusPc(i2cBus);
    HANDLE pipe = masterBusPc->masterPipeHandle;

    writeCharToPipe(pipe, data);
    return data;
}

unsigned char portableMasterReadI2C(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    I2cMasterBusPc* masterBusPc = getMasterI2cBusPc(i2cBus);
    HANDLE pipe = masterBusPc->slavePipeHandle;

    unsigned char result = readCharFromPipe(pipe);
    
    return result;
}

void portableMasterWaitSendI2C(I2cBusConnection* i2cBusConnection) {
    // No Wait
}

void portableMasterCloseI2C(I2cBus* i2cBus) {

}
