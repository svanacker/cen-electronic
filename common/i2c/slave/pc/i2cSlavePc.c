#include "i2cSlaveSetupPc.h"

#include "../i2cSlave.h"
#include "../i2cSlaveSetup.h"
#include "../../i2cConstants.h"
#include "../../i2cDebug.h"

#include "../../../../common/pc/pipe/pipeClientHelper.h"
#include "../../../../common/pc/pipe/pipeServerHelper.h"


unsigned char portableSlaveReadI2C(I2cBusConnection* i2cBusConnection) {
    I2cSlaveBusConnectionPc* i2cSlaveBusConnectionPc = getSlaveI2cBusConnectionPc(i2cBusConnection);
    HANDLE masterToSlaveHandle = i2cSlaveBusConnectionPc->masterToSlaveHandle;

    unsigned char result = readCharFromPipe(masterToSlaveHandle);
    return result;
}

void portableSlaveWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char c) {
    I2cSlaveBusConnectionPc* i2cSlaveBusConnectionPc = getSlaveI2cBusConnectionPc(i2cBusConnection);
    HANDLE slaveToMasterHandle = i2cSlaveBusConnectionPc->slaveToMasterHandle;

    writeCharToPipe(slaveToMasterHandle, c);
}
