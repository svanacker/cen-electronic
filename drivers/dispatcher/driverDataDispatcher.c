#include <stdlib.h>
#include <stdbool.h>

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

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/transmitMode.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

#include "../../drivers/driver.h"

void transmitDriverData(TransmitMode transmitMode,
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
		append(errorOutputStream, '(');
		appendString(errorOutputStream, getTransmitModeAsString(transmitMode));
		append(errorOutputStream, ')');
        appendStringAndDec(errorOutputStream, ",addr=", address);
    }
}

bool handleNotificationFromDispatcher(DriverDataDispatcher* dispatcher) {
    InputStream* inputStream = dispatcher->inputStream;

    if (inputStream == NULL) {
        writeError(NO_DISPATCHER_INPUT_STREAM);
        return false;
    }

    if (inputStream->availableData(inputStream)) {

        // Get the underlying buffer
        Buffer* inputBuffer = (Buffer*) (inputStream->object);
        if (inputBuffer == NULL) {
            writeError(NO_DISPATCHER_INPUT_BUFFER);
        }
        int bufferSize = getBufferElementsCount(inputBuffer);

        if (bufferSize < DEVICE_AND_COMMAND_HEADER_LENGTH) {
            return false;
        }

        char deviceHeader = bufferGetCharAtIndex(inputBuffer, DEVICE_HEADER_INDEX);
		char notifyHeader = bufferGetCharAtIndex(inputBuffer, NOTIFY_HEADER_INDEX);

        // find the device corresponding to this header
        const Device* device = deviceDataDispatcherFindDevice(deviceHeader, notifyHeader, bufferSize, DEVICE_MODE_NOTIFY);
        if (device == NULL) {
            return false;
        }

		// Remove deviceHeader & notifyHeader
		bufferReadChar(inputBuffer);
		bufferReadChar(inputBuffer);

		deviceHandleNotificationFunction* notificationFunction = device->deviceHandleNotification;

        if (notificationFunction != NULL) {
            // do the callback
            notificationFunction(device, notifyHeader, inputStream);
            return true;
        } else {
            writeError(DISPATCHER_NO_CALLBACK_FOR_NOTIFICATION);
            append(getErrorOutputStreamLogger(), notifyHeader);
        }
    }

    return false;
}
