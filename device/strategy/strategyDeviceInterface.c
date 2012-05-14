#include "strategyDeviceInterface.h"

#include "../../common/commons.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getStrategyDeviceName(void) {
    return "Strategy";
}

unsigned int getStrategyVersion(void) {
    return 1;
}

int deviceStrategyGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
	// Robot opponent position
    if (header == COMMAND_SET_OPPONENT_ROBOT_POSITION) {
		if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setOpponentRobotPos", 3);
				setArgumentUnsignedHex4(0, "x (mm)");
				setArgumentSeparator(1);
				setArgumentUnsignedHex4(2, "y (mm)");
            }
            return 9;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setOpponentRobotPos");
            }
            return 0;
        }
	}
	// Config
	else if (header == COMMAND_SET_CONFIG) {
		if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setConfig", 1);
				setArgumentUnsignedHex4(0, "config");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setConfig");
            }
            return 0;
        }
	}
	// Print Gameboard
	else if (header == COMMAND_PRINT_GAME_BOARD) {
		// same input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("printGameBoard");
		}
		return 0;
	}
	// Next step
	else if (header == COMMAND_NEXT_STEP) {
		if (mode == DEVICE_MODE_INPUT) {
			// same input/output
			if (fillDeviceArgumentList) {
				setFunctionNoArgument("nextStep");
			}
			return 0;
		} else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("nextStep", 1);
				setArgumentUnsignedHex2(0, "status");
            }
            return 2;
        }
		
	}
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getStrategyDeviceName,
//    .deviceGetSoftwareRevision = &getStrategyVersion,
    .deviceGetInterface = &deviceStrategyGetInterface
};

DeviceInterface* getStrategyDeviceInterface() {
    return &deviceInterface;
}
