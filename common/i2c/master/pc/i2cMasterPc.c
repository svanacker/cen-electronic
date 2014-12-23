#include "i2cMasterPc.h"
#include "i2cMasterSetupPc.h"
#include "../i2cMaster.h"
#include "../../../../common/i2c/i2cCommon.h"

#include "../../../../common/io/buffer.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/reader.h"

#include "../../../../test/main/pipeServerHelper.h"

unsigned int portableMasterWriteI2C(unsigned char data) {

	HANDLE pipe = getMasterPipeHandle();
	// TODO : Create a local version of I2C ! append(getOutputStream(&i2cMasterToSlavePcBuffer), data);
	writeCharToPipe(pipe, data);
	return data;
}

unsigned char portableMasterReadI2C() {
	// TODO : Find the right Address
	HANDLE pipe = getSlavePipeHandle(0x00);
	
	unsigned char result = readCharFromPipe(pipe);
	
	// return I2C_SLAVE_NO_DATA_IN_READ_BUFFER;
	return result;
}

void portableMasterWaitSendI2C(void) {
	// No Wait
}

void portableCloseI2C() {

}
