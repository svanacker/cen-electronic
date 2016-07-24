#include "silecDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getSilecDeviceName(void) {
    return "SILEC";
}

int deviceSilecGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == WRITE_FREQUENCY_SILEC) {
        if (fillDeviceArgumentList) {            
            setFunction("Silec Writing", 2, 0);
            setArgumentUnsignedHex4(0, "XXXXMHZ");            
            setArgumentUnsignedHex4(1, "XXXX00HZ");           
        }
        return commandLengthValueForMode(mode, 8, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = SILEC_DEVICE_HEADER,
    .deviceGetName = &getSilecDeviceName,
    .deviceGetInterface = &deviceSilecGetInterface
};

DeviceInterface* getSilecDeviceInterface(void) {
    return &deviceInterface;
}