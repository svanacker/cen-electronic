#include <stdbool.h>

#include "motionDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

#define MOTION_DEVICE_NOTIFY_LENGTH   16

const char* deviceMotionGetName(void) {
    return "motion";
}

void fillNotifyResults(char* notificationName) {
    setNotification(notificationName, 7);
    setArgumentUnsignedHex4(0, "x(mm)");
    setArgumentSeparator(1);
    setArgumentUnsignedHex4(2, "y(mm)");
    setArgumentSeparator(3);
    setArgumentUnsignedHex4(4, "ang(1/10)deg");
    setArgumentSeparator(5);
    setArgumentUnsignedChar1(6, "Fake data to debug :(");
}

int deviceMotionGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // forward MM
    if (commandHeader == COMMAND_MOTION_FORWARD_IN_MM) {
        if (fillDeviceArgumentList) {
            setFunction("forward", 1, 0);
            setArgumentUnsignedHex4(0, "distance (MM)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// backward MM
    else if (commandHeader == COMMAND_MOTION_BACKWARD_IN_MM) {
        if (fillDeviceArgumentList) {
            setFunction("backward", 1, 0);
            setArgumentUnsignedHex4(0, "distance (MM)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn left in degree
    else if (commandHeader == COMMAND_MOTION_LEFT_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Left", 1, 0);
            setArgumentUnsignedHex4(0, "leftAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn left by demi Quadrant
    else if (commandHeader == COMMAND_MOTION_LEFT_DEMI_QUADRANT) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Left (step of 45�)", 1, 0);
            setArgumentUnsignedHex2(0, "Demi Quadrant count");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }// turn right in degree
    else if (commandHeader == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Right", 1, 0);
            setArgumentUnsignedHex4(0, "rightAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    } else if (commandHeader == COMMAND_MOTION_RIGHT_DEMI_QUADRANT) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Right (step of 45�)", 1, 0);
            setArgumentUnsignedHex2(0, "Demi Quadrant count");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }// ONLY ONE WHEEL
        // turn left (only right in degree
    else if (commandHeader == COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Left One Wheel", 1, 0);
            setArgumentUnsignedHex4(0, "leftAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// turn right (only right wheel) in degree
    else if (commandHeader == COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE) {
        if (fillDeviceArgumentList) {
            setFunction("rotation Right One Wheel", 1, 0);
            setArgumentUnsignedHex4(0, "rightAngle (DeciDeg)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// motion : Cancel
    else if (commandHeader == COMMAND_MOTION_STOP) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Cancel Motion");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// motion : Cancel ALL
    else if (commandHeader == COMMAND_MOTION_CANCEL_ALL) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Cancel Motion All");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// motion : Obstacle
    else if (commandHeader == COMMAND_MOTION_OBSTACLE) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("motion Obstacle");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Calibration
    else if (commandHeader == COMMAND_SQUARE_CALIBRATION) {
        if (fillDeviceArgumentList) {
            setFunction("square Calibration", 3, 0);
            setArgumentUnsignedHex2(0, "left (0x00)or right (0x01)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "length (distance in mm)");
        }
        return commandLengthValueForMode(mode, 7, 0);
    }// Parameters
        // MODE REPLACE / ADD
    else if (commandHeader == COMMAND_MOTION_MODE_ADD) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("motion Mode Add");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_MOTION_MODE_REPLACE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("motion Mode Replace");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_MOTION_MODE_GET) {
        if (fillDeviceArgumentList) {
            setFunction("motion Mode Get", 0, 1);
            setResultUnsignedChar1(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 1);
    } else if (commandHeader == COMMAND_MOTION_NOTIFY_FAKE) {
        if (fillDeviceArgumentList) {
            setFunction("Generate fake Notification", 1, 0);
            setArgumentUnsignedChar1(0, "Notif. type char");
            setResultUnsignedChar1(0, "value");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    // NOTIFICATION
    if (DEVICE_MODE_NOTIFY == mode) {
        if (commandHeader == NOTIFY_MOTION_STATUS_REACHED) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notify Reached");
            }
            return MOTION_DEVICE_NOTIFY_LENGTH;
        } else if (commandHeader == NOTIFY_MOTION_STATUS_BLOCKED) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notify Blocked");
            }
            return MOTION_DEVICE_NOTIFY_LENGTH;
        } else if (commandHeader == NOTIFY_MOTION_STATUS_SHOCKED) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notify Shocked");
            }
            return MOTION_DEVICE_NOTIFY_LENGTH;
        } else if (commandHeader == NOTIFY_MOTION_STATUS_OBSTACLE) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notify Obstacle");
            }
            return MOTION_DEVICE_NOTIFY_LENGTH;
        } else if (commandHeader == NOTIFY_MOTION_STATUS_FAILED) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notify Failed");
            }
            return MOTION_DEVICE_NOTIFY_LENGTH;
        } else if (commandHeader == NOTIFY_MOTION_STATUS_MOVING) {
            if (fillDeviceArgumentList) {
                fillNotifyResults("notify Moving");
            }
            return MOTION_DEVICE_NOTIFY_LENGTH;
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
