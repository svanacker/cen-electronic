#include "mpuDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getMpuDeviceName(void) {
    return "Motion-Processor-Unit";
}

int deviceMpuGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == GET_ACCELERATION_MPU) {
        if (fillDeviceArgumentList) {            
            setFunction("MPU Acceleration", 0, 5);
            setResultUnsignedHex4(0, "Acceleration X");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "Acceleration Y");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "Acceleration Z");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }else if (commandHeader == GET_GYROSCOPE_MPU) {
        if (fillDeviceArgumentList) {            
            setFunction("MPU Gyroscope", 0, 5);
            setResultUnsignedHex4(0, "Gyroscope X");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "Gyroscope Y");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "Gyroscope Z");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }else if (commandHeader == GET_TEMPERATURE_MPU) {
        if (fillDeviceArgumentList) {            
            setFunction("MPU Temperature", 0, 1);
            setResultUnsignedHex4(0, "Temperature Celcius");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = MPU_DEVICE_HEADER,
    .deviceGetName = &getMpuDeviceName,
    .deviceGetInterface = &deviceMpuGetInterface
};

DeviceInterface* getMpuDeviceInterface(void) {
    return &deviceInterface;
}