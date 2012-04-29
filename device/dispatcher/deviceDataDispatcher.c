#include <stdlib.h>

#include "deviceDataDispatcher.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceList.h"

unsigned int getWaitedDataLength(const char header) {
    int size = getDeviceCount();
    int i;
    for (i = 0; i < size; i++) {
        Device* result = getDevice(i);
        DeviceInterface* interface = result->interface;
        int deviceDataLength = interface->deviceGetInterface(header, DEVICE_MODE_INPUT, NULL);
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
        int deviceDataLength = interface->deviceGetInterface(header, mode, NULL);
        // if dataLength in the buffer has more data than
        // deviceDataLength = data - 1 (1 = size of header)
        if (deviceDataLength != -1 && dataLength > deviceDataLength) {
            return result;
        }
    }
    return NULL;
}
