#include <stdlib.h>

#include "i2cMaster.h"
#include "i2cMasterSetup.h"
#include "../../../common/i2c/i2cDebug.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"

/**
 * OUTPUT STREAM INTERFACE FOR I2C
 * Output is buffered because we send more efficiently the data
 */

/**
 * @private
 */
Buffer* _i2cMasterGetOutputBuffer(OutputStream* outputStream) {
    Buffer* result = (Buffer*) outputStream->object;

    return result;
}

/**
 * @private
 */
void _i2cMasterOpenOutputStream(OutputStream* outputStream, int param1) {
    i2cMasterInitialize();
}

/**
 * @private
 */
void _i2cMasterCloseOutputStream(OutputStream* outputStream) {
    i2cMasterFinalize();
}

/**
 * @private
 * We don't write directly the char, because it's more efficient
 * to wait the end of data to send a array in i2c
 */
void _writeCharI2C(OutputStream* outputStream, char c) {
    Buffer* buffer = _i2cMasterGetOutputBuffer(outputStream);

	// Debug
	appendI2cDebugOutputChar(c);
	// Real
	bufferWriteChar(buffer, c);
}

/**
 * @private
 * We flush the buffer (more efficient)
 */
void _flushI2C(OutputStream* outputStream) {
    int address = outputStream->address;
    Buffer* buffer = _i2cMasterGetOutputBuffer(outputStream);
    i2cMasterWriteBuffer(address, buffer);
}

void initMasterI2cOutputStream(OutputStream* outputStream,
        Buffer* i2cBuffer,
        unsigned char i2cWriteAddress) {
    outputStream->address = i2cWriteAddress;
    outputStream->openOutputStream = _i2cMasterOpenOutputStream;
    outputStream->closeOutputStream = _i2cMasterCloseOutputStream;
    outputStream->writeChar = _writeCharI2C;
    outputStream->flush = _flushI2C;
    outputStream->object = (int*) i2cBuffer;
    _i2cMasterOpenOutputStream(outputStream, 0);
}
