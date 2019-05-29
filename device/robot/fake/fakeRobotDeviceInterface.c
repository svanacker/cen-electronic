#include <stdbool.h>

#include "fakeRobotDeviceInterface.h"

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceDebug.h"
#include "../../../device/deviceConstants.h"

const char* deviceFakeRobotGetName(void) {
    return "fakeRobot";
}

int deviceFakeRobotGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // Get the position
    if (commandHeader == COMMAND_FAKE_ROBOT_GET_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("Get Position", 0, 7);
            setResultUnsignedHex4(0, "x (mm)");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "y (mm)");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "angle (deci degree)");
            setResultSeparator(5);
            setResultUnsignedHex4(6, "radius (mm)");
        }
        return commandLengthValueForMode(mode, 0, 19);
    }
    else if (commandHeader == COMMAND_FAKE_ROBOT_SET_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("Set Position", 7, 0);
            setArgumentUnsignedHex4(0, "x (mm)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "y (mm)");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "angle (deci degree)");
            setArgumentSeparator(5);
            setArgumentUnsignedHex4(6, "radius (mm)");
        }
        return commandLengthValueForMode(mode, 19, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = FAKE_ROBOT_DEVICE_HEADER,
    .deviceGetName = &deviceFakeRobotGetName,
    .deviceGetInterface = &deviceFakeRobotGetInterface
};

DeviceInterface* getFakeRobotDeviceInterface(void) {
    return &deviceInterface;
}
