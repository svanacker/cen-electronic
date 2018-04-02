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

#include "../../device/device.h"

#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"

static IOExpander* ioExpander;

void deviceIOExpanderInit(void) {
    
}

void deviceIOExpanderShutDown(void) {
}

bool deviceIOExpanderIsOk(void) {
    return true;
}

void deviceIOExpanderHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ALL BITS
    if (commandHeader == COMMAND_IO_EXPANDER_READ_VALUE) {
        ackCommand(outputStream, IO_DEVICE_HEADER, COMMAND_IO_EXPANDER_READ_VALUE);
        unsigned char value = ioExpander->ioExpanderReadValue(ioExpander);
        appendHex2(outputStream, value);
    }
    else if (commandHeader == COMMAND_IO_EXPANDER_WRITE_VALUE) {
        ackCommand(outputStream, IO_DEVICE_HEADER, COMMAND_IO_EXPANDER_WRITE_VALUE);
        unsigned char newValue = readHex2(inputStream);
        ioExpander->ioExpanderWriteValue(ioExpander, newValue);
    }
    // SINGLE BIT
    else if (commandHeader == COMMAND_IO_EXPANDER_READ_SINGLE_BIT) {
        ackCommand(outputStream, IO_DEVICE_HEADER, COMMAND_IO_EXPANDER_READ_SINGLE_BIT);
        unsigned int ioIndex = readHex2(inputStream);
        bool value = ioExpander->ioExpanderReadSingleValue(ioExpander, ioIndex);
        appendHex(outputStream, (unsigned char) value);
    }
    else if (commandHeader == COMMAND_IO_EXPANDER_WRITE_SINGLE_BIT) {
        ackCommand(outputStream, IO_DEVICE_HEADER, COMMAND_IO_EXPANDER_WRITE_SINGLE_BIT);
        unsigned int ioIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool newValue = (bool) readHex(inputStream);
        ioExpander->ioExpanderWriteSingleValue(ioExpander, ioIndex, newValue);
    }
    // DEBUG
    else if (commandHeader == COMMAND_IO_EXPANDER_DEBUG) {
        ackCommand(outputStream, IO_DEVICE_HEADER, COMMAND_IO_EXPANDER_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        printIOExpanderStatesTable(debugOutputStream, ioExpander);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceIOExpanderInit,
    .deviceShutDown = &deviceIOExpanderShutDown,
    .deviceIsOk = &deviceIOExpanderIsOk,
    .deviceHandleRawData = &deviceIOExpanderHandleRawData,
};

DeviceDescriptor* getIOExpanderDeviceDescriptor(IOExpander* ioExpanderParam) {
    ioExpander = ioExpanderParam;
    return &descriptor;
}
