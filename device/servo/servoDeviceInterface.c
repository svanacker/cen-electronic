#include "servoDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceServoGetName() {
    return "servo";
}

int deviceServoGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList ) {
    if (mode == DEVICE_MODE_INPUT) {
        if (commandHeader == INDEX_COMMAND_SERVO) {
            if (fillDeviceArgumentList) {
				setFunction("updateServoAllParams", 3);
				setArgumentUnsignedHex2(0, "ServoIdx");
				setArgumentUnsignedHex2(1, "speed");
				setArgumentUnsignedHex4(2, "value");
            }
            return 8;
        }
		else if (commandHeader == COMPACT_COMMAND_SERVO) {
            if (fillDeviceArgumentList) {
				setFunction("updateServoCompact", 1);
				setArgumentUnsignedHex4(0, "value");
            }
            return 4;
		}
    } else if (mode == DEVICE_MODE_OUTPUT) {
        if (commandHeader == INDEX_COMMAND_SERVO || commandHeader == COMPACT_COMMAND_SERVO) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("updateServoAllParams");
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = SERVO_DEVICE_HEADER,
    .deviceGetName = &deviceServoGetName,
    .deviceGetInterface = &deviceServoGetInterface
};

DeviceInterface* getServoDeviceInterface() {
    return &deviceInterface;
}
