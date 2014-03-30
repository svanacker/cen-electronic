#include <stdlib.h>
#include "driverTransmitter.h"

#include "driverStreamListener.h"

#include "../common/commons.h"
#include "../common/cmd/commonCommand.h"

#include "../common/error/error.h"

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

/** RedirectFunction : OFTEN NULL. */
static transmitFromDriverRequestBufferFunction* redirectFunction;

void setRedirectionTransmitFromDriverRequestBuffer(transmitFromDriverRequestBufferFunction* function) {
	redirectFunction = function;
}

bool transmitFromDriverRequestBuffer() {
	// Handle redirection
	if (redirectFunction != NULL) {
		return redirectFunction();
	}
    // We do exactly as if the data was written by a end-user
    // requestBuffer must be filled before calling this method
    Buffer* requestBuffer = getDriverRequestBuffer();
    Buffer* responseBuffer = getDriverResponseBuffer();

    InputStream* inputStream = getDriverResponseInputStream();
	if (inputStream == NULL) {
		writeError(DRIVER_INPUT_STREAM_NULL);
		return false;
	}

    // The first char is the header
    char header = bufferGetFirstChar(requestBuffer);

    bool result = handleStreamInstruction(
            requestBuffer,
            responseBuffer,
            // Don't copy to an outputStream, because, we
            // want to read the content of responseBuffer
            NULL,
            // No Input Filter
            NULL,
            // No Output Filter
            NULL);

    // We need ack
    checkIsAck(inputStream);
    // Device answer with the same header as the request
    checkIsChar(inputStream, header);

    return result;
}
