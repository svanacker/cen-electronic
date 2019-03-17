#include "accelerometerDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"
#include "accelerometerDeviceInterface.h"

const char* getAccelerometerDeviceName(void) {
    return "Accelerometer";
}

int deviceAccelerometerGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_ACCELEROMETER_GET_SAMPLE_COUNT) {
        if (fillDeviceArgumentList) {
            setFunction("getSampleCount", 0, 1);
            setResultUnsignedHex4(0, "Sample count");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    else if (commandHeader == COMMAND_ACCELEROMETER_GET_SAMPLE_RAW_DATA) {
        if (fillDeviceArgumentList) {
            setFunction("Sample Raw Data", 0, 5);
            setResultUnsignedHex4(0, "X Raw Data");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "Y Raw Data");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "Z Raw Data");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }
    else if (commandHeader == COMMAND_ACCELEROMETER_GET_SAMPLE_DATA_MILLIG_G) {
        if (fillDeviceArgumentList) {
            setFunction("Sample Data MilliG", 0, 5);
            setResultUnsignedHex4(0, "X (mG)");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "Y (mG)");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "Z (mG)");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }
    // TRESHOLD
    else if (commandHeader == COMMAND_ACCELEROMETER_GET_THRESHOLD) {
        if (fillDeviceArgumentList) {
            setFunction("Get Threshold", 0, 1);
            setResultUnsignedHex4(0, "Threshold (milli G)");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    else if (commandHeader == COMMAND_ACCELEROMETER_SET_THRESHOLD) {
        if (fillDeviceArgumentList) {
            setFunction("Set Threshold", 1, 0);
            setArgumentUnsignedHex4(0, "Threshold (milliG)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    // DEBUG
    else if (commandHeader == COMMAND_ACCELEROMETER_DEBUG_CONFIG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug Config");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_ACCELEROMETER_DEBUG_VALUES) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug Values");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = ACCELEROMETER_DEVICE_HEADER,
    .deviceGetName = &getAccelerometerDeviceName,
    .deviceGetInterface = &deviceAccelerometerGetInterface
};

DeviceInterface* getAccelerometerDeviceInterface() {
    return &deviceInterface;
}
