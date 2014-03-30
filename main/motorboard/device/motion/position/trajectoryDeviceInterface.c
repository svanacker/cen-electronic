#include "trajectoryDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"

#define GET_ABS_POS_STRING 			"getAbsPos"
#define GET_DEBUG_ABS_POS_STRING 	"getDbgAbsPos"
#define SET_ABS_POS_STRING 			"setAbsPos"
#define ANGLE_1_10_DEG 				"angle(1/10)deg"
#define X_MM 						"x(mm)"
#define Y_MM 						"y(mm)"

const char* getTrajectoryDeviceName(void) {
    return "Trajectory";
}

void fillAbsolutePosition() {
	setArgumentUnsignedHex4(0, X_MM);
	setArgumentSeparator(1);
	setArgumentUnsignedHex4(2, Y_MM);
	setArgumentSeparator(3);
	setArgumentUnsignedHex4(4, ANGLE_1_10_DEG);
}

int trajectoryGetInterface(char header, int mode, bool fillDeviceArgumentList) {
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
    .deviceGetInterface = &trajectoryGetInterface
};

DeviceInterface* getTrajectoryDeviceInterface() {
    return &deviceInterface;
}
