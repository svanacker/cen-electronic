#include <stdlib.h>

#include "deviceDataDispatcher.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

unsigned int getWaitedDataLength(const char deviceHeader) {
    int size = getDeviceCount();
    int i;
    for (i = 0; i < size; i++) {
        Device* result = getDevice(i);
		DeviceInterface* interface = result->deviceInterface;
        int deviceDataLength = interface->deviceGetInterface(deviceHeader, DEVICE_MODE_INPUT, false);
        return deviceDataLength;
    }
    return -1;
}

const Device* deviceDataDispatcherFindDevice(const char deviceHeader, const char commandHeader, int dataLength, int mode) {
    int i;
    int size = getDeviceCount();
    for (i = 0; i < size; i++) {
        Device* result = getDevice(i);
		DeviceInterface* interface = result->deviceInterface;
        char deviceInterfaceHeader = interface->deviceHeader;
        // check if this is the right device
        if (deviceHeader != deviceInterfaceHeader) {
            continue;
        }

        int deviceDataLength = interface->deviceGetInterface(commandHeader, mode, false);
        if (deviceDataLength == DEVICE_HEADER_NOT_HANDLED) {
            continue;
        }
        // if dataLength in the buffer has more data than
        // deviceDataLength = data - 2 (2 = size of device header + size of command header)
        if (dataLength >= deviceDataLength - DEVICE_AND_COMMAND_HEADER_LENGTH) {
            return result;
        }
        else {
            /*
            // dataLength is not enough : we can return IMMEDIATELY
            appendStringAndDec(getOutputStreamLogger(WARNING), "header=", header);
            appendStringAndDec(getOutputStreamLogger(WARNING), "dataLength=", dataLength);
            appendStringAndDec(getOutputStreamLogger(WARNING), ", deviceDataLength=", deviceDataLength);
            println(getOutputStreamLogger(WARNING));
            */
            return NULL;
        }
    }
    return NULL;
}
