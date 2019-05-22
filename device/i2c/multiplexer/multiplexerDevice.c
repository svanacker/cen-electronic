#include "multiplexerDevice.h"
#include "multiplexerDeviceInterface.h"

#include <stdbool.h>

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/pin.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/device.h"
#include "../../../device/deviceDescriptor.h"

#include "../../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../../drivers/i2c/multiplexer/multiplexerDebug.h"

// FORWARD DECLARATION
MultiplexerList* getMultiplexerListFromDeviceDescriptor(DeviceDescriptor* deviceDescriptor);

static DeviceDescriptor descriptor;

void deviceMultiplexerInit(void) {
    
}

void deviceMultiplexerShutDown(void) {
}

bool deviceMultiplexerIsOk(void) {
    return true;
}

/**
 * @private
 */
Multiplexer* readMultiplexerFromInputStream(InputStream* inputStream) {
    unsigned int multiplexerIndex = readHex2(inputStream);

    MultiplexerList* multiplexerList = getMultiplexerListFromDeviceDescriptor(&descriptor);

    Multiplexer* multiplexer = getMultiplexerByIndex(multiplexerList, multiplexerIndex);

    return multiplexer;
}


void deviceMultiplexerHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ALL CHANNELS
    if (commandHeader == COMMAND_MULTIPLEXER_READ_CHANNELS_MASK) {
        ackCommand(outputStream, MULTIPLEXER_HEADER, COMMAND_MULTIPLEXER_READ_CHANNELS_MASK);
        Multiplexer* multiplexer = readMultiplexerFromInputStream(inputStream);

        unsigned char value = multiplexer->multiplexerReadChannelsMask(multiplexer);
        appendHex2(outputStream, value);
    }
    else if (commandHeader == COMMAND_MULTIPLEXER_WRITE_CHANNELS_MASK) {
        ackCommand(outputStream, MULTIPLEXER_HEADER, COMMAND_MULTIPLEXER_WRITE_CHANNELS_MASK);
        Multiplexer* multiplexer = readMultiplexerFromInputStream(inputStream);
        checkIsSeparator(inputStream);
        unsigned char newValue = readHex2(inputStream);

        multiplexer->multiplexerWriteChannelsMask(multiplexer, newValue);
    }
    // SINGLE CHANNEL
    else if (commandHeader == COMMAND_MULTIPLEXER_READ_SINGLE_CHANNEL) {
        ackCommand(outputStream, MULTIPLEXER_HEADER, COMMAND_MULTIPLEXER_READ_SINGLE_CHANNEL);

        Multiplexer* multiplexer = readMultiplexerFromInputStream(inputStream);

        checkIsSeparator(inputStream);

        unsigned int ioIndex = readHex2(inputStream);
        bool value = multiplexer->multiplexerGetChannelEnable (multiplexer, ioIndex);
        appendHex(outputStream, (unsigned char) value);
    }
    else if (commandHeader == COMMAND_MULTIPLEXER_READ_SINGLE_CHANNEL) {
        ackCommand(outputStream, MULTIPLEXER_HEADER, COMMAND_MULTIPLEXER_READ_SINGLE_CHANNEL);

        Multiplexer* multiplexer = readMultiplexerFromInputStream(inputStream);

        checkIsSeparator(inputStream);

        unsigned int ioIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool newValue = (bool) readHex(inputStream);
        multiplexer->multiplexerSetChannelEnable(multiplexer, ioIndex, newValue);
    }
    // DEBUG
    else if (commandHeader == COMMAND_MULTIPLEXER_DEBUG) {
        ackCommand(outputStream, MULTIPLEXER_HEADER, COMMAND_MULTIPLEXER_DEBUG);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();

        MultiplexerList* multiplexerList = getMultiplexerListFromDeviceDescriptor(&descriptor);

        printMultiplexerTable(debugOutputStream, multiplexerList);
    }
}

MultiplexerList* getMultiplexerListFromDeviceDescriptor(DeviceDescriptor* deviceDescriptor) {
    return (MultiplexerList*)deviceDescriptor->object;
}


DeviceDescriptor* getMultiplexerDeviceDescriptor(MultiplexerList* multiplexerList) {
    initDeviceDescriptor(&descriptor,
        &deviceMultiplexerInit,
        &deviceMultiplexerShutDown,
        &deviceMultiplexerIsOk,
        &deviceMultiplexerHandleRawData,
        (int*) multiplexerList);

    return &descriptor;
}
