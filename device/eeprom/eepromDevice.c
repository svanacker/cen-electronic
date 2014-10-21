#include <peripheral/legacy/i2c_legacy.h>

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
    char data = 0;
    if (header == COMMAND_READ_DATA_EEPROM) {
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_DATA_EEPROM);
        appendHex2(outputStream, data);
    } else if (header == COMMAND_WRITE_DATA_EEPROM) {
        data = readHex2(inputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_DATA_EEPROM);
    } else if (header == COMMAND_READ_BUFFER_EEPROM) {
        data = readHex2(inputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_BUFFER_EEPROM);
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