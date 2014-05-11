#include "adcDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getADCDeviceName(void) {
    return "ADC";
}

int deviceADCGetInterface(char header, int mode,
        bool fillDeviceArgumentList) {
    if (header == COMMAND_GET_ADC_VALUE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getADC", 1);
				setArgumentUnsignedHex2(0, "ADC_idx");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getADC", 1);
				setArgumentUnsignedHex4(0, "Value(mV)");
            }
            return 4;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = ADC_DEVICE_HEADER,
    .deviceGetName = &getADCDeviceName,
    .deviceGetInterface = &deviceADCGetInterface
};

DeviceInterface* getADCDeviceInterface() {
    return &deviceInterface;
}
