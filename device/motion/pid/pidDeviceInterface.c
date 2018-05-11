#include <stdbool.h>

#include "pidDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getPidDeviceName(void) {
    return "PID";
}

int devicePidGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // MOTION PARAMETERS
    if (commandHeader == COMMAND_GET_MOTION_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("get Motion Parameter", 1, 3);
            setArgumentUnsignedHex2(0, "motionType");
            setResultFloatHex4(0, "a (mm / sec)");
            setResultSeparator(1);
            setResultFloatHex4(2, "s (mm / sec^2)");
        }
        return commandLengthValueForMode(mode, 2, 9);
    }
    else if (commandHeader == COMMAND_SET_MOTION_PARAMETERS) {
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
    // PID PARAMETER
    else if (commandHeader == COMMAND_GET_PID_PARAMETERS) {
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
    }
    else if (commandHeader == COMMAND_SET_PID_PARAMETERS) {
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
        // PERSISTENCE
    }
    else if (commandHeader == COMMAND_LOAD_PID_PARAMETERS_DEFAULT_VALUES) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("load Pid Default Values");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_SAVE_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("save PID Parameters To Eeprom");
        }
        return commandLengthValueForMode(mode, 0, 0);
        // DEBUG / TRAJECTORY
    }
    else if (commandHeader == COMMAND_GET_COMPUTATION_VALUES_DATA_PID) {
        if (fillDeviceArgumentList) {
            // Argument : Type / Index : 7 octets
            setFunction("Get Computation Values Data Pid", 3, 25);
            setArgumentUnsignedHex2(0, "instructionType");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "index");
            // Instruction Type => 3 octets
            setResultUnsignedHex2(0, "instructionType");
            setResultSeparator(1);
            // Pid Time => 5 octets
            setResultFloatHex4(2, "pidTime (milliSec)");
            setResultSeparator(3);
            // Speed => 10 octets
            setResultFloatHex4(4, "normal Speed (mm / s)");
            setResultSeparator(5);
            setResultFloatHex4(6, "Real Speed (mm / s)");
            setResultSeparator(7);
            // Acceleration => 10 octets
            setResultFloatHex4(8, "normal Acceleration (mm / s)");
            setResultSeparator(9);
            setResultFloatHex4(10, "Real Acceleration (mm / s)");
            setResultSeparator(11);
            // Position => 14 octets
            setResultFloatHex6(12, "normal Position (mm)");
            setResultSeparator(13);
            setResultFloatHex6(14, "position (mm)");
            setResultSeparator(15);
            // Errors => 15 octets
            setResultFloatHex4(16, "error (mm)");
            setResultSeparator(17);
            setResultFloatHex4(18, "Int Error (mm * s)");
            setResultSeparator(19);
            setResultFloatHex4(20, "Deriv Error (mm / s)");
            setResultSeparator(21);
            // Errors with factor => 15 octets
            /*
            setResultFloatHex4(22, "PExE (mm)");
            setResultSeparator(23);
            setResultFloatHex4(24, "IExI (mm * s)");
            setResultSeparator(25);
            setResultFloatHex4(26, "DExE (mm / s)");
            setResultSeparator(27);
            */
            // U / Normal U => 9 octets
            setResultFloatHex4(22, "normal U");
            setResultSeparator(23);
            setResultFloatHex4(24, "u");
            // Computation : end of motion
            // TODO : Add Bool value
            // setResultBool(25, "abs Acceleration Too High Than Expected");
            // setResultBool(26, "abs Speed Too Low Than Expected");
            // setResultBool(27, "abs U Too High Than Expected");
        }
        return commandLengthValueForMode(mode, 7, 66);
    }
    else if (commandHeader == COMMAND_CLEAR_COMPUTATION_VALUES_DATA_PID) {
        if (fillDeviceArgumentList) {
            setFunction("Clear Computation Values Data PID", 1, 0);
            setArgumentUnsignedHex2(0, "instructionType");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_SET_COMPUTATION_VALUES_DATA_PID) {
        if (fillDeviceArgumentList) {
            setFunction("Set Computation Values Data PID", 25, 0);

            // InstructionType / Index => 3 octets
            setArgumentUnsignedHex2(0, "instructionType");
            setArgumentSeparator(1);

            // Pid Time => 5 octets
            setArgumentFloatHex4(2, "pidTime (milliSec)");
            setArgumentSeparator(3);

            // Speed => 10 octets
            setArgumentFloatHex4(4, "normal Speed (mm / s)");
            setArgumentSeparator(5);
            setArgumentFloatHex4(6, "Real Speed (mm / s)");
            setArgumentSeparator(7);

            // Acceleration => 10 octets
            setArgumentFloatHex4(8, "normal Acceleration (mm / s)");
            setArgumentSeparator(9);
            setArgumentFloatHex4(10, "Real Acceleration (mm / s)");
            setArgumentSeparator(11);

            // Position => 14 octets
            setArgumentFloatHex6(12, "normal Position (mm)");
            setArgumentSeparator(13);
            setArgumentFloatHex6(14, "position (mm)");
            setArgumentSeparator(15);

            // Errors => 15 octets
            setArgumentFloatHex4(16, "error (mm)");
            setArgumentSeparator(17);
            setArgumentFloatHex4(18, "Int Error (mm * s)");
            setArgumentSeparator(19);
            setArgumentFloatHex4(20, "Deriv Error (mm / s)");
            setArgumentSeparator(21);

            // U / Normal U => 9 octets
            setArgumentFloatHex4(22, "normal U");
            setArgumentSeparator(23);
            setArgumentFloatHex4(24, "u");
        }
        return commandLengthValueForMode(mode, 66, 0);
    } else if (commandHeader == COMMAND_GET_MOTION_DEFINITION_TRAJECTORY) {
        if (fillDeviceArgumentList) {    
            setFunction("get Motion Parameter", 1, 25);
            setArgumentUnsignedHex2(0, "idx");
            // Result
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
    // END DETECTION
    // -> DETAIL PHASE
    else if (commandHeader == COMMAND_SET_END_DETECTION_PARAMETER_DETAIL) {
        if (fillDeviceArgumentList) {
            setFunction("set End Detection Detail Parameter", 9, 0);
            setArgumentFloatHex4(0, "accelerationTooHighTresholdFactor");
            setArgumentSeparator(1);
            setArgumentFloatHex4(2, "speedTooLowThresholdFactor");
            setArgumentSeparator(3);
            setArgumentFloatHex4(4, "uTooHighTresholdFactor");
            setArgumentSeparator(5);
            setArgumentFloatHex4(6, "speedMinThreshold");
            setArgumentSeparator(7);
            setArgumentFloatHex4(8, "uMinThresholdValue");
        }
        return commandLengthValueForMode(mode, 24, 0);
    }
    else if (commandHeader == COMMAND_GET_END_DETECTION_PARAMETER_DETAIL) {
        if (fillDeviceArgumentList) {
            setFunction("get End Detection Detail Parameter", 0, 9);
            setResultFloatHex4(0, "accelerationTooHighTresholdFactor");
            setResultSeparator(1);
            setResultFloatHex4(2, "speedTooLowThresholdFactor");
            setResultSeparator(3);
            setResultFloatHex4(4, "uTooHighTresholdFactor");
            setResultSeparator(5);
            setResultFloatHex4(6, "speedMinThreshold");
            setResultSeparator(7);
            setResultFloatHex4(8, "uMinThresholdValue");
        }
        return commandLengthValueForMode(mode, 0, 24);
    }
    
    // -> AGGREGATION_PHASE
    else if (commandHeader == COMMAND_SET_END_DETECTION_PARAMETER_AGGREGATION) {
        if (fillDeviceArgumentList) {
            setFunction("set End Detection Aggregation Parameter", 9, 0);
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
    }
    else if (commandHeader == COMMAND_GET_END_DETECTION_PARAMETER_AGGREGATION) {
        if (fillDeviceArgumentList) {
            setFunction("get End Detection Aggregation Parameter", 0, 9);
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
