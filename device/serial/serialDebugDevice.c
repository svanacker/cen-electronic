#include <stdbool.h>

#include "serialDebugDevice.h"
#include "serialDebugDeviceInterface.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"

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

void deviceSerialDebugHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    // Serial Input Buffers
    if (commandHeader == COMMAND_SERIAL_INPUT_BUFFERS) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_INPUT_BUFFERS);
        printSerialInputBuffers(getInfoOutputStreamLogger());         
    }
    else if (commandHeader == COMMAND_SERIAL_LIST) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_LIST);
        printSerialLinkList(getInfoOutputStreamLogger());         
    }
    else if (commandHeader == COMMAND_SERIAL_CHAR_OUTPUT) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_CHAR_OUTPUT);
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        checkIsSeparator(inputStream);
        char c = readHex2(inputStream);
        serialPutc(serialPort, c);
    }
    else if (commandHeader == COMMAND_SERIAL_CHAR_ARRAY_OUTPUT) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_CHAR_ARRAY_OUTPUT);
        enum SerialPort serialPort = (enum SerialPort) readHex2(inputStream);
        int i;
        for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
            checkIsSeparator(inputStream);
            char c = readHex2(inputStream);
            if (c != 0) {
                serialPutc(serialPort, c);
            }
        }
    }
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
