#include <stdlib.h>

#include "device.h"
#include "deviceInterface.h"
#include "deviceDescriptor.h"

#include "../common/io/ioUtils.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/log/logger.h"
#include "../common/error/error.h"

bool initDevice(const Device* device) {
    bool result = true;
    DeviceDescriptor* deviceDescriptor = device->descriptor;
    DeviceInterface* deviceInterface = device->deviceInterface;

    const char* deviceName = deviceInterface->deviceGetName();
    OutputStream* logStream = getInfoOutputStreamLogger();

    unsigned length = appendString(logStream, deviceName);
    appendSpaces(logStream, 18 - length);

    if (deviceDescriptor != NULL) {
        clearLastError();
        deviceDescriptor->deviceInit();

        result = deviceDescriptor->deviceIsOk();

        if (result) {
            appendString(logStream, "OK");
        }
        else {
            appendString(logStream, "KO (");
            appendDec(logStream, getLastError());
            append(logStream, ')');
        }
        deviceDescriptor->initErrorCode = getLastError();
    }
    // TODO : Manage when REMOTE ...
    println(logStream);

    return result;
}

void stopDevice(const Device* device) {
    DeviceDescriptor* deviceDescriptor = device->descriptor;
    if (deviceDescriptor != NULL) {
        deviceDescriptor->deviceShutDown();
    }
}

void ackCommand(OutputStream* outputStream, const unsigned char deviceHeader, const unsigned char commandHeader) {
    appendAck(outputStream);
    append(outputStream, deviceHeader);
    append(outputStream, commandHeader);
}
