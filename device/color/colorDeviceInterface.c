#include <stdbool.h>

#include "colorDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceColorSensorGetName(void) {
    return "COLOR SENSOR";
}

int deviceColorSensorGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_COLOR_SENSOR_READ) {
        if (fillDeviceArgumentList) {
            setFunction("read Color Sensor", 1, 1);
            setResultUnsignedHex2(0, "R");
            setResultUnsignedHex2(1, "G");
            setResultUnsignedHex2(2, "B");
        }
        return commandLengthValueForMode(mode, 2, 1);
    }
    else if (commandHeader == COMMAND_COLOR_SENSOR_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug Color Sensor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = COLOR_SENSOR_DEVICE_HEADER,
    .deviceGetName = &deviceColorSensorGetName,
    .deviceGetInterface = &deviceColorSensorGetInterface
};

DeviceInterface* getColorSensorDeviceInterface(void) {
    return &deviceInterface;
}
