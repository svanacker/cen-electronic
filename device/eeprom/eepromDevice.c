#include "eepromDevice.h"
#include "eepromDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../drivers/eeprom/24c16.h"

static Eeprom* eeprom_;

void deviceEepromInit(void) {
}

void deviceEepromShutDown(void) {
}

bool isEepromDeviceOk(void) {
    return true;
}

void deviceEepromHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream){
    if (header == COMMAND_READ_DATA_EEPROM) {
        unsigned long address = readHex4(inputStream);
        signed int value = eeprom_->eepromReadInt(eeprom_, address);
        appendHex2(outputStream, value);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_DATA_EEPROM);
    } else if (header == COMMAND_WRITE_DATA_EEPROM) {
        unsigned long address = readHex4(inputStream);
        int data = readHex2(inputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_DATA_EEPROM);
        eeprom_->eepromWriteInt(eeprom_, address,data);
    } else if (header == COMMAND_READ_BLOC_EEPROM) {
        unsigned long address = readHex4(inputStream);
        int index;
        for (index = 0; index < 8; index++) {
            signed int value = eeprom_->eepromReadInt(eeprom_, address + index);
            appendHex2(outputStream, value);
        }
        appendCR(outputStream);
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_READ_BLOC_EEPROM);
    } else if (header == COMMAND_WRITE_BLOC_EEPROM) {
        unsigned long address = readHex4(inputStream);
        signed int data;
        int index;
        for (index = 0; index < 4; index++) {
            data = readHex2(inputStream);
            eeprom_->eepromWriteInt(eeprom_, address + index,data);
            delay100us(4);  // delay <=3 don't write correctly
        }
        ackCommand(outputStream, EEPROM_DEVICE_HEADER, COMMAND_WRITE_BLOC_EEPROM);
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