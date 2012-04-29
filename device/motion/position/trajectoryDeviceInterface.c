#include "trajectoryDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"

static char* GET_ABS_POS_STRING = "getAbsPos";
static char* GET_DEBUG_ABS_POS_STRING = "getDbgAbsPos";
static char* SET_ABS_POS_STRING = "setAbsPos";
static char* ANGLE_1_10_DEG = "angle(1/10)deg";
static char* X_MM = "x(mm)";
static char* Y_MM = "y(mm)";

const char* getTrajectoryDeviceName(void) {
    return "Trajectory";
}

unsigned int getTrajectorySoftwareRevision(void) {
    return 1;
}

void fillAbsolutePosition() {
	setArgumentUnsignedHex4(0, X_MM);
	setArgumentSeparator(1);
	setArgumentUnsignedHex4(2, Y_MM);
	setArgumentSeparator(3);
	setArgumentUnsignedHex4(4, ANGLE_1_10_DEG);
}

int trajectoryGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (header == COMMAND_GET_ABSOLUTE_POSITION) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument(GET_ABS_POS_STRING);
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
                setFunction(GET_ABS_POS_STRING, 5);
				fillAbsolutePosition();
            }
            return 14;
        }
    } else if (header == COMMAND_DEBUG_GET_ABSOLUTE_POSITION) {
		// Same return in case of input / output
        if (fillDeviceArgumentList) {
			setFunctionNoArgument(GET_DEBUG_ABS_POS_STRING);
        }
        return 0;
    } else if (header == COMMAND_SET_ABSOLUTE_POSITION) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction(SET_ABS_POS_STRING, 5);
				fillAbsolutePosition();
            }
            return 14;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument(SET_ABS_POS_STRING);
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getTrajectoryDeviceName,
    .deviceGetSoftwareRevision = &getTrajectorySoftwareRevision,
    .deviceGetInterface = &trajectoryGetInterface
};

DeviceInterface* getTrajectoryDeviceInterface() {
    return &deviceInterface;
}
