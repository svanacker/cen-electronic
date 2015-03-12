#include "eepromDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getEepromDeviceName(void) {
    return "EEPROM";
}

#define EEPROM_DEVICE_READ_BLOCK_LENGTH   8
#define EEPROM_DEVICE_WRITE_BLOCK_LENGTH  4

int deviceEepromGetInterface(char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
	if (header == COMMAND_DUMP_TO_FILE_EEPROM) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("Dump Eeprom to File");
		}
		return 0;
	}
	else if (header == COMMAND_DUMP_TO_LOG_OUTPUT_STREAM_EEPROM) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("Dump Eeprom to log output Stream");
		}
		return 0;
	}
	else if (header == COMMAND_CLEAR_EEPROM) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("Clear Eeprom");
		}
		return 0;
	}
	else if (header == COMMAND_READ_DATA_EEPROM ) {
        if (fillDeviceArgumentList) {
            setFunction("Data Read", 1, 1);
            setArgumentUnsignedHex4(0, "address");
            setResultUnsignedHex2(0, "data");
        }
        return commandLengthValueForMode(mode, 4, 2);
    } else if (header == COMMAND_WRITE_DATA_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Date Write", 2, 0);
            setArgumentUnsignedHex4(0, "address");
            setArgumentUnsignedHex2(1, "data");
        }
        return commandLengthValueForMode(mode, 6, 0);

    } else if (header == COMMAND_READ_BLOCK_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Bloc Read", 1, EEPROM_DEVICE_READ_BLOCK_LENGTH + 1);
            setArgumentUnsignedHex4(0, "address");
            int i;
            for (i = 0; i < EEPROM_DEVICE_READ_BLOCK_LENGTH; i++) {
                setResultUnsignedHex2(i, "data");
            }
            setResultSeparator(EEPROM_DEVICE_READ_BLOCK_LENGTH);
        }
        return commandLengthValueForMode(mode, 4, EEPROM_DEVICE_READ_BLOCK_LENGTH * 2 + 1);

    } else if (header == COMMAND_WRITE_BLOCK_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Bloc Write", EEPROM_DEVICE_WRITE_BLOCK_LENGTH + 1, 0);
            setArgumentUnsignedHex4(0, "address");
            int i;
            for (i = 0; i < EEPROM_DEVICE_WRITE_BLOCK_LENGTH; i++) {
                setArgumentUnsignedHex2(i + 1, "data");
            }
        }
        return commandLengthValueForMode(mode, 4 + EEPROM_DEVICE_WRITE_BLOCK_LENGTH * 2, 0);
    }
	else if (header == COMMAND_INTENSIVE_TEST) {
		if (fillDeviceArgumentList) {
			setFunction("intensiveTest", 2, 1);
			setArgumentUnsignedHex4(0, "address");
			setArgumentUnsignedHex4(1, "length of test");
			setResultSignedHex2(0, "errors");
		}
		return commandLengthValueForMode(mode, 8, 2);
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
