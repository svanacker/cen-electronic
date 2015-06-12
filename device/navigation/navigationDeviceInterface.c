#include "navigationDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getNavigationDeviceName(void) {
    return "Navigation";
}

int deviceNavigationGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    if (commandHeader == COMMAND_NAVIGATION_LOCATION_COUNT ) {
        if (fillDeviceArgumentList) {
            setFunction("Navigation Location Count", 0, 1);
            setResultUnsignedHex4(0, "Count");
        }
        return commandLengthValueForMode(mode, 0, 4);
    } else if (commandHeader == COMMAND_NAVIGATION_GET_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunction("GetLocation", 1, 8);
            setArgumentUnsignedHex4(0, "Index");
            setResultUnsignedHex2(0, "Name(c0)");
            setResultUnsignedHex2(1, "Name(c1)");
            setResultUnsignedHex2(2, "Name(c2)");
            setResultUnsignedHex2(3, "Name(c3)");
            setResultSeparator(4);
            setResultUnsignedHex4(5, "x (mm)");
            setResultSeparator(6);
            setResultUnsignedHex4(7, "y (mm)");
        }
        return commandLengthValueForMode(mode, 4, 18);
    } else if (commandHeader == COMMAND_NAVIGATION_SET_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunction("SetLocation", 10, 0);
            setArgumentUnsignedHex4(0, "Index (replace, use 0xFFFF if just add)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Name(c0)");
            setArgumentUnsignedHex2(3, "Name(c1)");
            setArgumentUnsignedHex2(4, "Name(c2)");
            setArgumentUnsignedHex2(5, "Name(c3)");
            setArgumentSeparator(6);
            setArgumentUnsignedHex4(7, "x (mm)");
            setArgumentSeparator(8);
            setArgumentUnsignedHex4(9, "y (mm)");
        }
        return commandLengthValueForMode(mode, 23, 0);
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
