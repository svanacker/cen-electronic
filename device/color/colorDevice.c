#include <stdbool.h>
#include <stdlib.h>

#include "colorDevice.h"
#include "colorDeviceInterface.h"

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

#include "../../drivers/colorSensor/colorSensor.h"
#include "../../drivers/colorSensor/colorSensorDebug.h"

static ColorSensor* colorSensor;

void deviceColorSensorInit(void) {
    if (colorSensor == NULL) {
        writeError(COLOR_SENSOR_NULL);
        return;
    }
    colorSensor->colorSensorInit(colorSensor);
}

void deviceColorSensorShutDown(void) {
}

bool deviceColorSensorIsOk(void) {
    return true;
}

void deviceColorSensorHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_COLOR_SENSOR_READ) {
        ackCommand(outputStream, COLOR_SENSOR_DEVICE_HEADER, COMMAND_COLOR_SENSOR_READ);
        Color* color = colorSensor->colorSensorReadValue(colorSensor);
        appendHex4(outputStream, color->R);
        appendSeparator(outputStream);
        appendHex4(outputStream, color->G);
        appendSeparator(outputStream);
        appendHex4(outputStream, color->B);
    }
    else if (commandHeader == COMMAND_COLOR_SENSOR_READ_TYPE) {
        ackCommand(outputStream, COLOR_SENSOR_DEVICE_HEADER, COMMAND_COLOR_SENSOR_READ_TYPE);
        enum ColorType colorType = colorSensor->colorSensorFindColorType(colorSensor);
        appendHex2(outputStream, colorType);
    }
    else if (commandHeader == COMMAND_COLOR_SENSOR_DEBUG) {
        ackCommand(outputStream, COLOR_SENSOR_DEVICE_HEADER, COMMAND_COLOR_SENSOR_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        printColorSensorTable(debugOutputStream, colorSensor);
    }
    /** Only for PC */
    else if (commandHeader == COMMAND_COLOR_SENSOR_WRITE) {
        ackCommand(outputStream, COLOR_SENSOR_DEVICE_HEADER, COMMAND_COLOR_SENSOR_WRITE);
        colorSensor->color->R = readHex4(inputStream);
        checkIsSeparator(inputStream);
        colorSensor->color->G = readHex4(inputStream);
        checkIsSeparator(inputStream);
        colorSensor->color->B = readHex4(inputStream);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceColorSensorInit,
    .deviceShutDown = &deviceColorSensorShutDown,
    .deviceIsOk = &deviceColorSensorIsOk,
    .deviceHandleRawData = &deviceColorSensorHandleRawData,
};

DeviceDescriptor* getColorSensorDeviceDescriptor(ColorSensor* colorSensorParam) {
    colorSensor = colorSensorParam;
    return &descriptor;
}
