#include "strategyDeviceInterface.h"

#include "../../common/commons.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getStrategyDeviceName(void) {
    return "STRATEGY";
}

unsigned int getStrategyVersion(void) {
    return 1;
}

int deviceStrategyGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getStrategyDeviceName,
    .deviceGetSoftwareRevision = &getStrategyVersion,
    .deviceGetInterface = &deviceStrategyGetInterface
};

DeviceInterface* getStrategyDeviceInterface() {
    return &deviceInterface;
}
