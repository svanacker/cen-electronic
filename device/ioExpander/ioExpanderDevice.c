#include "ioExpanderDevice.h"
#include "ioExpanderDeviceInterface.h"

#include <stdbool.h>

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

void deviceIOExpanderInit(void) {
    
}

void deviceIOExpanderShutDown(void) {
}

bool deviceIOExpanderIsOk(void) {
    return true;
}

void deviceIOExpanderHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
}


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceIOExpanderInit,
    .deviceShutDown = &deviceIOExpanderShutDown,
    .deviceIsOk = &deviceIOExpanderIsOk,
    .deviceHandleRawData = &deviceIOExpanderHandleRawData,
};

DeviceDescriptor* getIOExpanderDeviceDescriptor(void) {
    return &descriptor;
}
