#include <stdlib.h>

#include "jennic5139Driver.h"
#include "jennic5139EventParser.h"

#include "../../common/io/buffer.h"
#include "../../common/io/stream.h"
#include "../../common/io/inputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

// INPUT STREAM INTERFACE

/**
 * @private
 */
void _jennic5139OpenInputStream(InputStream* inputStream, int param1) {

}

/**
 * @private
 */
void _jennic5139CloseInputStream(InputStream* inputStream) {

}

InputStream* _jennicGetUnderlyingInputStream() {
    Buffer* inDataBuffer = getJennicInDataBuffer();
    InputStream* result = getInputStream(inDataBuffer);

    return result;
}

bool _jennic5139AvailableData(InputStream* inputStream) {
    // fetch data to fill the data buffer
    copyFromZigbeeToDebugRetainingData();
    InputStream* underlyingInputStream = _jennicGetUnderlyingInputStream();

    bool result = underlyingInputStream->availableData(underlyingInputStream);

    return result;
}

/**
 * Be aware not to read before call to "availableDataFunction"
 * @private
 */
char _jennic5139ReadChar(InputStream* inputStream) {
    InputStream* underlyingInputStream = _jennicGetUnderlyingInputStream();

    char result = underlyingInputStream->readChar(underlyingInputStream);

    return result;
}

void initZigbeeInputStream(InputStream* inputStream,
                                char* jennicAddress) {
    int address = stringChecksum(jennicAddress);
    inputStream->address = address;
    inputStream->openInputStream = _jennic5139OpenInputStream;
    inputStream->closeInputStream = _jennic5139CloseInputStream;
    inputStream->readChar = _jennic5139ReadChar;
    inputStream->availableData = _jennic5139AvailableData;
    // TODO : Have the address
    inputStream->object = NULL;
    _jennic5139OpenInputStream(inputStream, address);
}
