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

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../device/deviceInterface.h"
#include "../device/deviceConstants.h"

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
        bool result = redirectFunction();
        return result;
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

    // The first char is the device header
    unsigned dataDispacherLength = 0;
    unsigned char deviceHeader = bufferGetCharAtIndex(requestBuffer, DEVICE_HEADER_INDEX);

    if (deviceHeader == DISPATCHER_COMMAND_HEADER) {
        dataDispacherLength = DISPATCHER_COMMAND_AND_INDEX_HEADER_LENGTH;
        // Reload the real Device Header
        deviceHeader = bufferGetCharAtIndex(requestBuffer, dataDispacherLength + DEVICE_HEADER_INDEX);
    }

    // The second char is the command header
    unsigned char commandHeader = bufferGetCharAtIndex(requestBuffer, dataDispacherLength + COMMAND_HEADER_INDEX);

    bool result = handleStreamInstruction(
            requestBuffer,
            responseBuffer,
            // Don't copy to an outputStream, because, we
            // want to read the content of responseBuffer
            NULL,
            // TODO : Check why we don't provide any NotificationOutputStream
            NULL,
            // No Input Filter
            NULL,
            // No Output Filter
            NULL);

    // We need ack
    result = checkIsAck(inputStream);
    if (!result) {
        // The buffer is corrupted, but we would like to avoid further problem
        clearInputStream(inputStream);
        return false;
    }
    // Device header answer with the same header as the request
    checkIsChar(inputStream, deviceHeader);
    if (!result) {
        // The buffer is corrupted, but we would like to avoid further problem
        clearInputStream(inputStream);
        return false;
    }
    // Command header answer with the same header as the request
    checkIsChar(inputStream, commandHeader);
    if (!result) {
        // The buffer is corrupted, but we would like to avoid further problem
        clearInputStream(inputStream);
        return false;
    }

    return result;
}
