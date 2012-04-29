#include <stdlib.h>

#include "../../device/system/systemDeviceInterface.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"

#include "../../common/error/error.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/dispatcher/deviceDataDispatcher.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"

void transmitDriverData(int transmitMode,
        int address,
        Buffer* requestBuffer,
        Buffer* responseBuffer,
        int dataToTransferCount,
        int dataToReceiveCount
        ) {
    // Find dispatcher
    DriverDataDispatcher* dispatcher = getDriverDataDispatcherByTransmitMode(transmitMode, address);

    // If the dispatcher is found
    if (dispatcher != NULL) {
        // Transmit the data
        dispatcher->driverDataDispatcherTransmitData(dispatcher,
                requestBuffer,
                responseBuffer,
                dataToTransferCount,
                dataToReceiveCount
                );
    } else {
        writeError(NO_DISPATCHER_FOUND);
        OutputStream* errorOutputStream = getErrorOutputStreamLogger();
        appendStringAndDec(errorOutputStream, ",transmitMode=", transmitMode);
        appendStringAndDec(errorOutputStream, ",addr=", address);
    }
}

BOOL handleNotificationFromDispatcher(DriverDataDispatcher* dispatcher) {
    InputStream* inputStream = dispatcher->inputStream;

    if (inputStream == NULL) {
        writeError(NO_DISPATCHER_INPUT_STREAM);
        return FALSE;
    }

    if (inputStream->availableData(inputStream)) {

        // Get the underlying buffer
        Buffer* inputBuffer = (Buffer*) (inputStream->object);
        if (inputBuffer == NULL) {
            writeError(NO_DISPATCHER_INPUT_BUFFER);
        }
        char header = bufferGetFirstChar(inputBuffer);
        int bufferSize = getBufferElementsCount(inputBuffer);

        // find the device corresponding to this header
        const Device* device = deviceDataDispatcherFindDevice(header, bufferSize, DEVICE_MODE_OUTPUT);

        // if the device was not found, we continue
        if (device == NULL) {
            writeError(DEVICE_NOT_FOUND);
            OutputStream* errorOutputStream = getErrorOutputStreamLogger();
            appendString(errorOutputStream, "header=");
            append(errorOutputStream, header);
            appendStringAndDec(errorOutputStream, ",bufSize=", bufferSize);
            appendString(errorOutputStream, ",content=");
            copyInputToOutputStream(inputStream, errorOutputStream, NULL, COPY_ALL);

            return FALSE;
        }

        deviceHandleCallbackRawDataFunction* callbackFunction = device->deviceHandleCallbackRawData;

        if (callbackFunction != NULL) {
            // do the callback
            callbackFunction(device, header, inputStream);
            return TRUE;
        } else {
            writeError(DISPATCHER_NO_CALLBACK_FOR);
            append(getErrorOutputStreamLogger(), header);
        }
    }

    return FALSE;
}
