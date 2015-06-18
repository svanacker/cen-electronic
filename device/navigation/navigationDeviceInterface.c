#include "navigationDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getNavigationDeviceName(void) {
    return "Navigation";
}

int deviceNavigationGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    // Locations
    if (commandHeader == COMMAND_NAVIGATION_LOCATION_COUNT ) {
        if (fillDeviceArgumentList) {
            setFunction("Navigation Location Count", 0, 1);
            setResultUnsignedHex4(0, "Count");
        }
        return commandLengthValueForMode(mode, 0, 4);
    } else if (commandHeader == COMMAND_NAVIGATION_GET_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunction("GetLocation", 1, 5);
            setArgumentUnsignedHex4(0, "Index");
            setResultFixedCharArray(0, "Name");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "x (mm)");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "y (mm)");
        }
        return commandLengthValueForMode(mode, 4, 18);
    } else if (commandHeader == COMMAND_NAVIGATION_SET_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunction("SetLocation", 7, 0);
            setArgumentUnsignedHex4(0, "Index (replace, use 0xFFFF if just add)");
            setArgumentSeparator(1);
            setArgumentFixedCharArray(2, "Name");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "x (mm)");
            setArgumentSeparator(5);
            setArgumentUnsignedHex4(6, "y (mm)");
        }
        return commandLengthValueForMode(mode, 23, 0);
    }
    // Paths
    if (commandHeader == COMMAND_NAVIGATION_PATH_COUNT) {
        if (fillDeviceArgumentList) {
            setFunction("Navigation Path Count", 0, 1);
            setResultUnsignedHex4(0, "Count");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    else if (commandHeader == COMMAND_NAVIGATION_GET_PATH) {
        if (fillDeviceArgumentList) {
            setFunction("GetPath", 1, 19);
            setArgumentUnsignedHex4(0, "Index");
            setResultFixedCharArray(0, "LocationName1");
            setResultSeparator(1);
            setResultFixedCharArray(2, "LocationName2");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "Cost");
            setResultSeparator(5);
            setResultUnsignedHex4(6, "ControlPoint1 (mm)");
            setResultSeparator(7);
            setResultUnsignedHex4(8, "ControlPoint2 (mm)");
            setResultSeparator(9);
            setResultUnsignedHex4(10, "angle1");
            setResultSeparator(11);
            setResultUnsignedHex4(12, "angle2");
            setResultSeparator(13);
            setResultUnsignedHex2(14, "accelerationFactor");
            setResultSeparator(15);
            setResultUnsignedHex2(16, "speedFactor");
            setResultSeparator(17);
            setResultUnsignedChar1(18, "mustGoBackward");
        }
        return commandLengthValueForMode(mode, 4, 42);
    }
    else if (commandHeader == COMMAND_NAVIGATION_SET_PATH) {
        if (fillDeviceArgumentList) {
            setFunction("SetPath", 21, 0);
            setArgumentUnsignedHex4(0, "Index (replace, use 0xFFFF if just add)");
            setArgumentSeparator(1);
            setArgumentFixedCharArray(2, "LocationName1");
            setArgumentSeparator(3);
            setArgumentFixedCharArray(4, "LocationName2");
            setArgumentSeparator(5);
            setArgumentUnsignedHex4(6, "Cost");
            setArgumentSeparator(7);
            setArgumentUnsignedHex4(8, "ControlPoint1 (mm)");
            setArgumentSeparator(9);
            setArgumentUnsignedHex4(10, "ControlPoint2 (mm)");
            setArgumentSeparator(11);
            setArgumentUnsignedHex4(12, "angle1");
            setArgumentSeparator(13);
            setArgumentUnsignedHex4(14, "angle2");
            setArgumentSeparator(15);
            setArgumentUnsignedHex2(16, "accelerationFactor");
            setArgumentSeparator(17);
            setArgumentUnsignedHex2(18, "speedFactor");
            setArgumentSeparator(19);
            setArgumentUnsignedChar1(20, "mustGoBackward");
        }
        return commandLengthValueForMode(mode, 47, 0);
    }


    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = NAVIGATION_DEVICE_HEADER,
    .deviceGetName = &getNavigationDeviceName,
    .deviceGetInterface = &deviceNavigationGetInterface
};

DeviceInterface* getNavigationDeviceInterface(void) {
    return &deviceInterface;
}
