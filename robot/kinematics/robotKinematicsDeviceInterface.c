#include "robotKinematicsDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getKinematicsDeviceName(void) {
    return "Kinematics";
}

int deviceRobotKinematicsGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("load Default Values");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_KINEMATICS_SAVE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("save To Eeprom");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// DEBUG
    else if (commandHeader == COMMAND_KINEMATICS_LIST_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("debug as Table List");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// GET ALL values
    else if (commandHeader == COMMAND_KINEMATICS_READ_ALL) {
        if (fillDeviceArgumentList) {
            setFunction("real All", 0, 13);
            // CODER VALUE
            setResultUnsignedHex6(0, "coder Wheel Average Diameter (nanoM)");
            setResultSeparator(1);
            setResultUnsignedHex6(2, "coder Wheel Average Delta Diameter (microM)");
            setResultSeparator(3);
            setResultUnsignedHex6(4, "coder Wheel Distance Between Wheels (microM)");
            setResultSeparator(5);
            setResultUnsignedHex6(6, "coder Wheel Pulse By Rotation (pulse/rotation)");
            setResultSeparator(7);
            // MOTOR VALUE
            setResultUnsignedHex6(8, "motor Wheel Average Diameter (microMM)");
            setResultSeparator(9);
            setResultUnsignedHex6(10, "motor Wheel Distance Between Wheels (microM)");
            setResultSeparator(11);
            setResultUnsignedHex6(12, "motor Wheel Rotation By Second At FullSpeed (rot/sec)");
        }
        return commandLengthValueForMode(mode, 0, 48);
    }// CODER VALUE
    else if (commandHeader == COMMAND_SET_CODER_WHEEL_AVERAGE_DIAMETER_MM) {
        if (fillDeviceArgumentList) {
            setFunction("set Coder Wheel Average Diameter", 1, 0);
            setArgumentUnsignedHex6(0, "value (nanoM)");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_SET_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM) {
        if (fillDeviceArgumentList) {
            setFunction("set Coder Wheel Average Delta Diameter", 1, 0);
            setArgumentUnsignedHex6(0, "value (nanoM)");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_SET_CODER_DISTANCE_BETWEEN_WHEELS_MM) {
        if (fillDeviceArgumentList) {
            setFunction("set Coder Distance Between Wheels", 1, 0);
            setArgumentUnsignedHex6(0, "value (microM)");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_SET_CODER_WHEEL_PULSE_BY_ROTATION) {
        if (fillDeviceArgumentList) {
            setFunction("set Coder Wheel Pulse By Rotation", 1, 0);
            setArgumentUnsignedHex6(0, "value (pulse / rotation)");
        }
        return commandLengthValueForMode(mode, 6, 0);
    }// MOTOR VALUE
    else if (commandHeader == COMMAND_SET_MOTOR_WHEEL_AVERAGE_DIAMETER_MM) {
        if (fillDeviceArgumentList) {
            setFunction("set Motor Wheel Average Diameter", 1, 0);
            setArgumentUnsignedHex6(0, "value (microM)");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_SET_MOTOR_DISTANCE_BETWEEN_WHEELS_MM) {
        if (fillDeviceArgumentList) {
            setFunction("set Motor Distance Between Wheels", 1, 0);
            setArgumentUnsignedHex6(0, "value (microM)");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_SET_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED) {
        if (fillDeviceArgumentList) {
            setFunction("set Motor Wheel Rotation By Seconds At Full Speed", 1, 0);
            setArgumentUnsignedHex6(0, "rotation / second");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_SET_ROBOT_TYPE) {
        if (fillDeviceArgumentList) {
            setFunction("set RobotType", 1, 0);
            setArgumentUnsignedHex2(0, "BIG (1), SMALL(2)");
        }
        return commandLengthValueForMode(mode, 2, 0);
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
