#include "pwmMotorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getPwmMotorDeviceName(void) {
    return "PWM_MOTOR";
}

int deviceMotorGetInterface(char header, int mode,
        bool fillDeviceArgumentList) {
    if (header == COMMAND_MOVE_MOTOR) {
        if (fillDeviceArgumentList) {
			setFunction("runMotor", 2, 0);
			setArgumentSignedHex2(0, "left");
			setArgumentSignedHex2(1, "right");
        }
        return commandLengthValueForMode(mode, 4, 0);
    } else if (header == COMMAND_STOP_MOTOR) {
        if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("stopMotor");
        }
        return 0;
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = MOTOR_DEVICE_HEADER,
    .deviceGetName = &getPwmMotorDeviceName,
    .deviceGetInterface = &deviceMotorGetInterface
};

DeviceInterface* getMotorDeviceInterface() {
    return &deviceInterface;
}
