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
I2cBusConnection* _i2cMasterGetI2cBusConnection(OutputStream* outputStream) {
    I2cMasterOutputStream* i2cMasterOutputStream = _i2cMasterGetMasterOutputStream(outputStream);
    
    I2cBusConnection* result = i2cMasterOutputStream->i2cBusConnection;

    return result;
}


/**
 * @private
 */
void _i2cMasterOpenOutputStream(OutputStream* outputStream, int param1) {
    I2cBusConnection* i2cBusConnection = _i2cMasterGetI2cBusConnection(outputStream);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    if (i2cBus->initialized) {
        return;
    }
    i2cMasterInitialize(i2cBus);
}

/**
 * @private
 */
void _i2cMasterCloseOutputStream(OutputStream* outputStream) {
    I2cBusConnection* i2cBusConnection = _i2cMasterGetI2cBusConnection(outputStream);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    i2cMasterFinalize(i2cBus);
}

/**
 * @private
 * We don't write directly the char, because it's more efficient
 * to wait the end of data to send a array in i2c
 */
void _writeCharI2C(OutputStream* outputStream, unsigned char c) {
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
    Buffer* buffer = _i2cMasterGetOutputBuffer(outputStream);
    I2cBusConnection* i2cBusConnection = _i2cMasterGetI2cBusConnection(outputStream);
    i2cMasterWriteBuffer(i2cBusConnection, buffer);
}

void initMasterI2cOutputStream(I2cMasterOutputStream* i2cMasterOutputStream, I2cBusConnection* i2cBusConnection, OutputStream* outputStream,
        Buffer* i2cOutputBuffer) {
    i2cMasterOutputStream->i2cBusConnection = i2cBusConnection;
    i2cMasterOutputStream->outputStream = outputStream;
    i2cMasterOutputStream->outputBuffer = i2cOutputBuffer;
    outputStream->object = (int*) i2cMasterOutputStream;

    outputStream->address = i2cBusConnection->i2cAddress;
    outputStream->openOutputStream = _i2cMasterOpenOutputStream;
    outputStream->closeOutputStream = _i2cMasterCloseOutputStream;
    outputStream->writeChar = _writeCharI2C;
    outputStream->flush = _flushI2C;
    _i2cMasterOpenOutputStream(outputStream, 0);
}
