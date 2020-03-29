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
