#include "motionDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"

unsigned int deviceMotionGetSoftwareRevision() {
    return 1;
}

const char* deviceMotionGetName() {
    return "motion";
}

void fillSplineParameters() {
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

int deviceMotionGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    // goto
    if (header == COMMAND_MOTION_GOTO_IN_PULSE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("gotoPulse", 4);
				setArgumentUnsignedHex4(0, "left");
				setArgumentUnsignedHex4(1, "right");
				setArgumentUnsignedHex2(2, "a");
				setArgumentUnsignedHex2(3, "s");
            }
            return 16;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("gotoPulse");
            }
            return 0;
        }
    }// forward MM
    else if (header == COMMAND_MOTION_FORWARD_IN_MM) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("forwardMM", 1);
				setArgumentUnsignedHex4(0, "distMM");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("forwardMM");
            }
            return 0;
        }
    }// backward MM
    else if (header == COMMAND_MOTION_BACKWARD_IN_MM) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("backwardMM", 1);
				setArgumentUnsignedHex4(0, "distMM");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("backwardMM");
            }
            return 0;
        }
    }// turn left in degree
    else if (header == COMMAND_MOTION_LEFT_IN_DECI_DEGREE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("rotLeftDecDeg", 1);
				setArgumentUnsignedHex4(0, "leftAngleDecDeg");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("rotLeftDecDeg");
            }
            return 0;
        }
    }// turn right in degree
    else if (header == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("rotRightDecDeg", 1);
				setArgumentUnsignedHex4(0, "rightAngleDecDeg");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("rotRightDecDeg");
            }
            return 0;
        }
    }// ONLY ONE WHEEL
        // turn left (only right in degree
    else if (header == COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("rotLeft1WheelDecDeg", 1);
				setArgumentUnsignedHex4(0, "leftAngleDecDeg");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("rotLeft1WheelDecDeg");
            }
            return 0;
        }
    }// turn right (only right wheel) in degree
    else if (header == COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("rotRight1WheelDecDeg", 1);
				setArgumentUnsignedHex4(0, "rightAngleDecDeg");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("rotRightDecDeg");
            }
            return 0;
        }
    }// B-Spline with relative spline
    else if (header == COMMAND_MOTION_SPLINE_RELATIVE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("bSplineRel", 12);
				fillSplineParameters();
            }
            return 23;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("bSplineRel");
            }
            return 0;
        }
    }// B-Spline with absolute spline
    else if (header == COMMAND_MOTION_SPLINE_ABSOLUTE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("bSplineAbs", 12);
				fillSplineParameters();
            }
            return 23;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("bSplineRel");
            }
            return 0;
        }
    } // BSpline : test
    else if (header == COMMAND_MOTION_SPLINE_TEST_LEFT) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("bSplineTestLeft");
        }
        return 0;
    } 
    else if (header == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("bSplineTestRight");
        }
        return 0;
    }
	// motion : Cancel
	else if (header == COMMAND_MOTION_CANCEL) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("cancelMot");
        }
        return 0;
    }// motion : Obstacle
    else if (header == COMMAND_MOTION_OBSTACLE) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("motionObstacle");
        }
        return 0;
    }// Calibration
    else if (header == COMMAND_SQUARE_CALIBRATION) {
        if (mode == DEVICE_MODE_INPUT) {
	        if (fillDeviceArgumentList) {
				setFunction("squareCalib", 2);
				setArgumentUnsignedHex2(0, "l/r");
				setArgumentUnsignedHex4(1, "length");
            }
			return 6;
		 }
		 else if (mode == DEVICE_MODE_OUTPUT) {
			if (fillDeviceArgumentList) {
				setFunctionNoArgument("squareCalib");
			}
			return 0;
		}
    }// Parameters
    else if (header == COMMAND_GET_MOTION_PARAMETERS) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getMotionParam", 1);
				setArgumentUnsignedHex2(0, "motionType");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getMotionParam", 2);
				setArgumentUnsignedHex2(0, "a");
				setArgumentUnsignedHex2(1, "s");
            }
            return 4;
        }
    } else if (header == COMMAND_SET_MOTION_PARAMETERS) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setMotionParam", 3);
				setArgumentUnsignedHex2(0, "motionType");
				setArgumentUnsignedHex2(1, "a");
				setArgumentUnsignedHex2(2, "s");
           }
            return 6;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setMotionParam");
            }
            return 0;
        }
    } else if (header == NOTIFY_MOTION_STATUS) {
        if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("motionStatus", 7);
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
        // Mode is only output because it's only notification
		// but used to reset if needed
		else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("motionStatus");
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceMotionGetName,
//    .deviceGetSoftwareRevision = &deviceMotionGetSoftwareRevision,
    .deviceGetInterface = &deviceMotionGetInterface
};

DeviceInterface* getMotionDeviceInterface() {
    return &deviceInterface;
}
