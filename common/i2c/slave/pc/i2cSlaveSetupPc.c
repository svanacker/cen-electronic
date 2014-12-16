#include "i2cSlavePc.h"
#include "../../../../common/commons.h"

#include "../../../../common/error/error.h"

#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"
#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../i2cSlaveSetup.h"

bool initialized = false;

void i2cSlaveInitialize(char writeAddress) {
    // Avoid more than one initialization
    if (initialized) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
	initialized = true;
	getI2CSlaveToMasterPcBuffer();

    appendString(getOutputStreamLogger(DEBUG), "I2C Slave Write Address=");
    appendHex2(getOutputStreamLogger(DEBUG), writeAddress);
    appendCRLF(getOutputStreamLogger(DEBUG));
}
