#include <stdlib.h>

#include "deviceDataDispatcher.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

unsigned int getWaitedDataLength(const char header) {
    int size = getDeviceCount();
    int i;
    for (i = 0; i < size; i++) {
        Device* result = getDevice(i);
        DeviceInterface* interface = result->interface;
        int deviceDataLength = interface->deviceGetInterface(header, DEVICE_MODE_INPUT, FALSE);
        return deviceDataLength;
    }
    return -1;
}

const Device* deviceDataDispatcherFindDevice(const char header, int dataLength, int mode) {
    int i;
    int size = getDeviceCount();
    for (i = 0; i < size; i++) {
        Device* result = getDevice(i);
        DeviceInterface* interface = result->interface;
        int deviceDataLength = interface->deviceGetInterface(header, mode, FALSE);
        if (deviceDataLength == DEVICE_HEADER_NOT_HANDLED) {
			continue;
		}
        // if dataLength in the buffer has more data than
        // deviceDataLength = data - 1 (1 = size of header)
		if (dataLength > deviceDataLength) {
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
