#include <stdbool.h>

#include "motionDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceMotionGetName(void) {
    return "motion";
}

void fillNotifyResults(char* notificationName) {
    setNotification(notificationName, 5);
    setArgumentUnsignedHex4(0, "x(mm)");
    setArgumentSeparator(1);
    setArgumentUnsignedHex4(2, "y(mm)");
    setArgumentSeparator(3);
    setArgumentUnsignedHex4(4, "ang(1/10)deg");
}

int deviceMotionGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // goto
    if (commandHeader == COMMAND_MOTION_GOTO_IN_PULSE) {
        if (fillDeviceArgumentList) {
            setFunction("gotoPulse", 4, 0);
            setArgument(0, DEVICE_ARG_SIGNED_HEX_6, "left (pulse)");
            setArgument(1, DEVICE_ARG_SIGNED_HEX_6, "right (pulse)");
            setArgumentUnsignedHex2(2, "a");
            setArgumentUnsignedHex2(3, "s");
        }
        return commandLengthValueForMode(mode, 16, 0);
    }// forward MM
    else if (commandHeader == COMMAND_MOTION_FORWARD_IN_MM) {
        if (fillDeviceArgumentList) {
            setFunction("forwardMM", 1, 0);
            setArgumentUnsignedHex4(0, "distance (MM)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// backward MM
    else if (commandHeader == COMMAND_MOTION_BACKWARD_IN_MM) {
        if (fillDeviceArgumentList) {
            setFunction("backwardMM", 1, 0);
            setArgumentUnsignedHex4(0, "distance (MM)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn left in degree
    else if (commandHeader == COMMAND_MOTION_LEFT_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Left DeciDeg", 1, 0);
            setArgumentUnsignedHex4(0, "leftAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn right in degree
    else if (commandHeader == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Right DeciDeg", 1, 0);
            setArgumentUnsignedHex4(0, "rightAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// ONLY ONE WHEEL
        // turn left (only right in degree
    else if (commandHeader == COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Left One Wheel DeciDeg", 1, 0);
            setArgumentUnsignedHex4(0, "leftAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn right (only right wheel) in degree
    else if (commandHeader == COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Right One Wheel DeciDeg", 1, 0);
            setArgumentUnsignedHex4(0, "rightAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    // motion : Cancel
    else if (commandHeader == COMMAND_MOTION_STOP) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("cancelMotion");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // motion : Cancel ALL
    else if (commandHeader == COMMAND_MOTION_CANCEL_ALL) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("cancelMotionAll");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// motion : Obstacle
    else if (commandHeader == COMMAND_MOTION_OBSTACLE) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("motionObstacle");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Calibration
    else if (commandHeader == COMMAND_SQUARE_CALIBRATION) {
        if (fillDeviceArgumentList) {
            setFunction("squareCalib", 3, 0);
            setArgumentUnsignedHex2(0, "left/right");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "length");
        }
        return commandLengthValueForMode(mode, 7, 0);
    }// Parameters
	// MODE REPLACE / ADD
	else if (commandHeader == COMMAND_MOTION_MODE_ADD) {
		if(fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("motionModeAdd");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
	else if (commandHeader == COMMAND_MOTION_MODE_REPLACE) {
		if(fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("motionModeReplace");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
	else if (commandHeader == COMMAND_MOTION_MODE_GET) {
		if (fillDeviceArgumentList) {
			setFunction("motionModeGet", 0, 1);
			setResultUnsignedChar1(0, "value");
		}
		return commandLengthValueForMode(mode, 0, 1);
	}
	// NOTIFICATION
    if (DEVICE_MODE_NOTIFY == mode) {
        if (commandHeader == NOTIFY_MOTION_STATUS_REACHED) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notifyReached");
            }
            return 14;
        }
        else if (commandHeader == NOTIFY_MOTION_STATUS_FAILED) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notifyFailed");
            }
            return 14;
        }
        else if (commandHeader == NOTIFY_MOTION_STATUS_OBSTACLE) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notifyObstacle");
            }
            return 14;
        }
        else if (commandHeader == NOTIFY_MOTION_STATUS_MOVING) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notifyMoving");
            }
            return 14;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = MOTION_DEVICE_HEADER,
    .deviceGetName = &deviceMotionGetName,
    .deviceGetInterface = &deviceMotionGetInterface
};

DeviceInterface* getMotionDeviceInterface(void) {
    return &deviceInterface;
}
