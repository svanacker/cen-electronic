#include <stdlib.h>

#include "deviceDataDispatcher.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

unsigned int getWaitedDataLength(const unsigned char deviceHeader) {
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

const Device* deviceDataDispatcherFindDevice(const unsigned char deviceHeader, const unsigned char commandHeader, const int dataLength, const DeviceInterfaceMode mode) {
    int i;
    int size = getDeviceCount();
    for (i = 0; i < size; i++) {
        Device* result = getDevice(i);
        DeviceInterface* interface = result->deviceInterface;
        unsigned char deviceInterfaceHeader = interface->deviceHeader;
        // check if this is the right device
        if (deviceHeader != deviceInterfaceHeader) {
            continue;
        }

        int expectedDeviceDataLength = interface->deviceGetInterface(commandHeader, mode, false);
        if (expectedDeviceDataLength == DEVICE_HEADER_NOT_HANDLED) {
            continue;
        }
        // if dataLength in the buffer has more data than
        // deviceDataLength = data + 2 (2 = size of device header + size of command header)
        if (dataLength >= expectedDeviceDataLength + DEVICE_AND_COMMAND_HEADER_LENGTH) {
            return result;
        } else {
            /*
            // dataLength is not enough : we can return IMMEDIATELY
            appendStringAndDec(getWarningOutputStreamLogger(), "header=", header);
            appendStringAndDec(getWarningOutputStreamLogger(), "dataLength=", dataLength);
            appendStringAndDec(getWarningOutputStreamLogger(), ", deviceDataLength=", deviceDataLength);
            println(getWarningOutputStreamLogger());
             */
            return NULL;
        }
    }
    return NULL;
}
