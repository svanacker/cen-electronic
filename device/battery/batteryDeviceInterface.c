#include "batteryDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getBatteryDeviceName(void) {
    return "Battery";
}

int deviceBatteryGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    if (commandHeader == COMMAND_READ_BATTERY ) {
        if (fillDeviceArgumentList) {
            setFunction("Clock Read", 0, 1);
            setResultUnsignedHex4(0, "Battery Value (mV)");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = BATTERY_DEVICE_HEADER,
    .deviceGetName = &getBatteryDeviceName,
    .deviceGetInterface = &deviceBatteryGetInterface
};

DeviceInterface* getBatteryDeviceInterface(void) {
    return &deviceInterface;
}
