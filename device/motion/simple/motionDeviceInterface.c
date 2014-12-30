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

void fillSplineParameters(void) {
	// X3/Y3 as absolute position
	setArgumentUnsignedHex4(0, "x3(mm)");
	setArgumentSeparator(1);
	setArgumentUnsignedHex4(2, "y3(mm)");
	setArgumentSeparator(3);
	setArgumentUnsignedHex4(4, "finalAngDecDeg");
	setArgumentSeparator(5);
	setArgumentSignedHex2(6, "distP0-P1(cm)");
	setArgumentSeparator(7);
	setArgumentSignedHex2(8, "distP2-P3(cm)");
	setArgumentSeparator(9);
	setArgumentUnsignedChar1(10, "speedFactor");
	setArgumentUnsignedChar1(11, "accFactor");
}

int deviceMotionGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // goto
    if (commandHeader == COMMAND_MOTION_GOTO_IN_PULSE) {
        if (fillDeviceArgumentList) {
            setFunction("gotoPulse", 4, 0);
            setArgument(0, DEVICE_ARG_SIGNED_HEX_6, "left");
            setArgument(1, DEVICE_ARG_SIGNED_HEX_6, "right");
            setArgumentUnsignedHex2(2, "a");
            setArgumentUnsignedHex2(3, "s");
        }
        return commandLengthValueForMode(mode, 16, 0);
    }// forward MM
    else if (commandHeader == COMMAND_MOTION_FORWARD_IN_MM) {
        if (fillDeviceArgumentList) {
            setFunction("forwardMM", 1, 0);
            setArgumentUnsignedHex4(0, "distMM");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// backward MM
    else if (commandHeader == COMMAND_MOTION_BACKWARD_IN_MM) {
        if (fillDeviceArgumentList) {
            setFunction("backwardMM", 1, 0);
            setArgumentUnsignedHex4(0, "distMM");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn left in degree
    else if (commandHeader == COMMAND_MOTION_LEFT_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotLeftDecDeg", 1, 0);
            setArgumentUnsignedHex4(0, "leftAngleDecDeg");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn right in degree
    else if (commandHeader == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotRightDecDeg", 1, 0);
            setArgumentUnsignedHex4(0, "rightAngleDecDeg");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// ONLY ONE WHEEL
        // turn left (only right in degree
    else if (commandHeader == COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotLeft1WheelDecDeg", 1, 0);
            setArgumentUnsignedHex4(0, "leftAngleDecDeg");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn right (only right wheel) in degree
    else if (commandHeader == COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotRight1WheelDecDeg", 1, 0);
            setArgumentUnsignedHex4(0, "rightAngleDecDeg");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// B-Spline with relative spline
    else if (commandHeader == COMMAND_MOTION_SPLINE_RELATIVE) {
        if (fillDeviceArgumentList) {
            setFunction("bSplineRel", 12, 0);
            fillSplineParameters();
        }
        return commandLengthValueForMode(mode, 23, 0);
    }// B-Spline with absolute spline
    else if (commandHeader == COMMAND_MOTION_SPLINE_ABSOLUTE) {
        if (fillDeviceArgumentList) {
            setFunction("bSplineAbs", 12, 0);
            fillSplineParameters();
        }
        return commandLengthValueForMode(mode, 23, 0);
    } // BSpline : test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_LEFT) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSplineTestLeft");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } 
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSplineTestRight");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // motion : Cancel
    else if (commandHeader == COMMAND_MOTION_CANCEL) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("cancelMot");
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
            setFunction("squareCalib", 2, 0);
            setArgumentUnsignedHex2(0, "l/r");
            setArgumentUnsignedHex4(1, "length");
        }
        return commandLengthValueForMode(mode, 6, 0);
    }// Parameters
    else if (commandHeader == COMMAND_GET_MOTION_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("getMotionParam", 1, 2);
            setArgumentUnsignedHex2(0, "motionType");
            setResultUnsignedHex2(0, "a");
            setResultUnsignedHex2(1, "s");
        }
        return commandLengthValueForMode(mode, 2, 4);
    } else if (commandHeader == COMMAND_SET_MOTION_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("setMotionParam", 3, 0);
            setArgumentUnsignedHex2(0, "motionType");
            setArgumentUnsignedHex2(1, "a");
            setArgumentUnsignedHex2(2, "s");
        }
        return commandLengthValueForMode(mode, 6, 0);
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
