#include "eepromDevice.h"
#include "eepromDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../drivers/eeprom/24c16.h"

void deviceEepromInit(void) {
}

void deviceEepromShutDown(void) {
}

bool isEepromDeviceOk(void) {
    return true;
}

void deviceEepromHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream){
    int data = 0;
    long address = 0;
    if (header == COMMAND_READ_DATA_EEPROM) {
        address = readHex4(inputStream);
        appendHex2(outputStream, eepromReadInt(address));
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_DATA_EEPROM);
    } else if (header == COMMAND_WRITE_DATA_EEPROM) {
        address = readHex4(inputStream);
        data = readHex2(inputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_DATA_EEPROM);
        eepromWriteint(address,data);
    } else if (header == COMMAND_READ_BLOC_EEPROM) {
        address = readHex4(inputStream);
        appendHex2(outputStream, eepromReadInt(address));
        appendHex2(outputStream, eepromReadInt(address+1));
        appendHex2(outputStream, eepromReadInt(address+2));
        appendHex2(outputStream, eepromReadInt(address+3));
        appendHex2(outputStream, eepromReadInt(address+4));
        appendHex2(outputStream, eepromReadInt(address+5));
        appendHex2(outputStream, eepromReadInt(address+6));
        appendHex2(outputStream, eepromReadInt(address+7));
        appendCR(outputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_BLOC_EEPROM);
    } else if (header == COMMAND_WRITE_BLOC_EEPROM) {
        address = readHex4(inputStream);
        data = readHex2(inputStream);
        eepromWriteint(address,data);
        data = readHex2(inputStream);
        eepromWriteint(address+1,data);
        data = readHex2(inputStream);
        eepromWriteint(address+2,data);
        data = readHex2(inputStream);
        eepromWriteint(address+3,data);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_BLOC_EEPROM);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceEepromInit,
    .deviceShutDown = &deviceEepromShutDown,
    .deviceIsOk = &isEepromDeviceOk,
    .deviceHandleRawData = &deviceEepromHandleRawData,
};

DeviceDescriptor* getEepromDeviceDescriptor() {
    return &descriptor;
}