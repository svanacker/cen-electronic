#include "laserBeaconDeviceInterface.h"
#include "commonBeaconDeviceInterface.h"

#include "../../device/deviceInterface.h"

unsigned int deviceBeaconGetSoftwareRevision() {
    return 1;
}

const char* deviceBeaconGetName() {
    return "Laser Beacon";
}

int deviceBeaconGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
	if (header == COMMAND_INIT_JENNIC_AS_COORDINATER) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("InitJennicAsCoordinater");
		}
		return 0;
	}
	else if (header == COMMAND_SEND_ROBOT_POSITION_FROM_COORDINATER_TO_ROUTER) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("sendRobotPositionFromCoordinaterToRouter");
		}
		return 0;
	}
    else if (header == COMMAND_BEACON_POSITION) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("robotPosition");
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("robotPosition", 3);
				setArgumentUnsignedHex4(0, "x (mm)");
				setArgumentSeparator(1);
				setArgumentUnsignedHex4(2, "y (mm)");
            }
            return 9;
        }
    }
	// Show the configuration of the both laser and general configuration
    else if (header == COMMAND_BEACON_CONFIGURATION) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("beaconConfiguration");
		}
        return 0;
    }
	// Set the configuration to define distance between beacon, and position
	// of point calibration
	else if (header == COMMAND_BEACON_SET_CONFIGURATION) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setBeaconConfiguration", 5);
				setArgumentUnsignedHex4(0, "distanceBetweenBeacon(mm)");
				setArgumentSeparator(1);
				setArgumentUnsignedHex4(2, "calibration->x");
				setArgumentSeparator(3);
				setArgumentUnsignedHex4(4, "calibration->y");
            }
            return 14;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setBeaconConfiguration");
            }
            return 0;
        }
	}
    else if (header == COMMAND_BEACON_CALIBRATION) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("beaconCalibration");
		}
        return 0;
    }
	else if (header == COMMAND_ROUTER_LIGHT) {
       if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("routerLight", 1);
				setArgumentUnsignedHex2(0, "on/off");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("routerLight");
            }
            return 0;
        }
		return 0;
	}
	else if (header == COMMAND_BEACON_SERVO_RUN) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("beaconServoRun");
		}
		return 0;
	}
	else if (header == COMMAND_BEACON_SERVO_STOP) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("beaconServoStop");
		}
		return 0;
	}
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceBeaconGetName,
//    .deviceGetSoftwareRevision = &deviceBeaconGetSoftwareRevision,
    .deviceGetInterface = &deviceBeaconGetInterface
};

DeviceInterface* getLaserBeaconDeviceInterface() {
    return &deviceInterface;
}
