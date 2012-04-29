#include "servoDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceServoGetName() {
    return "servo";
}

unsigned int deviceServoGetSoftwareRevision() {
    return 1;
}

int deviceServoGetInterface(char header, int mode, BOOL fillDeviceArgumentList ) {
    if (mode == DEVICE_MODE_INPUT) {
        if (header == COMMAND_SERVO) {
            if (fillDeviceArgumentList) {
				setFunction("updateServo", 3);
				setArgumentUnsignedHex2(0, "ServoIdx");
				setArgumentUnsignedHex2(1, "speed");
				setArgumentUnsignedHex4(2, "value");
            }
            return 8;
        }
    } else if (mode == DEVICE_MODE_OUTPUT) {
        if (header == COMMAND_SERVO) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("updateServo");
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceServoGetName,
    .deviceGetSoftwareRevision = &deviceServoGetSoftwareRevision,
    .deviceGetInterface = &deviceServoGetInterface
};

DeviceInterface* getServoDeviceInterface() {
    return &deviceInterface;
}
