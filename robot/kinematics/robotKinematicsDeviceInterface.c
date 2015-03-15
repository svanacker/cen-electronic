#include "robotKinematicsDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getKinematicsDeviceName(void) {
    return "Kinematics";
}

int deviceRobotKinematicsGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("kinematicsLoadDefaultValues");
            setResultUnsignedHex6(0, "value");
        }
        return 0;
    }
    // Wheels Average Length (get/set)
    else if (commandHeader == COMMAND_GET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH) {
        if (fillDeviceArgumentList) {
            setFunction("getWheelsAverageLengthForOnePulse (nanometer)", 0, 1);
            setResultUnsignedHex6(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 6);
    }
    else if (commandHeader == COMMAND_SET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH) {
        if (fillDeviceArgumentList) {
            setFunction("setWheelsAverageLengthForOnePulse (nanometer)", 1, 0);
            setArgumentUnsignedHex6(0, "value");
        }
        return commandLengthValueForMode(mode, 6, 0);
    }
    // Rotation By Seconds (get/set)
    else if (commandHeader == COMMAND_GET_ROTATION_BY_SECONDS_AT_FULL_SPEED) {
        if (fillDeviceArgumentList) {
            setFunction("getRotationBySecondsAtFullSpeed", 0, 1);
            setResultUnsignedHex2(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    else if (commandHeader == COMMAND_SET_ROTATION_BY_SECONDS_AT_FULL_SPEED) {
        if (fillDeviceArgumentList) {
            setFunction("setRotationBySecondsAtFullSpeed", 1, 0);
            setArgumentUnsignedHex2(0, "value");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    // Pulse by rotation (get/set)
    else if (commandHeader == COMMAND_GET_PULSE_BY_ROTATION) {
        if (fillDeviceArgumentList) {
            setFunction("getPulseByRotation", 0, 1);
            setResultUnsignedHex4(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    else if (commandHeader == COMMAND_SET_PULSE_BY_ROTATION) {
        if (fillDeviceArgumentList) {
            setFunction("setPulseByRotation", 1, 0);
            setArgumentUnsignedHex4(0, "value");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    // Wheel delta length (get/set)
    else if (commandHeader == COMMAND_GET_WHEEL_DELTA_FOR_ONE_PULSE_LENGTH) {
        if (fillDeviceArgumentList) {
            setFunction("getWheelDeltaLengthForOnePulse (nanometer)", 0, 1);
            setResultUnsignedHex6(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 6);
    }
    else if (commandHeader == COMMAND_SET_WHEEL_DELTA_FOR_ONE_PULSE_LENGTH) {
        if (fillDeviceArgumentList) {
            setFunction("setWheelDeltaLengthForOnePulse (nanometer)", 1, 0);
            setArgumentUnsignedHex6(0, "value");
        }
        return commandLengthValueForMode(mode, 6, 0);
    }
    // Wheel distance (get/set)
    else if (commandHeader == COMMAND_GET_WHEELS_DISTANCE) {
        if (fillDeviceArgumentList) {
            setFunction("getWheelsDistance (µm)", 0, 1);
            setResultUnsignedHex6(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 6);
    }
    else if (commandHeader == COMMAND_SET_WHEELS_DISTANCE) {
        if (fillDeviceArgumentList) {
            setFunction("setWheelsDistance (µm)", 1, 0);
            setArgumentUnsignedHex6(0, "value");
        }
        return commandLengthValueForMode(mode, 6, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = KINEMATICS_HEADER,
    .deviceGetName = &getKinematicsDeviceName,
    .deviceGetInterface = &deviceRobotKinematicsGetInterface
};

DeviceInterface* getRobotKinematicsDeviceInterface() {
    return &deviceInterface;
}
