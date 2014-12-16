#include "../../../../common/commons.h"

#include <stdlib.h>

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

static Buffer i2cSlaveToMasterPcBuffer;
#define I2C_SLAVE_PC_LENGTH	40
static char i2cSlaveToMasterPcBufferArray[I2C_SLAVE_PC_LENGTH];

// Specific to Pc
Buffer* getI2CSlaveToMasterPcBuffer(void) {
	if (i2cSlaveToMasterPcBuffer.length == 0) {
		initBuffer(&i2cSlaveToMasterPcBuffer, (char(*)[]) &i2cSlaveToMasterPcBufferArray, I2C_SLAVE_PC_LENGTH, "i2cMasterPc", "TO_MASTER");
	}
	return &i2cSlaveToMasterPcBuffer;
}