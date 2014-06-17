#include "servoDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceServoGetName() {
    return "servo";
}

int deviceServoGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList ) {
	// WRITE FUNCTIONS
    if (commandHeader == SERVO_COMMAND_WRITE) {
    	if (fillDeviceArgumentList) {
			setFunction("updateServoAllParams", 3, 0);
			setArgumentUnsignedHex2(0, "ServoIdx");
			setArgumentUnsignedHex2(1, "speed");
			setArgumentUnsignedHex4(2, "value");
		}
        return commandLengthValueForMode(mode, 8, 0);
	}
	else if (commandHeader == SERVO_COMMAND_WRITE_COMPACT) {
    	if (fillDeviceArgumentList) {
			setFunction("updateServoCompact", 1, 0);
			setArgumentUnsignedHex4(0, "value");
		}
        return commandLengthValueForMode(mode, 4, 0);
	}
	// READ_FUNCTIONS
	else if (commandHeader == SERVO_COMMAND_READ_SPEED) {
        if (fillDeviceArgumentList) {
			setFunction("servoReadSpeed", 1, 1);
			setArgumentUnsignedHex2(0, "ServoIdx");
			setResultUnsignedHex4(0, "Speed");
		}
		return commandLengthValueForMode(mode, 2, 4);
	}
	else if (commandHeader == SERVO_COMMAND_READ_CURRENT_POSITION) {
		if (fillDeviceArgumentList) {
			setFunction("servoReadCurrentPosition", 1, 1);
			setArgumentUnsignedHex2(0, "ServoIdx");
			setResultUnsignedHex4(0, "Current Position");
        }
        return commandLengthValueForMode(mode, 2, 4);
	}
	else if (commandHeader == SERVO_COMMAND_READ_TARGET_POSITION) {
        if (fillDeviceArgumentList) {
			setFunction("servoReadTargetPosition", 1, 1);
			setArgumentUnsignedHex2(0, "ServoIdx");
			setResultUnsignedHex4(0, "Target Position");
        }
        return commandLengthValueForMode(mode, 2, 4);
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
