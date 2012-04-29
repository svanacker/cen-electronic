#include <stdlib.h>

#include "device.h"
#include "deviceInterface.h"

#include "../common/commons.h"
#include "../common/delay/delay30F.h"

#include "../common/io/ioUtils.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/log/logger.h"

/**
 * Init the device with the information given by deviceDescriptor.
 * We write the debug information to the serial interface, and if possible to an LCD drivers
 * @param device the device.
 */
BOOL initDevice(const Device* device) {
    int result = TRUE;
    DeviceDescriptor* deviceDescriptor = device->descriptor;
    DeviceInterface* deviceInterface = device->interface;

    const char* deviceName = deviceInterface->deviceGetName();
    OutputStream* logStream = getDebugOutputStreamLogger();

    appendString(logStream, deviceName);
    append(logStream, ':');

    if (deviceDescriptor != NULL) {
        deviceDescriptor->deviceInit();

        int result = deviceDescriptor->deviceIsOk();

        if (result) {
            appendString(logStream, "OK");
        } else {
            appendString(logStream, "KO");
        }
    }

    unsigned int version = deviceInterface->deviceGetSoftwareRevision();
    append(logStream, '(');
    appendDec(logStream, version);
    append(logStream, ')');

    println(logStream);

    return result;
}

void stopDevice(const Device* device) {
    DeviceDescriptor* deviceDescriptor = device->descriptor;
    if (deviceDescriptor != NULL) {
        deviceDescriptor->deviceShutDown();
    }
}

void forwardCallbackRawDataTo(InputStream* inputStream,
        OutputStream* outputStream,
        const Device* device,
        int header) {
    DeviceInterface* deviceInterface = device->interface;
    // Length = data of output from the message and add the length of message (1)
    int dataLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_OUTPUT, FALSE) + 1;

    copyInputToOutputStream(inputStream, outputStream, NULL, dataLength);
}
