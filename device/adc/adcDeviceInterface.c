#include "adcDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getADCDeviceName(void) {
    return "ADC";
}

int deviceADCGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_GET_ADC_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("getADC", 1, 1);
            setArgumentUnsignedHex2(0, "ADC_idx");
            setResultUnsignedHex4(0, "Value(mV)");
        }
        return commandLengthValueForMode(mode, 2, 4);
    }
    else if (commandHeader == COMMANG_GET_ADC_VALUE_DEBUG_PERIOD) {
        if (fillDeviceArgumentList) {
            setFunction("getADCPeriod", 5, 0);
            setArgumentUnsignedHex2(0, "ADC_idx");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Sample Count");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "Deci seconds between read");
        }
        return commandLengthValueForMode(mode, 8, 0);
    }
    else if (commandHeader == COMMAND_GET_ADC_ALL_VALUES) {
        if (fillDeviceArgumentList) {
            setFunction("getADC_AllValues", 0, 11);
            setResultUnsignedHex4(0, "Value 0(mV)");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "Value 1(mV)");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "Value 2(mV)");
            setResultSeparator(5);
            setResultUnsignedHex4(6, "Value 3(mV)");
            setResultSeparator(7);
            setResultUnsignedHex4(8, "Value 4(mV)");
            setResultSeparator(9);
            setResultUnsignedHex4(10, "Value 5(mV)");
        }
        return commandLengthValueForMode(mode, 0, 29);
    }
    else if (commandHeader == COMMAND_GET_ADC_LIST) {   
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("getADCList");
        }
        return commandLengthValueForMode(mode, 0, 0);
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
