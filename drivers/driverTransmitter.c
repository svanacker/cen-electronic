#include <stdlib.h>
#include "driverTransmitter.h"

#include "driverStreamListener.h"

#include "../common/commons.h"
#include "../common/cmd/commonCommand.h"

#include "../common/io/inputStream.h"
#include "../common/io/ioUtils.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/reader.h"
#include "../common/io/stream.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../drivers/driverList.h"
#include "../drivers/driverStreamListener.h"

BOOL transmitFromDriverRequestBuffer() {
    // We do exactly as if the data was written by a end-user
    // requestBuffer must be filled before calling this method
    Buffer* requestBuffer = getDriverRequestBuffer();
    Buffer* responseBuffer = getDriverResponseBuffer();

    // The first char is the header
    char header = bufferGetFirstChar(requestBuffer);

    BOOL result = handleStreamInstruction(
            requestBuffer,
            responseBuffer,
            // Don't copy to an outputStream, because, we
            // want to read the content of responseBuffer
            NULL,
            // No Input Filter
            NULL,
            // No Output Filter
            NULL);

    InputStream* inputStream = getDriverResponseInputStream();
    // We need ack
    checkIsAck(inputStream);
    // Device answer with the same header as the request
    checkIsChar(inputStream, header);

    return result;
}
