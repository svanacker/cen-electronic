#include "eepromDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getEepromDeviceName(void) {
    return "EEPROM";
}

int deviceEepromGetInterface(unsigned char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    if (header == COMMAND_DUMP_TO_FILE_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Dump Eeprom to File");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    if (header == COMMAND_RELOAD_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Reload Dump File to Eeprom (PC)");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (header == COMMAND_DUMP_TO_LOG_OUTPUT_STREAM_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Dump Eeprom to log output Stream");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
	else if (header == COMMAND_DUMP_PARTIAL_CONTENT_TO_LOG_OUTPUT_STREAM_EEPROM) {
		if (fillDeviceArgumentList) {
			setFunction("Dump Part of Eeprom to log output Stream", 3, 0);
			setArgumentUnsignedHex4(0, "startAddress");
			setArgumentSeparator(1);
			setArgumentUnsignedHex4(2, "length");
		}
		return commandLengthValueForMode(mode, 9, 0);
	}
	else if (header == COMMAND_FORMAT_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Clear Eeprom", 5, 0);
            setArgumentUnsignedHex4(0, "startAddress");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "length");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "clearValue");
        }
        return commandLengthValueForMode(mode, 12, 0);
    }
    else if (header == COMMAND_READ_BYTE_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Byte Read", 1, 1);
            setArgumentUnsignedHex4(0, "address");
            setResultUnsignedHex2(0, "byte");
        }
        return commandLengthValueForMode(mode, 4, 2);
    }
    else if (header == COMMAND_READ_INT_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Int Read", 1, 1);
            setArgumentUnsignedHex4(0, "address");
            setResultUnsignedHex4(0, "int");
        }
        return commandLengthValueForMode(mode, 4, 4);
    }
    else if (header == COMMAND_READ_FLOAT_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Float Read", 3, 1);
            setArgumentUnsignedHex4(0, "address");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "digitPrecision");
            setResultFloatHex4(0, "float (4)");
        }
        return commandLengthValueForMode(mode, 7, 4);
    }
    else if (header == COMMAND_WRITE_BYTE_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Byte Write", 3, 0);
            setArgumentUnsignedHex4(0, "address");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "data");
        }
        return commandLengthValueForMode(mode, 7, 0);
    }
    else if (header == COMMAND_WRITE_INT_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Int Write", 3, 0);
            setArgumentUnsignedHex4(0, "address");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "int");
        }
        return commandLengthValueForMode(mode, 9, 0);
    }
    else if (header == COMMAND_WRITE_FLOAT_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Float Write", 5, 0);
            setArgumentUnsignedHex4(0, "address");
            setArgumentSeparator(1);
            setArgumentFloatHex4(2, "float");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "digitPrecision");
        }
        return commandLengthValueForMode(mode, 12, 0);
    }
    else if (header == COMMAND_READ_BLOCK_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Bloc Read", 1, EEPROM_DEVICE_READ_BLOCK_LENGTH * 2 - 1);
            setArgumentUnsignedHex4(0, "address");
            int i;
            for (i = 0; i < EEPROM_DEVICE_READ_BLOCK_LENGTH; i++) {
                if (i > 0) {
                    setResultSeparator(i * 2 - 1);
                }
                setResultUnsignedHex2(i * 2, "data");
            }
        }
        return commandLengthValueForMode(mode, 4, EEPROM_DEVICE_READ_BLOCK_LENGTH * 3 - 1);

    }
    else if (header == COMMAND_WRITE_BLOCK_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Bloc Write", EEPROM_DEVICE_WRITE_BLOCK_LENGTH * 2 + 1, 0);
            setArgumentUnsignedHex4(0, "address");
            int i;
            for (i = 0; i < EEPROM_DEVICE_WRITE_BLOCK_LENGTH; i++) {
                setArgumentSeparator(i * 2 + 1);
                setArgumentUnsignedHex2(i * 2 + 2, "data");
            }
        }
        return commandLengthValueForMode(mode, 4 + EEPROM_DEVICE_WRITE_BLOCK_LENGTH * 3, 0);
    }
    else if (header == COMMAND_INTENSIVE_TEST) {
        if (fillDeviceArgumentList) {
            setFunction("intensiveTest", 3, 1);
            setArgumentUnsignedHex4(0, "address");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "length of test");
            setResultUnsignedHex4(0, "errors");
        }
        return commandLengthValueForMode(mode, 9, 4);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = EEPROM_DEVICE_HEADER,
    .deviceGetName = &getEepromDeviceName,
    .deviceGetInterface = &deviceEepromGetInterface
};

DeviceInterface* getEepromDeviceInterface(void) {
    return &deviceInterface;
}
