#include "eepromDevice.h"
#include "eepromDeviceInterface.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

static Eeprom* eeprom_;

void _deviceEepromCheckInitialized() {
    if (eeprom_ == NULL) {
        writeError(EEPROM_NULL);
    }
    if (!isEepromInitialized(eeprom_)) {
        writeError(EEPROM_NOT_INITIALIZED);
    }
}

void deviceEepromInit(void) {
    _deviceEepromCheckInitialized();
}

void deviceEepromShutDown(void) {
}

bool isEepromDeviceOk(void) {
    // TODO : Check by reading a value in the EEPROM
    return true;
}

void deviceEepromHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream){
    _deviceEepromCheckInitialized();
	if (commandHeader == COMMAND_DUMP_TO_FILE_EEPROM) {
		ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_DUMP_TO_FILE_EEPROM);
		dumpEeprom(eeprom_);
	}
    if (commandHeader == COMMAND_READ_DATA_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_DATA_EEPROM);
        unsigned long address = readHex4(inputStream);
        char value = eeprom_->eepromReadChar(eeprom_, address);
        appendHex2(outputStream, value);
    } else if (commandHeader == COMMAND_WRITE_DATA_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_DATA_EEPROM);
        unsigned long address = readHex4(inputStream);
        int data = readHex2(inputStream);
        eeprom_->eepromWriteChar(eeprom_, address, data);
    } else if (commandHeader == COMMAND_READ_BLOCK_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_BLOCK_EEPROM);
        unsigned long address = readHex4(inputStream);
        int index;
        for (index = 0; index < 8; index++) {
            char value = eeprom_->eepromReadChar(eeprom_, address + index);
            appendHex2(outputStream, value);
        }
    } else if (commandHeader == COMMAND_WRITE_BLOCK_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_BLOCK_EEPROM);
        unsigned long address = readHex4(inputStream);
        char data;
        int index;
        for (index = 0; index < 4; index++) {
            data = readHex2(inputStream);
            eeprom_->eepromWriteChar(eeprom_, address + index, data);
        }
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceEepromInit,
    .deviceShutDown = &deviceEepromShutDown,
    .deviceIsOk = &isEepromDeviceOk,
    .deviceHandleRawData = &deviceEepromHandleRawData,
};

DeviceDescriptor* getEepromDeviceDescriptor(Eeprom* eepromParam) {
    eeprom_ = eepromParam;
    return &descriptor;
}
