#include "../../../../common/commons.h"

#include <stdlib.h>

#include "i2cSlaveSetupPc.h"

#include "../i2cSlave.h"
#include "../i2cSlaveSetup.h"
#include "../../i2cConstants.h"
#include "../../i2cDebug.h"

#include "../../../../common/delay/cenDelay.h"

#include "../../../../common/io/inputStream.h"
#include "../../../../common/io/outputStream.h"
#include "../../../../common/io/buffer.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/ioUtils.h"

#include "../../../../common/log/logger.h"

#include "../../../../test/main/pipeClientHelper.h"
#include "../../../../test/main/pipeServerHelper.h"


unsigned char portableSlaveReadI2C(void) {
	HANDLE masterToSlaveHandle = getI2CMasterToSlaveHandle();

	unsigned char result = readCharFromPipe(masterToSlaveHandle);
	return result;
}

void portableSlaveWriteI2C(unsigned char c) {
	HANDLE slaveToMasterHandle = getI2CSlaveToMasterHandle();

	writeCharToPipe(slaveToMasterHandle, c);
}
