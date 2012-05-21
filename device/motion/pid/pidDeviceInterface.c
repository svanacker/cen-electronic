#include "pidDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"

const char* getPIDDeviceName(void) {
    return "PID";
}

void fillArgumentForPlainPid() {
	setArgumentUnsignedHex2(0, "pidIdx");
	setArgumentUnsignedHex2(1, "p");
	setArgumentUnsignedHex2(2, "i");
	setArgumentUnsignedHex2(3, "d");
	setArgumentUnsignedHex2(4, "mI");
}

void fillForPlainEndDetectionParameter() {
	setArgumentUnsignedHex2(0, "absDPosIntFacThres");
	setArgumentUnsignedHex2(1, "maxUIntFacThres");
	setArgumentUnsignedHex2(2, "maxUIntConThres");
	setArgumentUnsignedHex2(3, "timeRangeAna");
	setArgumentUnsignedHex2(4, "noAnaAtStart");
}

int devicePIDGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (header == COMMAND_WRITE_PID) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setPID", 5);
				fillArgumentForPlainPid();
            }
            return 10;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setPID");
            }
            return 0;
        }
    } else if (header == COMMAND_READ_PID) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getPID", 1);
				setArgumentUnsignedHex2(0, "idx");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getPID", 5);
				fillArgumentForPlainPid();
            }
            return 10;
        }
    } else if (header == COMMAND_SET_END_DETECTION_PARAMETER) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setEndDetectParam", 5);
				fillForPlainEndDetectionParameter();
            }
            return 10;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setEndDetectParam");
            }
            return 0;
        }
    } else if (header == COMMAND_GET_END_DETECTION_PARAMETER) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("getEndDetectParam");
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getEndDetectParam", 5);
				fillForPlainEndDetectionParameter();
            }
            return 10;
        }
    } else if (header == COMMAND_SEND_DEBUG_DATA_PID) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("sendDbgDataPid", 1);
				setArgumentUnsignedChar1(0, "idx");
            }
            return 1;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
					setFunction("sendDbgDataPid", 11);
					// _01001-00020-5678-40-200050008000
					setArgumentUnsignedChar1(0, "idx");
					setArgument(1, DEVICE_ARG_UNSIGNED_HEX_3, "pidTime");
					setArgumentUnsignedChar1(2, "pidTipe");
					setArgumentSeparator(3); 
					setArgument(4, DEVICE_ARG_SIGNED_HEX_5, "pos");
					setArgumentSeparator(5);
					setArgumentUnsignedHex4(6, "err");
					setArgumentSeparator(7);
					setArgumentUnsignedHex2(8, "u");
					setArgumentSeparator(9);
					setArgument(10, DEVICE_ARG_UNSIGNED_HEX_12, "time/absDelPosiInt/uIntegral");
            }
            return 32;
        }
    } else if (header == COMMAND_SEND_MOTION_PARAMETER) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("sendMotParam", 1);
				setArgumentUnsignedChar1(0, "idx");
            }
            return 1;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {	
					setFunction("sendMotParam", 10);
					setArgumentUnsignedChar1(0, "idx");
					setArgument(1, DEVICE_ARG_UNSIGNED_HEX_6, "a/s/smax");
					setArgumentSeparator(2);
					setArgument(3, DEVICE_ARG_UNSIGNED_HEX_8, "t1/t2/t3");
					setArgumentSeparator(4);
					setArgument(5, DEVICE_ARG_UNSIGNED_HEX_10, "p1/p2");
					setArgumentSeparator(6);
					setArgumentUnsignedChar1(7, "profileType");
					setArgumentUnsignedChar1(8, "motionType");
					setArgumentUnsignedChar1(9, "pidType");
            }
            return 32;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getPIDDeviceName,
    .deviceGetInterface = &devicePIDGetInterface
};

DeviceInterface* getPIDDeviceInterface() {
    return &deviceInterface;
}
