#include <stdbool.h>

#include "colorDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceColorSensorGetName(void) {
    return "COLOR SENSOR";
}

int deviceColorSensorGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_COLOR_SENSOR_READ) {
        if (fillDeviceArgumentList) {
            setFunction("read Color Sensor", 0, 5);
            setResultUnsignedHex4(0, "R");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "G");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "B");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }
    else if (commandHeader == COMMAND_COLOR_SENSOR_READ_TYPE) {
        if (fillDeviceArgumentList) {
            setFunction("Read Color Type", 0, 1);
            setResultUnsignedHex2(0, "Red=0, Green=2, Orange=3, Blue=4...");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    else if (commandHeader == COMMAND_COLOR_SENSOR_WRITE) {
        if (fillDeviceArgumentList) {
            setFunction("write Color Sensor", 5, 0);
            setArgumentUnsignedHex4(0, "R");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "G");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "B");
        }
        return commandLengthValueForMode(mode, 14, 0);
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
