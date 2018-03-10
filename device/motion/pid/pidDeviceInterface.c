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
            setFunction("get Motion Parameter", 1, 3);
            setArgumentUnsignedHex2(0, "motionType");
            setResultFloatHex4(0, "a (mm / sec)");
            setResultSeparator(1);
            setResultFloatHex4(2, "s (mm / sec^2)");
        }
        return commandLengthValueForMode(mode, 2, 9);
    } else if (commandHeader == COMMAND_SET_MOTION_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("set Motion Parameter", 5, 0);
            setArgumentUnsignedHex2(0, "motionType");
            setArgumentSeparator(1);
            setArgumentFloatHex4(2, "a (mm / sec)");
            setArgumentSeparator(3);
            setArgumentFloatHex4(4, "s (mm / sec^2)");
        }
        return commandLengthValueForMode(mode, 12, 0);
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
            setArgumentUnsignedHex2(0, "pid Index");
            setArgumentSeparator(1);
            setArgumentFloatHex4(2, "p (milli)");
            setArgumentSeparator(3);
            setArgumentFloatHex4(4, "i (milli)");
            setArgumentSeparator(5);
            setArgumentFloatHex4(6, "d (milli)");
            setArgumentSeparator(7);
            setArgumentFloatHex4(8, "mI (milli)");
        }
        return commandLengthValueForMode(mode, 22, 0);
    } else if (commandHeader == COMMAND_READ_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("get PID", 1, 9);
            setArgumentUnsignedHex2(0, "pid Index");
            setResultUnsignedHex2(0, "pid Index");
            setResultSeparator(1);
            setResultFloatHex4(2, "p (milli)");
            setResultSeparator(3);
            setResultFloatHex4(4, "i (milli)");
            setResultSeparator(5);
            setResultFloatHex4(6, "d (milli)");
            setResultSeparator(7);
            setResultFloatHex4(8, "mI (milli)");
        }
        return commandLengthValueForMode(mode, 2, 22);
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
            setFunction("set End Detection Parameter", 9, 0);
            setArgumentFloatHex4(0, "absDeltaPositionIntegralFactorThreshold");
            setArgumentSeparator(1);
            setArgumentFloatHex4(2, "maxUIntegralFactorThreshold");
            setArgumentSeparator(3);
            setArgumentFloatHex4(4, "maxUIntegralConstantThreshold");
            setArgumentSeparator(5);
            setArgumentFloatHex4(6, "timeRangeAnalysis");
            setArgumentSeparator(7);
            setArgumentFloatHex4(8, "noAnalysisAtStartupTime");
        }
        return commandLengthValueForMode(mode, 24, 0);
    } else if (commandHeader == COMMAND_GET_END_DETECTION_PARAMETER) {
        if (fillDeviceArgumentList) {
            setFunction("get End Detection Parameter", 0, 9);
            setResultFloatHex4(0, "absDeltaPositionIntegralFactorThreshold");
            setResultSeparator(1);             
            setResultFloatHex4(2, "maxUIntegralFactorThreshold");
            setResultSeparator(3);             
            setResultFloatHex4(4, "maxUIntegralConstantThreshold");
            setResultSeparator(5);             
            setResultFloatHex4(6, "timeRangeAnalysis");
            setResultSeparator(7);             
            setResultFloatHex4(8, "noAnalysisAtStartupTime");
        }
        return commandLengthValueForMode(mode, 0, 24);
    } else if (commandHeader == COMMAND_GET_DEBUG_DATA_PID) {
        if (fillDeviceArgumentList) {
            setFunction("send Debug Data Pid", 1, 17);
            
            setArgumentUnsignedHex2(0, "instructionType");

            setResultUnsignedHex2(0, "instructionType");
            setResultSeparator(1);             
            setResultFloatHex4(2, "pidTime (milliSec)");
            setResultSeparator(3);             
            setResultFloatHex4(4, "normal Position (mm)");
            setResultSeparator(5);
            setResultFloatHex4(6, "position (mm)");
            setResultSeparator(7);
            setResultFloatHex4(8, "error (mm)");
            setResultSeparator(9);
            setResultFloatHex4(10, "u");
            setResultSeparator(11);
            setResultFloatHex4(12, "endMotion integralTime");
            setResultSeparator(13);
            setResultFloatHex4(14, "endMotion absDelta Position Integral");
            setResultSeparator(15);
            setResultFloatHex4(16, "endMotion Integral");
        }
        return commandLengthValueForMode(mode, 2, 42);
    } else if (commandHeader == COMMAND_GET_MOTION_PARAMETER) {
        if (fillDeviceArgumentList) {    
            setFunction("get Motion Parameter", 1, 25);
            
            setArgumentUnsignedHex2(0, "idx");
            
            setResultUnsignedHex2(0, "idx");
            setResultSeparator(1);
            setResultFloatHex4(2, "a (mm / sec^2)");
            setResultSeparator(3);
            setResultFloatHex4(4, "s (mm / sec)");
            setResultSeparator(5);
            setResultFloatHex4(6, "smax (mm / sec)");
            setResultSeparator(7);
            setResultFloatHex4(8, "t1 (sec)");
            setResultSeparator(9);
            setResultFloatHex4(10, "t2 (sec)");
            setResultSeparator(11);
            setResultFloatHex4(12, "t3 (sec)");
            setResultSeparator(13);
            setResultFloatHex4(14, "p1 (mm)");
            setResultSeparator(15);
            setResultFloatHex4(16, "p2 (mm)");
            setResultSeparator(17);
            setResultFloatHex4(18, "p3/nextPosition (mm)");
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
