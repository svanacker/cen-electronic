#include "deviceDescriptor.h"

#include "../common/error/error.h"

bool isDeviceDescriptorInitializedProperly(DeviceDescriptor* deviceDescriptor) {
    return deviceDescriptor->initErrorCode != ERROR_NONE;
}