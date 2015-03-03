#include <stdbool.h>
#include <stdlib.h>

#include "dataDispatcherDeviceDriver.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/deviceConstants.h"
#include "../../device/system/systemDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"
#include "../../drivers/driverStreamListener.h"

bool pingDriverDataDispatcher(unsigned char dispatcherIndex) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

	// To Select the dispatcher
    append(outputStream, DATA_DISPATCHER_DEVICE_HEADER);
    appendHex2(outputStream, dispatcherIndex);

	// To check if it's not another board which replies ...
	append(outputStream, SYSTEM_DEVICE_HEADER);
    append(outputStream, COMMAND_PING);
    appendHex2(outputStream, dispatcherIndex);

    // We do exactly as if the data was written by a end-user
    // requestBuffer must be filled before calling this method
    Buffer* requestBuffer = getDriverRequestBuffer();
    Buffer* responseBuffer = getDriverResponseBuffer();

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

    if (result) {
        readHex(inputStream); // ack
        readHex(inputStream); // deviceHeader
        readHex(inputStream); // commandHeader
        int realDispatcherIndex = readHex2(inputStream);
        return (dispatcherIndex == realDispatcherIndex);
    }
    return false;
}

bool pingDriverDataDispatcherList() {
    bool result = true;
    int size = getDriverDataDispatcherCount();
    int i;
    for (i = 0; i < size; i++) {
        bool pingOk = pingDriverDataDispatcher(i);

        // Note if only one of them does not ping
        if (!pingOk) {
            result = false;
        }

    }
    return result;
}