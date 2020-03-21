#include "deviceDescriptor.h"

#include "../common/error/error.h"

bool isDeviceDescriptorInitializedProperly(DeviceDescriptor* deviceDescriptor) {
    return deviceDescriptor->initErrorCode != ERROR_NONE;
}

void initDeviceDescriptor(DeviceDescriptor* deviceDescriptor,
        deviceInitFunction *deviceInit,
        deviceShutDownFunction *deviceShutDown,
        deviceIsOkFunction *deviceIsOk,
        deviceHandleRawDataFunction *deviceHandleRawData,
        int* object) {
    deviceDescriptor->deviceInit = deviceInit;
    deviceDescriptor->deviceShutDown = deviceShutDown;
    deviceDescriptor->deviceIsOk = deviceIsOk;
    deviceDescriptor->deviceHandleRawData = deviceHandleRawData;
    deviceDescriptor->object = object;
}