#include <stdlib.h>

#include "device.h"
#include "deviceInterface.h"

#include "../common/commons.h"

#include "../common/io/ioUtils.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/log/logger.h"

bool initDevice(const Device* device) {
    int result = true;
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
        const char header,
        int mode) {
    DeviceInterface* deviceInterface = device->interface;
    // Length = data of output from the message and add the length of header message (deviceHeader + commandHeader)
    int dataLength = deviceInterface->deviceGetInterface(header, mode, false) + DEVICE_AND_COMMAND_HEADER_LENGTH;

    copyInputToOutputStream(inputStream, outputStream, NULL, dataLength);
}

void ackCommand(OutputStream* outputStream, const char deviceHeader, const char commandHeader) {
    appendAck(outputStream);
    append(outputStream, deviceHeader);
    append(outputStream, commandHeader);
}
