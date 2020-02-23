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

static LedArray* ledArray;

void deviceLedInit(void) {
    if (ledArray == NULL) {
        writeError(LED_ARRAY_NULL);
        return;
    }
    ledArray->ledArrayInit(ledArray);
}

void deviceLedShutDown(void) {
}

bool deviceLedIsOk(void) {
    return true;
}

void deviceLedHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    /** Only for PC */
    if (commandHeader == COMMAND_LED_WRITE) {
        ackCommand(outputStream, COLOR_SENSOR_DEVICE_HEADER, COMMAND_LED_WRITE);
        /*
        unsigned charIndex = readHex2(inputStream);
        appendHex2(outputStream, ledArray);
        colorSensor->color->R = readHex4(inputStream);
        checkIsSeparator(inputStream);
        colorSensor->color->G = readHex4(inputStream);
        checkIsSeparator(inputStream);
        colorSensor->color->B = readHex4(inputStream);
        */
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLedInit,
    .deviceShutDown = &deviceLedShutDown,
    .deviceIsOk = &deviceLedIsOk,
    .deviceHandleRawData = &deviceLedHandleRawData,
};

DeviceDescriptor* getLedDeviceDescriptor(LedArray* ledArrayParam) {
    ledArray = ledArrayParam;
    return &descriptor;
}
