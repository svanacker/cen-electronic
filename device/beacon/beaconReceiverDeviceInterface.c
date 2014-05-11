#include "beaconReceiverDeviceInterface.h"
#include "commonBeaconDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* beaconReceiverDeviceGetName() {
    return "beaconReceiver";
}

int beaconReceiverDeviceGetInterface(char commandHeader, int mode,
        bool fillDeviceArgumentList) {
	// getOpponentRobotPos
    if (commandHeader == COMMAND_GET_OPPONENT_ROBOT_POSITION) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("getOpponentRobotPos");
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getOpponentRobotPos", 3);
				setArgumentUnsignedHex4(0, "x(mm)");
				setArgumentSeparator(1);
				setArgumentUnsignedHex4(2, "y(mm)");
            }
            return 9;
        }
    }
	// setOpponentRobotPos
    if (commandHeader == COMMAND_SET_OPPONENT_ROBOT_POSITION_FROM_LASER_TO_RECEIVER) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setOpponentRobotPos", 3);
				setArgumentUnsignedHex4(0, "x(mm)");
				setArgumentSeparator(1);
				setArgumentUnsignedHex4(2, "y(mm)");
            }
            return 9;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setOpponentRobotPos");
            }
            return 0;
        }
    }
	// init Router
    else if (commandHeader == COMMAND_INIT_JENNIC_AS_ROUTER) {
		// same output / input
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("initJennicAsRouter");
		}
		return 0;
    }
	// Network status
	else if (commandHeader == COMMANG_GET_RECEIVER_NETWORK_STATUS) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("getReceiverNetworkStatus");
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getReceiverNetworkStatus", 1);
				setArgumentUnsignedHex4(0, "status");
            }
            return 2;
        }
	}
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = BEACON_RECEIVER_DEVICE_HEADER,
    .deviceGetName = &beaconReceiverDeviceGetName,
    .deviceGetInterface = &beaconReceiverDeviceGetInterface
};

DeviceInterface* getBeaconReceiverDeviceInterface() {
    return &deviceInterface;
}
