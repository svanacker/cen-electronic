#include "strategyDeviceInterface.h"

#include "../../common/commons.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getStrategyDeviceName(void) {
    return "Strategy";
}

int deviceStrategyGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
	// Robot opponent position
    if (commandHeader == COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION) {
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
	else if (commandHeader == COMMAND_STRATEGY_SET_CONFIG) {
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
	else if (commandHeader == COMMAND_STRATEGY_PRINT_GAME_BOARD) {
		// same input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("printGameBoard");
		}
		return 0;
	}
	// Next step
	else if (commandHeader == COMMAND_STRATEGY_NEXT_STEP) {
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
	// Notify position
    else if (commandHeader == COMMAND_STRATEGY_SET_ROBOT_POSITION) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("strategySetRobotPosition", 7);
				setArgumentUnsignedHex2(0, "status");
				setArgumentSeparator(1);
				setArgumentUnsignedHex4(2, "x(mm)");
				setArgumentSeparator(3);
				setArgumentUnsignedHex4(4, "y(mm)");
				setArgumentSeparator(5);
				setArgumentUnsignedHex4(6, "ang(1/10)deg");
            }
            return 17;
        }
		else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("strategySetRobotPosition");
            }
            return 0;
		}
	}	
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = STRATEGY_DEVICE_HEADER,
    .deviceGetName = &getStrategyDeviceName,
    .deviceGetInterface = &deviceStrategyGetInterface
};

DeviceInterface* getStrategyDeviceInterface() {
    return &deviceInterface;
}
