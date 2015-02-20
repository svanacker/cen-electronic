#include "fileDevice.h"
#include "fileDeviceInterface.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

void deviceFileInit(void) {

}

void deviceFileShutDown(void) {
}

bool isFileDeviceOk(void) {
    return true;
}

void deviceFileHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream){
    if (commandHeader == COMMAND_SHOW_LIST_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_SHOW_LIST_FILE);
        // TODO
    } else if (commandHeader == COMMAND_SHOW_CONTENT_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_SHOW_CONTENT_FILE);
        unsigned int fileIndex = readHex2(inputStream);
        // TODO
    } else if (commandHeader == COMMAND_CREATE_NEW_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_CREATE_NEW_FILE);
        unsigned int fileIndex = readHex2(inputStream);
        // TODO
    } else if (commandHeader == COMMAND_DELETE_FILE) {
        ackCommand(outputStream, FILE_DEVICE_HEADER, COMMAND_DELETE_FILE);
        unsigned int fileIndex = readHex2(inputStream);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceFileInit,
    .deviceShutDown = &deviceFileShutDown,
    .deviceIsOk = &isFileDeviceOk,
    .deviceHandleRawData = &deviceFileHandleRawData,
};

DeviceDescriptor* getFileDeviceDescriptor() {
    return &descriptor;
}