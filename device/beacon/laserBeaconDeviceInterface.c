#include "laserBeaconDeviceInterface.h"
#include "commonBeaconDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

unsigned int deviceBeaconGetSoftwareRevision() {
    return 1;
}

const char* deviceBeaconGetName() {
    return "Laser Beacon";
}

int deviceBeaconGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_INIT_JENNIC_AS_COORDINATER) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("InitJennicAsCoordinater");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_SEND_ROBOT_POSITION_FROM_COORDINATER_TO_ROUTER) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("sendRobotPositionFromCoordinaterToRouter");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_BEACON_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("robotPosition", 0, 3);
            setResultUnsignedHex4(0, "x (mm)");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "y (mm)");
        }
        return commandLengthValueForMode(mode, 0, 9);
    }// Show the configuration of the both laser and general configuration
    else if (commandHeader == COMMAND_BEACON_CONFIGURATION) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("beaconConfiguration");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Set the configuration to define distance between beacon, and position
        // of point calibration
    else if (commandHeader == COMMAND_BEACON_SET_CONFIGURATION) {
        if (fillDeviceArgumentList) {
            setFunction("setBeaconConfiguration", 5, 0);
            setArgumentUnsignedHex4(0, "distanceBetweenBeacon(mm)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "calibration->x");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "calibration->y");
        }
        return commandLengthValueForMode(mode, 14, 0);
    } else if (commandHeader == COMMAND_BEACON_CALIBRATION) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("beaconCalibration");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_ROUTER_LIGHT) {
        if (fillDeviceArgumentList) {
            setFunction("routerLight", 1, 0);
            setArgumentUnsignedHex2(0, "on/off");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_BEACON_SERVO_RUN) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("beaconServoRun");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_BEACON_SERVO_STOP) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("beaconServoStop");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LASER_BEACON_DEVICE_HEADER,
    .deviceGetName = &deviceBeaconGetName,
    .deviceGetInterface = &deviceBeaconGetInterface
};

DeviceInterface* getLaserBeaconDeviceInterface() {
    return &deviceInterface;
}
