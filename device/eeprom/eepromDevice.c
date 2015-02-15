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
    return true;
}

void deviceEepromHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream){
    _deviceEepromCheckInitialized();
    if (commandHeader == COMMAND_READ_DATA_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_DATA_EEPROM);
        unsigned long address = readHex4(inputStream);
        signed int value = eeprom_->eepromReadInt(eeprom_, address);
        appendHex2(outputStream, value);
    } else if (commandHeader == COMMAND_WRITE_DATA_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_DATA_EEPROM);
        unsigned long address = readHex4(inputStream);
        int data = readHex2(inputStream);
        eeprom_->eepromWriteInt(eeprom_, address, data);
    } else if (commandHeader == COMMAND_READ_BLOCK_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_BLOCK_EEPROM);
        unsigned long address = readHex4(inputStream);
        int index;
        for (index = 0; index < 8; index++) {
            signed int value = eeprom_->eepromReadInt(eeprom_, address + index);
            appendHex2(outputStream, value);
        }
    } else if (commandHeader == COMMAND_WRITE_BLOCK_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_BLOCK_EEPROM);
        unsigned long address = readHex4(inputStream);
        signed int data;
        int index;
        for (index = 0; index < 4; index++) {
            data = readHex2(inputStream);
            eeprom_->eepromWriteInt(eeprom_, address + index, data);
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