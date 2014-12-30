#include "beaconReceiverDeviceInterface.h"
#include "commonBeaconDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* beaconReceiverDeviceGetName(void) {
    return "beaconReceiver";
}

int beaconReceiverDeviceGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // getOpponentRobotPos
    if (commandHeader == COMMAND_GET_OPPONENT_ROBOT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("getOpponentRobotPos", 0, 3);
            setResultUnsignedHex4(0, "x(mm)");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "y(mm)");
        }
        return commandLengthValueForMode(mode, 0, 9);
    }
    // setOpponentRobotPos
    else if (commandHeader == COMMAND_SET_OPPONENT_ROBOT_POSITION_FROM_LASER_TO_RECEIVER) {
        if (fillDeviceArgumentList) {
            setFunction("setOpponentRobotPos", 3, 0);
            setArgumentUnsignedHex4(0, "x(mm)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "y(mm)");
        }
        return commandLengthValueForMode(mode, 9, 0);
    }
    // init Router
    else if (commandHeader == COMMAND_INIT_JENNIC_AS_ROUTER) {
        // same output / input
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("initJennicAsRouter");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Network status
    else if (commandHeader == COMMAND_GET_RECEIVER_NETWORK_STATUS) {
        if (fillDeviceArgumentList) {
            setFunction("getReceiverNetworkStatus", 0, 1);
            setResultUnsignedHex4(0, "status");
        }
        return commandLengthValueForMode(mode, 0, 2);
     }   
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = BEACON_RECEIVER_DEVICE_HEADER,
    .deviceGetName = &beaconReceiverDeviceGetName,
    .deviceGetInterface = &beaconReceiverDeviceGetInterface
};

DeviceInterface* getBeaconReceiverDeviceInterface(void) {
    return &deviceInterface;
}
