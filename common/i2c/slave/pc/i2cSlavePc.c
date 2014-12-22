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

#include "../../../../test/main/pipeHelper.h"

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

unsigned char portableSlaveReadI2C(void) {
	HANDLE masterToSlaveHandle = getI2CMasterToSlaveHandle();

	unsigned char result = readCharFromPipe(masterToSlaveHandle);
	return result;
}

void portableSlaveWriteI2C(unsigned char c) {
	// TODO : Implementation
}

void handleI2CDataFromMaster(void)
{
	StreamLink* i2cStreamLink = getI2cStreamLink();

	// The buffer which must be send to the master
	Buffer* i2cSlaveOutputBuffer = i2cStreamLink->outputBuffer;
	// Get an inputStream to read the buffer to send to the master
	InputStream* i2cInputStream = getInputStream(i2cSlaveOutputBuffer);
	// For debug
	Buffer* debugI2cOutputBuffer = getDebugI2cOutputBuffer();
	// There is available data
	if (i2cInputStream->availableData(i2cInputStream)) {
		char c = i2cInputStream->readChar(i2cInputStream);
		// for debug support
		if (debugI2cOutputBuffer != NULL) {
			bufferWriteChar(debugI2cOutputBuffer, c);
		}
		// we send it to the master
		portableSlaveWriteI2C(c);
	}
	else {
		// There is no data, we send it to the master
		// We send 0 (end of buffer)
		if (debugI2cOutputBuffer != NULL) {
			bufferWriteChar(debugI2cOutputBuffer, I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
		}
		portableSlaveWriteI2C(I2C_SLAVE_NO_DATA_IN_READ_BUFFER);
	}
}

void sendI2CDataToMaster(void) {
	StreamLink* i2cStreamLink = getI2cStreamLink();

	int data = portableSlaveReadI2C();
	if (data != INCORRECT_DATA && data != I2C_SLAVE_FAKE_WRITE) {
		Buffer* i2cSlaveInputBuffer = i2cStreamLink->inputBuffer;
		OutputStream* outputStream = getOutputStream(i2cSlaveInputBuffer);
		// Read data from the Master
		append(outputStream, data);
		Buffer* debugI2cInputBuffer = getDebugI2cInputBuffer();
		if (debugI2cInputBuffer != NULL) {
			bufferWriteChar(debugI2cInputBuffer, data);
		}
	}
}