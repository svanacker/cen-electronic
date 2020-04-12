#include "ioDevice.h"
#include "ioDeviceInterface.h"

#include <stdbool.h>

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/pin.h"
#include "../../common/io/pinDebug.h"
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
PinList* getPinListFromDeviceDescriptor(void);

static DeviceDescriptor descriptor;

void deviceIOInit(void) {

}

void deviceIOShutDown(void) {
}

bool deviceIOIsOk(void) {
    return true;
}

void deviceIOHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    PinList* pinList = getPinListFromDeviceDescriptor();
    // ALL BITS
    if (commandHeader == COMMAND_IO_READ) {
        ackCommand(outputStream, IO_HEADER, COMMAND_IO_READ);
        unsigned char pinIndex = readHex2(inputStream);
        bool value = getPinValue(pinList, pinIndex);
        appendBool(outputStream, value);
    } else if (commandHeader == COMMAND_IO_WRITE) {
        ackCommand(outputStream, IO_HEADER, COMMAND_IO_WRITE);
        unsigned char pinIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool newValue = readBool(inputStream);
        setPinValue(pinList, pinIndex, newValue);
    } else if (commandHeader == COMMAND_IO_DEBUG) {
        ackCommand(outputStream, IO_HEADER, COMMAND_IO_DEBUG);
        printAllPinValues(pinList, getInfoOutputStreamLogger());
    } else if (commandHeader == COMMAND_IO_IS_INPUT) {
        ackCommand(outputStream, IO_HEADER, COMMAND_IO_IS_INPUT);
        unsigned char pinIndex = readHex2(inputStream);
        bool value = isPinInput(pinList, pinIndex);
        appendBool(outputStream, value);
    }
    else if (commandHeader == COMMAND_IO_SET_INPUT) {
        ackCommand(outputStream, IO_HEADER, COMMAND_IO_SET_INPUT);
        unsigned char pinIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool newValue = readBool(inputStream);
        setPinInput(pinList, pinIndex, newValue);
    }
}

DeviceDescriptor* getIODeviceDescriptor(PinList* pinList) {
    initDeviceDescriptor(&descriptor,
            &deviceIOInit,
            &deviceIOShutDown,
            &deviceIOIsOk,
            &deviceIOHandleRawData,
            (int*) pinList);

    return &descriptor;
}

PinList* getPinListFromDeviceDescriptor(void) {
    return (PinList*) (descriptor.object);
}
