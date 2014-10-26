#include "eeprom.h"
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
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_DATA_EEPROM);
        appendHex2(outputStream, my_eeprom_read_int(address));
    } else if (header == COMMAND_WRITE_DATA_EEPROM) {
        address = readHex4(inputStream);
        data = readHex2(inputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_DATA_EEPROM);
        my_eeprom_write_int(address,data);
    } else if (header == COMMAND_READ_BUFFER_EEPROM) {
        appendHex4(outputStream, address);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_BUFFER_EEPROM);
        appendHex2(outputStream, my_eeprom_read_bloc(address));
    }
    else if (header == COMMAND_WRITE_BUFFER_EEPROM) {
        data = readHex2(inputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_BUFFER_EEPROM);
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