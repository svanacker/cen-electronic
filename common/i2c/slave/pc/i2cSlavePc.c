#include "i2cSlaveSetupPc.h"

#include "../i2cSlave.h"
#include "../i2cSlaveSetup.h"
#include "../../i2cConstants.h"
#include "../../i2cDebug.h"

#include "../../../../common/pc/pipe/pipeClientHelper.h"
#include "../../../../common/pc/pipe/pipeServerHelper.h"


unsigned char portableSlaveReadI2C(void) {
    HANDLE masterToSlaveHandle = getI2CMasterToSlaveHandle();

    unsigned char result = readCharFromPipe(masterToSlaveHandle);
    return result;
}

void portableSlaveWriteI2C(unsigned char c) {
    HANDLE slaveToMasterHandle = getI2CSlaveToMasterHandle();

    writeCharToPipe(slaveToMasterHandle, c);
}
