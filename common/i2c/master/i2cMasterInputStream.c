#include <stdlib.h>

#include "i2cMaster.h"
#include "i2cMasterInputStream.h"
#include "i2cMasterSetup.h"

#include "../../../common/i2c/i2cDebug.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"

// DEBUG
#include "../../../common/log/logHandler.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

// INPUT STREAM INTERFACE

/**
 * @private
 */
I2cMasterInputStream* _i2cMasterGetMasterInputStream(InputStream* inputStream) {
    I2cMasterInputStream* result = (I2cMasterInputStream*) inputStream->object;

    return result;
}

/**
 * @private.
 * Get the buffer attached to the inputStream
 * @param inputStream returns the inputStream attached to the I2C Input Buffer.
 */
Buffer* _i2cMasterInputStreamGetBuffer(InputStream* inputStream) {
    I2cMasterInputStream* i2cMasterInputStream = _i2cMasterGetMasterInputStream(inputStream);

    Buffer* result = i2cMasterInputStream->inputBuffer;

    return result;
}

/**
 * @private
 */
I2cBusConnection* _i2cMasterInputStreamGetI2cBusConnection(InputStream* inputStream) {
    I2cMasterInputStream* i2cMasterInputStream = _i2cMasterGetMasterInputStream(inputStream);

    I2cBusConnection* result = i2cMasterInputStream->i2cBusConnection;

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
        I2cBusConnection* i2cBusConnection = _i2cMasterInputStreamGetI2cBusConnection(inputStream);
        unsigned char c = i2cMasterReadChar(i2cBusConnection);

        if (c == I2C_SLAVE_NO_DATA_IN_READ_BUFFER || c == INCORRECT_DATA) {
            break;
        }

        appendI2cDebugInputChar(c);

        Buffer* buffer = _i2cMasterInputStreamGetBuffer(inputStream);
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
    Buffer* buffer = _i2cMasterInputStreamGetBuffer(inputStream);
    bool result = !isBufferEmpty(buffer);

    return result;
}

/**
 * Be aware not to read before call to "availableDataFunction"
 * @private
 */
unsigned char _readCharI2C(InputStream* inputStream) {
    Buffer* buffer = _i2cMasterInputStreamGetBuffer(inputStream);
    return bufferReadChar(buffer);
}

void initMasterI2cInputStream(I2cMasterInputStream* i2cMasterInputStream,
        I2cBusConnection* i2cBusConnection,
        Buffer* i2cInputBuffer,
        InputStream* inputStream) {
    i2cMasterInputStream->i2cBusConnection = i2cBusConnection;
    i2cMasterInputStream->inputStream = inputStream;
    i2cMasterInputStream->inputBuffer = i2cInputBuffer;
    inputStream->object = (int*) i2cMasterInputStream;


    inputStream->address = i2cBusConnection->i2cAddress;
    inputStream->openInputStream = _i2cMasterOpenInputStream;
    inputStream->closeInputStream = _i2cMasterCloseInputStream;
    inputStream->readChar = _readCharI2C;
    inputStream->availableData = _i2cAvailableData;
    _i2cMasterOpenInputStream(inputStream, 0);
}
