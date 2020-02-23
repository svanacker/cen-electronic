#include "ioDevice.h"
#include "ioDeviceInterface.h"

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

#include "../../device/device.h"
#include "../../device/deviceDescriptor.h"

#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"

static DeviceDescriptor descriptor;

void deviceIOInit(void) {
    
}

void deviceIOShutDown(void) {
}

bool deviceIOIsOk(void) {
    return true;
}

void deviceIOHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ALL BITS
    if (commandHeader == COMMAND_IO_READ) {
        ackCommand(outputStream, IO_HEADER, COMMAND_IO_READ);
        unsigned char pinIndex = readHex2(inputStream);
        bool value = getPinValue(pinIndex);
        appendBool(outputStream, value);
    }
    else if (commandHeader == COMMAND_IO_WRITE) {
        ackCommand(outputStream, IO_HEADER, COMMAND_IO_WRITE);
        unsigned char pinIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool newValue = readBool(inputStream);
        setPinValue(pinIndex, newValue);
    }
}

DeviceDescriptor* getIODeviceDescriptor() {
    initDeviceDescriptor(&descriptor,
        &deviceIOInit,
        &deviceIOShutDown,
        &deviceIOIsOk,
        &deviceIOHandleRawData,
        NULL);

    return &descriptor;
}
