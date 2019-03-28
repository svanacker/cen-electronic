#include <stdbool.h>

#include "currentSensorDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getCurrentSensorDeviceName(void) {
    return "Current Sensor";
}

int deviceCurrentSensorGetInterface(char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    if (header == COMMAND_READ_CURRENT_SENSOR ) {
        if (fillDeviceArgumentList) {
            setFunction("Current Sensor Read", 0, 2);
            setResultUnsignedHex4(0, "CURRENT");
        }
        return commandLengthValueForMode(mode, 0, 4);
    } else if (header == COMMAND_SET_CURRENT_SENSOR_ALERT) {
        if (fillDeviceArgumentList) {
            setFunction("Set Alert Current Sensor", 1, 0);
            setArgumentUnsignedHex2(0, "Alert Current");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = CURRENT_SENSOR_DEVICE_HEADER,
    .deviceGetName = &getCurrentSensorDeviceName,
    .deviceGetInterface = &deviceCurrentSensorGetInterface
};

DeviceInterface* getCurrentSensorDeviceInterface() {
    return &deviceInterface;
}
