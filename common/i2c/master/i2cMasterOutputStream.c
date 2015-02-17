#include <stdlib.h>

#include "i2cMaster.h"
#include "i2cMasterSetup.h"
#include "i2cMasterOutputStream.h"

#include "../../../common/i2c/i2cCommon.h"
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
I2cMasterOutputStream* _i2cMasterGetMasterOutputStream(OutputStream* outputStream) {
    I2cMasterOutputStream* result = (I2cMasterOutputStream*) outputStream->object;

    return result;
}

/**
 * @private
 */
Buffer* _i2cMasterGetOutputBuffer(OutputStream* outputStream) {
    I2cMasterOutputStream* i2cMasterOutputStream = _i2cMasterGetMasterOutputStream(outputStream);
    
    Buffer* result = i2cMasterOutputStream->outputBuffer;

    return result;
}

/**
 * @private
 */
I2cBus* _i2cMasterGetI2cBus(OutputStream* outputStream) {
    I2cMasterOutputStream* i2cMasterOutputStream = _i2cMasterGetMasterOutputStream(outputStream);
    
    I2cBus* result = i2cMasterOutputStream->i2cBus;

    return result;
}


/**
 * @private
 */
void _i2cMasterOpenOutputStream(OutputStream* outputStream, int param1) {
    I2cBus* i2cBus = _i2cMasterGetI2cBus(outputStream);
    i2cMasterInitialize(i2cBus);
}

/**
 * @private
 */
void _i2cMasterCloseOutputStream(OutputStream* outputStream) {
    I2cBus* i2cBus = _i2cMasterGetI2cBus(outputStream);
    i2cMasterFinalize(i2cBus);
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
    I2cBus* i2cBus = _i2cMasterGetI2cBus(outputStream);
    i2cMasterWriteBuffer(i2cBus, address, buffer);
}

void initMasterI2cOutputStream(I2cMasterOutputStream* i2cMasterOutputStream, I2cBus* i2cBus, OutputStream* outputStream,
        Buffer* i2cOutputBuffer,
        unsigned char i2cWriteAddress) {
    i2cMasterOutputStream->i2cBus = i2cBus;
    i2cMasterOutputStream->outputStream = outputStream;
    i2cMasterOutputStream->outputBuffer = i2cOutputBuffer;
    outputStream->object = (int*) i2cMasterOutputStream;

    outputStream->address = i2cWriteAddress;
    outputStream->openOutputStream = _i2cMasterOpenOutputStream;
    outputStream->closeOutputStream = _i2cMasterCloseOutputStream;
    outputStream->writeChar = _writeCharI2C;
    outputStream->flush = _flushI2C;
    _i2cMasterOpenOutputStream(outputStream, 0);
}
