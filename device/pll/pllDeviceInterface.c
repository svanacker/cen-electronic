#include "pllDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getPllDeviceName(void) {
    return "Frequency Synthetiser";
}

int devicePllGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == WRITE_FREQUENCY_PLL) {
        if (fillDeviceArgumentList) {            
            setFunction("PLL Writing", 2, 0);
            setArgumentUnsignedHex4(0, "XXXXMHZ");            
            setArgumentUnsignedHex4(1, "XXXX00HZ");           
        }
        return commandLengthValueForMode(mode, 8, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PLL_DEVICE_HEADER,
    .deviceGetName = &getPllDeviceName,
    .deviceGetInterface = &devicePllGetInterface
};

DeviceInterface* getPllDeviceInterface(void) {
    return &deviceInterface;
}