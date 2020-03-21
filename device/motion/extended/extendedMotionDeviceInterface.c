#include <stdbool.h>

#include "extendedMotionDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceExtendedMotionGetName(void) {
    return "extendedMotion";
}

void fillSplineParameters(void) {
    // X3/Y3 as absolute position + Angle -> 19 octets
    setArgumentFloatHex6(0, "x3 (microM)");
    setArgumentSeparator(1);
    setArgumentFloatHex6(2, "y3 (microM)");
    setArgumentSeparator(3);
    setArgumentFloatHex4(4, "final Angle (DeciDegree)");
    setArgumentSeparator(5);
    // 2 Distances -> 10 octets
    setArgumentFloatHex4(6, "distance P0-P1 (mm)");
    setArgumentSeparator(7);
    setArgumentFloatHex4(8, "distance P2-P3 (mm)");
    setArgumentSeparator(9);
    // Speed Factors -> 5 octets
    setArgumentFloatHex2(10, "speedFactor (deci)");
    setArgumentSeparator(11);
    setArgumentFloatHex2(12, "acceleration Factor (deci)");
}

int deviceExtendedMotionGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // B-Spline with relative spline
    if (commandHeader == COMMAND_MOTION_SPLINE_RELATIVE) {
        if (fillDeviceArgumentList) {
            setFunction("bSpline Relative", 13, 0);
            fillSplineParameters();
        }
        return commandLengthValueForMode(mode, 34, 0);
    }// B-Spline with absolute spline
    else if (commandHeader == COMMAND_MOTION_SPLINE_ABSOLUTE) {
        if (fillDeviceArgumentList) {
            setFunction("bSpline Absolute", 13, 0);
            fillSplineParameters();
        }
        return commandLengthValueForMode(mode, 34, 0);
    }// BSpline : forward test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_FORWARD) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Forward");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_BACKWARD) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Backward");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BSpline : left test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_LEFT) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Left");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BSpline : right Test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Right");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BSpline : forward->left->forward test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_FORWARD_LEFT_FORWARD) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Forward->Left->Forward ");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BSpline : forward->right->forward test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_FORWARD_RIGHT_FORWARD) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Forward->Right->Forward");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BSpline : backward->left->backward test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_BACKWARD_LEFT_BACKWARD) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Backward->Left->Backward ");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BSpline : backward->right->backward test
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_BACKWARD_RIGHT_BACKWARD) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("bSpline Test Backward->Right->Backward");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = EXTENDED_MOTION_DEVICE_HEADER,
    .deviceGetName = &deviceExtendedMotionGetName,
    .deviceGetInterface = &deviceExtendedMotionGetInterface
};

DeviceInterface* getExtendedMotionDeviceInterface(void) {
    return &deviceInterface;
}
