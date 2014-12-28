#include <stdlib.h>

#include "i2cMaster.h"
#include "i2cMasterSetup.h"
#include "../../../common/i2c/i2cDebug.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"

// DEBUG
#include "../../../common/log/logHandler.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/printWriter.h"

// INPUT STREAM INTERFACE

/**
 * @private.
 * Get the buffer attached to the inputStream
 * @param inputStream returns the inputStream attached to the I2C Input Buffer.
 */
Buffer* getI2CMasterInputBuffer(InputStream* inputStream) {
    Buffer* result = (Buffer*) inputStream->object;

    return result;
}

/**
 * @private
 */
void _i2cMasterOpenInputStream(InputStream* inputStream, int param1) {

}

/**
 * @private
 */
void fillI2CInputInternalBuffer(InputStream* inputStream) {
    while (true) {
        unsigned char c = i2cMasterReadChar(inputStream->address);

        if (c == I2C_SLAVE_NO_DATA_IN_READ_BUFFER || c == INCORRECT_DATA) {
            break;
        }

        appendI2cDebugInputChar(c);

        Buffer* buffer = getI2CMasterInputBuffer(inputStream);
        bufferWriteChar(buffer, c);
    }
}

/**
 * @private
 */
void _i2cMasterCloseInputStream(InputStream* inputStream) {

}

bool _i2cAvailableData(InputStream* inputStream) {
    fillI2CInputInternalBuffer(inputStream);
    Buffer* buffer = getI2CMasterInputBuffer(inputStream);
    bool result = !isBufferEmpty(buffer);

    return result;
}

/**
 * Be aware not to read before call to "availableDataFunction"
 * @private
 */
char _readCharI2C(InputStream* inputStream) {
    Buffer* buffer = getI2CMasterInputBuffer(inputStream);
    return bufferReadChar(buffer);
}

void initMasterI2cInputStream(Buffer* i2cInputBuffer,
                                InputStream* inputStream,
                                unsigned char i2cWriteAddress) {
    inputStream->address = i2cWriteAddress;
    inputStream->openInputStream = _i2cMasterOpenInputStream;
    inputStream->closeInputStream = _i2cMasterCloseInputStream;
    inputStream->readChar = _readCharI2C;
    inputStream->availableData = _i2cAvailableData;
    inputStream->object = (int*) i2cInputBuffer;
    _i2cMasterOpenInputStream(inputStream, i2cWriteAddress);
}
