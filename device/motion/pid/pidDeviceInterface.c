#include <stdbool.h>

#include "pidDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getPidDeviceName(void) {
    return "PID";
}

int devicePidGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // MOTION PARAMETER
    if (commandHeader == COMMAND_MOTION_LOAD_DEFAULT_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("load Motion Default Parameters");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_GET_MOTION_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("getMotionParam", 1, 2);
            setArgumentUnsignedHex2(0, "motionType");
            setResultUnsignedHex2(0, "a");
            setResultUnsignedHex2(1, "s");
        }
        return commandLengthValueForMode(mode, 2, 4);
    } else if (commandHeader == COMMAND_SET_MOTION_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("setMotionParam", 3, 0);
            setArgumentUnsignedHex2(0, "motionType");
            setArgumentUnsignedHex2(1, "a");
            setArgumentUnsignedHex2(2, "s");
        }
        return commandLengthValueForMode(mode, 6, 0);
    }
    else if (commandHeader == COMMAND_MOTION_SAVE_TO_EEPROM_PARAMETERS) {
		if(fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("save Motion Param. To Eeprom");
		}
		return commandLengthValueForMode(mode, 0, 0);
    }

    // PID PARAMETER
    if (commandHeader == COMMAND_WRITE_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("setPID", 9, 0);
            setArgumentUnsignedHex2(0, "pidIdx");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "p");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "i");
            setArgumentSeparator(5);
            setArgumentUnsignedHex2(6, "d");
            setArgumentSeparator(7);
            setArgumentUnsignedHex2(8, "mI");
        }
        return commandLengthValueForMode(mode, 14, 0);
    } else if (commandHeader == COMMAND_READ_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("getPID", 1, 9);
            setArgumentUnsignedHex2(0, "pidIdx");
            setResultUnsignedHex2(0, "pidIdx");
            setResultSeparator(1);
            setResultUnsignedHex2(2, "p");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "i");
            setResultSeparator(5);
            setResultUnsignedHex2(6, "d");
            setResultSeparator(7);
            setResultUnsignedHex2(8, "mI");
        }
        return commandLengthValueForMode(mode, 2, 14);
    } else if (commandHeader == COMMAND_LOAD_PID_PARAMETERS_DEFAULT_VALUES) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("load Pid Param. Default Values");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_SAVE_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("save PID Parameters To Eeprom");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_SET_END_DETECTION_PARAMETER) {
        if (fillDeviceArgumentList) {
            setFunction("setEndDetectParam", 9, 0);
            setArgumentUnsignedHex2(0, "absDeltaPositionIntegralFactorThreshold");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "maxUIntegralFactorThreshold");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "maxUIntegralConstantThreshold");
            setArgumentSeparator(5);
            setArgumentUnsignedHex2(6, "timeRangeAnalysis");
            setArgumentSeparator(7);
            setArgumentUnsignedHex2(8, "noAnalysisAtStartupTime");
        }
        return commandLengthValueForMode(mode, 14, 0);
    } else if (commandHeader == COMMAND_GET_END_DETECTION_PARAMETER) {
        if (fillDeviceArgumentList) {
            setFunction("getEndDetectParameter", 0, 9);
            setResultUnsignedHex2(0, "absDeltaPositionIntegralFactorThreshold");
            setResultSeparator(1);             
            setResultUnsignedHex2(2, "maxUIntegralFactorThreshold");
            setResultSeparator(3);             
            setResultUnsignedHex2(4, "maxUIntegralConstantThreshold");
            setResultSeparator(5);             
            setResultUnsignedHex2(6, "timeRangeAnalysis");
            setResultSeparator(7);             
            setResultUnsignedHex2(8, "noAnalysisAtStartupTime");
        }
        return commandLengthValueForMode(mode, 0, 14);
    } else if (commandHeader == COMMAND_GET_DEBUG_DATA_PID) {
        if (fillDeviceArgumentList) {
            setFunction("send Debug Data Pid", 1, 17);
            
            setArgumentUnsignedHex2(0, "instructionType");

            setResultUnsignedHex2(0, "instructionType");
            setResultSeparator(1);             
            setResultUnsignedHex4(2, "pidTime");
            setResultSeparator(3);             
            setResultUnsignedHex6(4, "normalPosition");
            setResultSeparator(5);
            setResultUnsignedHex6(6, "position");
            setResultSeparator(7);
            setResultUnsignedHex4(8, "error");
            setResultSeparator(9);
            setResultUnsignedHex4(10, "u");
            setResultSeparator(11);
            setResultUnsignedHex4(12, "endMotion_integralTime");
            setResultSeparator(13);
            setResultUnsignedHex4(14, "endMotion_absDelPosiInt");
            setResultSeparator(15);
            setResultUnsignedHex4(16, "endMotion_uIntegral");
        }
        return commandLengthValueForMode(mode, 2, 46);
    } else if (commandHeader == COMMAND_GET_MOTION_PARAMETER) {
        if (fillDeviceArgumentList) {    
            setFunction("getMotionParameter", 1, 25);
            
            setArgumentUnsignedHex2(0, "idx");
            
            setResultUnsignedHex2(0, "idx");
            setResultSeparator(1);
            setResultUnsignedHex2(2, "a");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "s");
            setResultSeparator(5);
            setResultUnsignedHex2(6, "smax");
            setResultSeparator(7);
            setResultUnsignedHex4(8, "t1");
            setResultSeparator(9);
            setResultUnsignedHex4(10, "t2");
            setResultSeparator(11);
            setResultUnsignedHex4(12, "t3");
            setResultSeparator(13);
            setResultUnsignedHex6(14, "p1");
            setResultSeparator(15);
            setResultUnsignedHex6(16, "p2");
            setResultSeparator(17);
            setResultUnsignedHex6(18, "p3/nextPosition");
            setResultSeparator(19);
            setResultUnsignedChar1(20, "profileType");
            setResultSeparator(21);
            setResultUnsignedChar1(22, "motionParameterType");
            setResultSeparator(23);
            setResultUnsignedChar1(24, "pidType");
        }
        return commandLengthValueForMode(mode, 2, 53);
    }
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PID_DEVICE_HEADER,
    .deviceGetName = &getPidDeviceName,
    .deviceGetInterface = &devicePidGetInterface
};

DeviceInterface* getPidDeviceInterface() {
    return &deviceInterface;
}
