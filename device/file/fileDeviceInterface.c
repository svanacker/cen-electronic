#include "fileDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getFileDeviceName(void) {
    return "FILE/FAT";
}

int deviceFileGetInterface(char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    if (header == COMMAND_CREATE_FILE_SYSTEM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Create File System");
        }
        return 0;
    }
    else if (header == COMMAND_GET_FREE_SPACE) {
        if (fillDeviceArgumentList) {
            setFunction("Get Free Space", 0, 1);
            setResultUnsignedHex4(0, "result");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    else if (header == COMMAND_SHOW_LIST_FILE ) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show File List");
        }
        return 0;
    } else if (header == COMMAND_SHOW_CONTENT_FILE) {
        if (fillDeviceArgumentList) {
            setFunction("Show File Content", 1, 0);
            setArgumentUnsignedHex2(0, "fileIndex");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (header == COMMAND_CREATE_NEW_FILE) {
        if (fillDeviceArgumentList) {
            setFunction("Create New File", 1, 0);
            setArgumentUnsignedHex2(0, "fileIndex");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (header == COMMAND_DELETE_FILE) {
        if (fillDeviceArgumentList) {
            setFunction("Delete File", 1, 0);
            setArgumentUnsignedHex2(0, "fileIndex");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = FILE_DEVICE_HEADER,
    .deviceGetName = &getFileDeviceName,
    .deviceGetInterface = &deviceFileGetInterface
};

DeviceInterface* getFileDeviceInterface(void) {
    return &deviceInterface;
}
