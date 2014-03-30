#include <stdlib.h>

#include "i2cMaster.h"
#include "i2cMasterSetup.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/stream.h"
#include "../../../common/io/inputStream.h"

// DEBUG
#include "../../../common/delay/delay30F.h"
#include "../../../common/log/logHandler.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/printWriter.h"

// INPUT STREAM INTERFACE

/**
 * Get the buffer attached to the inputStream
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
    while (1) {
        // TODO : REMOVE the delay if it's OK
		delay100us(5);
        unsigned char c = i2cMasterReadChar(inputStream->address);

        if (c == I2C_SLAVE_NO_DATA_IN_READ_BUFFER || c == INCORRECT_DATA) {
            break;
        }

        /*
        append(getOutputStreamLogger(DEBUG), '(');
        append(getOutputStreamLogger(DEBUG), c);
        append(getOutputStreamLogger(DEBUG), ')');
         */

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
    return !isBufferEmpty(buffer);
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
