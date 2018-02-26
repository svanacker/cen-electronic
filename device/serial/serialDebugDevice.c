#include <stdbool.h>
#include <stdlib.h>

#include "serialDebugDevice.h"
#include "serialDebugDeviceInterface.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/loggerDebug.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialInputInterrupt.h"
#include "../../common/serial/serialLink.h"
#include "../../common/serial/serialLinkDebug.h"
#include "../../common/serial/serialLinkList.h"

#include "../../common/string/cenString.h"

#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"
#include "../../device/deviceUsage.h"

void deviceSerialDebugInit(void) {
}

void deviceSerialDebugShutDown(void) {
}

bool deviceSerialDebugIsOk(void) {
    return true;
}

void deviceSerialDebugHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // Serial Input Buffers
    if (commandHeader == COMMAND_SERIAL_DEBUG) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_DEBUG);
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        SerialLink* serialLink = getSerialLinkBySerialPort(serialPort);
        printSerialLinkBuffer(getInfoOutputStreamLogger(), serialLink);
    }
    else if (commandHeader == COMMAND_SERIAL_CLEAR) {
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        SerialLink* serialLink = getSerialLinkBySerialPort(serialPort);
        clearSerialLinkBuffer(serialLink);
        // We ack at the end because we just clear the buffer !
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_CLEAR);
    }
    else if (commandHeader == COMMAND_SERIAL_LIST) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_LIST);
        printSerialLinkList(getInfoOutputStreamLogger());         
    }
    // OUTPUT
    else if (commandHeader == COMMAND_SERIAL_CHAR_OUTPUT) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_CHAR_OUTPUT);
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        checkIsSeparator(inputStream);
        char c = readHex2(inputStream);
        SerialLink* serialLink = getSerialLinkBySerialPort(serialPort);
        StreamLink* streamLink = serialLink->streamLink;
        Buffer* outputBuffer = streamLink->outputBuffer;
        OutputStream* bufferOutputStream = getOutputStream(outputBuffer);
        append(bufferOutputStream, c);
        copyInputToOutputStream(&(outputBuffer->inputStream), streamLink->outputStream, NULL, COPY_ALL);
    }
    else if (commandHeader == COMMAND_SERIAL_CHAR_ARRAY_OUTPUT) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_CHAR_ARRAY_OUTPUT);
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        SerialLink* serialLink = getSerialLinkBySerialPort(serialPort);
        StreamLink* streamLink = serialLink->streamLink;
        Buffer* outputBuffer = streamLink->outputBuffer;
        OutputStream* bufferOutputStream = getOutputStream(outputBuffer);
        int i;
        for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
            checkIsSeparator(inputStream);
            char c = readHex2(inputStream);
            if (c != 0) {
                append(bufferOutputStream, c);
                copyInputToOutputStream(&(outputBuffer->inputStream), streamLink->outputStream, NULL, COPY_ALL);
            }
        }
    }
    // INPUT
    else if (commandHeader == COMMAND_SERIAL_CHAR_INPUT) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_CHAR_INPUT);
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        checkIsSeparator(inputStream);
        char c = readHex2(inputStream);
        SerialLink* serialLink = getSerialLinkBySerialPort(serialPort);
        StreamLink* streamLink = serialLink->streamLink;
        Buffer* inputBuffer = streamLink->inputBuffer;
        OutputStream* bufferOutputStream = getOutputStream(inputBuffer);
        append(bufferOutputStream, c);
    }
    else if (commandHeader == COMMAND_SERIAL_CHAR_ARRAY_INPUT) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_CHAR_ARRAY_INPUT);
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        SerialLink* serialLink = getSerialLinkBySerialPort(serialPort);
        StreamLink* streamLink = serialLink->streamLink;
        Buffer* inputBuffer = streamLink->inputBuffer;
        OutputStream* bufferOutputStream = getOutputStream(inputBuffer);
        int i;
        for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
            checkIsSeparator(inputStream);
            char c = readHex2(inputStream);
            if (c != 0) {
                append(bufferOutputStream, c);
            }
        }
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSerialDebugInit,
    .deviceShutDown = &deviceSerialDebugShutDown,
    .deviceIsOk = &deviceSerialDebugIsOk,
    .deviceHandleRawData = &deviceSerialDebugHandleRawData,
};

DeviceDescriptor* getSerialDebugDeviceDescriptor(void) {
    return &descriptor;
}
