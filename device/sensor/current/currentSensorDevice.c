#include <stdbool.h>

#include "currentSensor.h"
#include "currentSensorDevice.h"
#include "currentSensorDeviceInterface.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/i2c/i2cCommon.h"

#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/sensor/current/current.h"

#include "../../../device/device.h"

static Current* current;

void deviceCurrentSensorInit(void) {
}

void deviceCurrentSensorShutDown(void) {
}

bool isCurrentSensorDeviceOk(void) {
    return true;
}

void deviceCurrentSensorHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream){
    if (header == COMMAND_READ_CURRENT_SENSOR) {
        ackCommand(outputStream, CURRENT_SENSOR_DEVICE_HEADER, COMMAND_READ_CURRENT_SENSOR);
        unsigned int value = (unsigned int) current->readSensorValue(current);
        appendHex4(outputStream, value);
    } else if (header == COMMAND_SET_CURRENT_SENSOR_ALERT) {
        char currentSensorAlert = readHex2(inputStream);
        ackCommand(outputStream, CURRENT_SENSOR_DEVICE_HEADER, COMMAND_SET_CURRENT_SENSOR_ALERT);
        current->writeAlertLimit(current, currentSensorAlert);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceCurrentSensorInit,
    .deviceShutDown = &deviceCurrentSensorShutDown,
    .deviceIsOk = &isCurrentSensorDeviceOk,
    .deviceHandleRawData = &deviceCurrentSensorHandleRawData,
};

DeviceDescriptor* getCurrentSensorDeviceDescriptor(Current* currentParam) {
    current = currentParam;
    return &descriptor;
}
