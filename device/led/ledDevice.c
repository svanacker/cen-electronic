#include <stdbool.h>
#include <stdlib.h>

#include "ledDevice.h"
#include "ledDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/error/error.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/led/led.h"

// FORWARD DECLARATION
LedArray* getLedArrayFromDeviceDescriptor(void);

void deviceLedInit(void) {
    /*
    LedArray* ledArray = getLedArrayFromDeviceDescriptor();
    if (ledArray == NULL) {
        writeError(LED_ARRAY_NULL);
        return;
    }
    ledArray->ledArrayInit(ledArray);
    */
}

void deviceLedShutDown(void) {
}

bool deviceLedIsOk(void) {
    return true;
}

void deviceLedHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // SPECIFIC LED
    if (commandHeader == COMMAND_LED_WRITE) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_WRITE);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        unsigned char ledIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned int r = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned int g = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned int b = readHex2(inputStream);
        ledArray->ledArrayWriteValue(ledArray, ledIndex, r, g, b);
    }
    else if (commandHeader == COMMAND_LED_RED) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_RED);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        unsigned char ledIndex = readHex2(inputStream);
        ledArray->ledArrayWriteValue(ledArray, ledIndex, 0xFF, 0, 0);
    }
    else if (commandHeader == COMMAND_LED_GREEN) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_GREEN);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        unsigned char ledIndex = readHex2(inputStream);
        ledArray->ledArrayWriteValue(ledArray, ledIndex, 0x00, 0xFF, 0);
    }
    else if (commandHeader == COMMAND_LED_BLUE) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_BLUE);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        unsigned char ledIndex = readHex2(inputStream);
        ledArray->ledArrayWriteValue(ledArray, ledIndex, 0, 0, 0xFF);
    }
    // All LEDS
    else if (commandHeader == COMMAND_LED_CLEAR_ALL) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_CLEAR_ALL);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        int count = ledArray->ledCount;
        int i;
        for (i = 0; i < count; i++) {
            ledArray->ledArrayWriteValue(ledArray, i, 0, 0, 0);
        }
    }
    else if (commandHeader == COMMAND_LED_ALL_ON) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_ALL_ON);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        int count = ledArray->ledCount;
        int i;
        for (i = 0; i < count; i++) {
            ledArray->ledArrayWriteValue(ledArray, i, 0xFF, 0xFF, 0xFF);
        }
    }
    else if (commandHeader == COMMAND_LED_ALL_RED) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_ALL_RED);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        int count = ledArray->ledCount;
        int i;
        for (i = 0; i < count; i++) {
            ledArray->ledArrayWriteValue(ledArray, i, 0xFF, 0x00, 0x00);
        }
    }
    else if (commandHeader == COMMAND_LED_ALL_GREEN) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_ALL_GREEN);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        int count = ledArray->ledCount;
        int i;
        for (i = 0; i < count; i++) {
            ledArray->ledArrayWriteValue(ledArray, i, 0x00, 0xFF, 0x00);
        }
    }
    else if (commandHeader == COMMAND_LED_ALL_BLUE) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_ALL_BLUE);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        int count = ledArray->ledCount;
        int i;
        for (i = 0; i < count; i++) {
            ledArray->ledArrayWriteValue(ledArray, i, 0x00, 0x00, 0xFF);
        }
    }
    // DISTANCE
    else if (commandHeader == COMMAND_LED_ALL_AS_DISTANCE) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_LED_ALL_AS_DISTANCE);
        LedArray* ledArray = getLedArrayFromDeviceDescriptor();
        unsigned char distance = readHex2(inputStream);
        int count = ledArray->ledCount;
        int i;
        for (i = 0; i < count; i++) {
            setLedColorAsDistance(ledArray, i, distance);
        }
    }
}

static DeviceDescriptor descriptor;

LedArray* getLedArrayFromDeviceDescriptor(void) {
    return (LedArray*) descriptor.object;
}

DeviceDescriptor* getLedDeviceDescriptor(LedArray* ledArrayParam) {
    initDeviceDescriptor(&descriptor,
            &deviceLedInit,
            &deviceLedShutDown,
            &deviceLedIsOk,
            &deviceLedHandleRawData,
            (int*) ledArrayParam);
    return &descriptor;
}
