#include "pwmMotorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getPwmMotorDeviceName(void) {
    return "PWM_MOTOR";
}

unsigned int getPwmMotorVersion(void) {
    return 1;
}

int deviceMotorGetInterface(char header, int mode,
        BOOL fillDeviceArgumentList) {
    if (header == COMMAND_MOVE_MOTOR) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("runMotor", 2);
				setArgumentSignedHex2(0, "left");
				setArgumentSignedHex2(1, "right");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("motor");
            }
            return 0;
        }
    } else if (header == COMMAND_STOP_MOTOR) {
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("stopMotor");
        }
        return 0;
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getPwmMotorDeviceName,
//    .deviceGetSoftwareRevision = &getPwmMotorVersion,
    .deviceGetInterface = &deviceMotorGetInterface
};

DeviceInterface* getMotorDeviceInterface() {
    return &deviceInterface;
}
