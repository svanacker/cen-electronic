#include "pidDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"

const char* getPIDDeviceName(void) {
    return "PID";
}

int devicePIDGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_WRITE_PID) {
        if (fillDeviceArgumentList) {
            setFunction("setPID", 5, 0);
            setArgumentUnsignedHex2(0, "pidIdx");
            setArgumentUnsignedHex2(1, "p");
            setArgumentUnsignedHex2(2, "i");
            setArgumentUnsignedHex2(3, "d");
            setArgumentUnsignedHex2(4, "mI");
        }
        return commandLengthValueForMode(mode, 10, 0);
    } else if (commandHeader == COMMAND_READ_PID) {
            if (fillDeviceArgumentList) {
                setFunction("getPID", 1, 5);
                setArgumentUnsignedHex2(0, "pidIdx");
                setResultUnsignedHex2(0, "pidIdx");
                setResultUnsignedHex2(1, "p");
                setResultUnsignedHex2(2, "i");
                setResultUnsignedHex2(3, "d");
                setResultUnsignedHex2(4, "mI");
            }
            return commandLengthValueForMode(mode, 2, 10);
    } else if (commandHeader == COMMAND_SET_END_DETECTION_PARAMETER) {
        if (fillDeviceArgumentList) {
            setFunction("setEndDetectParam", 0, 5);
            setArgumentUnsignedHex2(0, "absDPosIntFacThres");
            setArgumentUnsignedHex2(1, "maxUIntFacThres");
            setArgumentUnsignedHex2(2, "maxUIntConThres");
            setArgumentUnsignedHex2(3, "timeRangeAna");
            setArgumentUnsignedHex2(4, "noAnaAtStart");
        }
        return commandLengthValueForMode(mode, 10, 0);
    } else if (commandHeader == COMMAND_GET_END_DETECTION_PARAMETER) {
        if (fillDeviceArgumentList) {
            setFunction("getEndDetectParam", 0, 5);
            setResultUnsignedHex2(0, "absDPosIntFacThres");
            setResultUnsignedHex2(1, "maxUIntFacThres");
            setResultUnsignedHex2(2, "maxUIntConThres");
            setResultUnsignedHex2(3, "timeRangeAna");
            setResultUnsignedHex2(4, "noAnaAtStart");
        }
        return commandLengthValueForMode(mode, 10, 0);
    } else if (commandHeader == COMMAND_SEND_DEBUG_DATA_PID) {
        if (fillDeviceArgumentList) {
            setFunction("sendDbgDataPid", 1, 11);
            
            setArgumentUnsignedChar1(0, "idx");
            
            // _01001-00020-5678-40-200050008000
            setResultUnsignedChar1(0, "idx");
            setResult(1, DEVICE_ARG_UNSIGNED_HEX_3, "pidTime");
            setResultUnsignedChar1(2, "pidTipe");
            setResultSeparator(3); 
            setResult(4, DEVICE_ARG_SIGNED_HEX_5, "pos");
            setResultSeparator(5);
            setResultUnsignedHex4(6, "err");
            setResultSeparator(7);
            setResultUnsignedHex2(8, "u");
            setResultSeparator(9);
            setResult(10, DEVICE_ARG_UNSIGNED_HEX_12, "time/absDelPosiInt/uIntegral");
        }
        return commandLengthValueForMode(mode, 32, 1);
    } else if (commandHeader == COMMAND_SEND_MOTION_PARAMETER) {
        if (fillDeviceArgumentList) {    
            setFunction("sendMotParam", 1, 10);
            
            setArgumentUnsignedChar1(0, "idx");
            
            setResultUnsignedChar1(0, "idx");
            setResult(1, DEVICE_ARG_UNSIGNED_HEX_6, "a/s/smax");
            setResultSeparator(2);
            setResult(3, DEVICE_ARG_UNSIGNED_HEX_8, "t1/t2/t3");
            setResultSeparator(4);
            setResult(5, DEVICE_ARG_UNSIGNED_HEX_10, "p1/p2");
            setResultSeparator(6);
            setResultUnsignedChar1(7, "profileType");
            setResultUnsignedChar1(8, "motionType");
            setResultUnsignedChar1(9, "pidType");
        }
        return commandLengthValueForMode(mode, 1, 32);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PID_DEVICE_HEADER,
    .deviceGetName = &getPIDDeviceName,
    .deviceGetInterface = &devicePIDGetInterface
};

DeviceInterface* getPIDDeviceInterface() {
    return &deviceInterface;
}
