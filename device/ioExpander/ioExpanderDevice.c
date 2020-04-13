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
#include "../../device/deviceDescriptor.h"

#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"

// FORWARD DECLARATION
IOExpanderList* getIOExpanderListFromDeviceDescriptor(DeviceDescriptor* deviceDescriptor);

static DeviceDescriptor descriptor;

void deviceIOExpanderInit(void) {

}

void deviceIOExpanderShutDown(void) {
}

bool deviceIOExpanderIsOk(void) {
    return true;
}

/**
 * @private
 */
IOExpander* readIOExpanderFromInputStream(InputStream* inputStream) {
    unsigned int ioExpanderIndex = readHex2(inputStream);

    IOExpanderList* ioExpanderList = getIOExpanderListFromDeviceDescriptor(&descriptor);

    IOExpander* ioExpander = getIOExpanderByIndex(ioExpanderList, ioExpanderIndex);

    return ioExpander;
}

void deviceIOExpanderHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ALL BITS
    if (commandHeader == COMMAND_IO_EXPANDER_READ_VALUE) {
        ackCommand(outputStream, IO_DEVICE_EXPANDER_HEADER, COMMAND_IO_EXPANDER_READ_VALUE);
        IOExpander* ioExpander = readIOExpanderFromInputStream(inputStream);

        unsigned char value = ioExpander->ioExpanderReadValue(ioExpander);
        appendHex2(outputStream, value);
    } else if (commandHeader == COMMAND_IO_EXPANDER_WRITE_VALUE) {
        ackCommand(outputStream, IO_DEVICE_EXPANDER_HEADER, COMMAND_IO_EXPANDER_WRITE_VALUE);
        IOExpander* ioExpander = readIOExpanderFromInputStream(inputStream);
        checkIsSeparator(inputStream);
        unsigned char newValue = readHex2(inputStream);

        ioExpander->ioExpanderWriteValue(ioExpander, newValue);
    }// SINGLE BIT
    else if (commandHeader == COMMAND_IO_EXPANDER_READ_SINGLE_BIT) {
        ackCommand(outputStream, IO_DEVICE_EXPANDER_HEADER, COMMAND_IO_EXPANDER_READ_SINGLE_BIT);

        IOExpander* ioExpander = readIOExpanderFromInputStream(inputStream);

        checkIsSeparator(inputStream);

        unsigned int ioIndex = readHex2(inputStream);
        bool value = ioExpander->ioExpanderReadSingleValue(ioExpander, ioIndex);
        appendHex(outputStream, (unsigned char) value);
    } else if (commandHeader == COMMAND_IO_EXPANDER_WRITE_SINGLE_BIT) {
        ackCommand(outputStream, IO_DEVICE_EXPANDER_HEADER, COMMAND_IO_EXPANDER_WRITE_SINGLE_BIT);

        IOExpander* ioExpander = readIOExpanderFromInputStream(inputStream);

        checkIsSeparator(inputStream);

        unsigned int ioIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool newValue = (bool) readHex(inputStream);
        ioExpander->ioExpanderWriteSingleValue(ioExpander, ioIndex, newValue);
    }// DEBUG
    else if (commandHeader == COMMAND_IO_EXPANDER_DEBUG) {
        ackCommand(outputStream, IO_DEVICE_EXPANDER_HEADER, COMMAND_IO_EXPANDER_DEBUG);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();

        IOExpanderList* ioExpanderList = getIOExpanderListFromDeviceDescriptor(&descriptor);

        printIOExpanderStatesTable(debugOutputStream, ioExpanderList);
    }
}

IOExpanderList* getIOExpanderListFromDeviceDescriptor(DeviceDescriptor* deviceDescriptor) {
    return (IOExpanderList*) deviceDescriptor->object;
}

DeviceDescriptor* getIOExpanderDeviceDescriptor(IOExpanderList* ioExpanderList) {
    initDeviceDescriptor(&descriptor,
            &deviceIOExpanderInit,
            &deviceIOExpanderShutDown,
            &deviceIOExpanderIsOk,
            &deviceIOExpanderHandleRawData,
            (int*) ioExpanderList);

    return &descriptor;
}
