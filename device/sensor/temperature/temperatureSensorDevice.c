#include <stdbool.h>

#include "temperatureSensor.h"
#include "temperatureSensorDevice.h"
#include "temperatureSensorDeviceInterface.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/i2c/i2cCommon.h"

#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/sensor/temperature/temperature.h"

#include "../../../device/device.h"

static Temperature* temperature;

void deviceTemperatureSensorInit(void) {
}

void deviceTemperatureSensorShutDown(void) {
}

bool isTemperatureSensorDeviceOk(void) {
    return true;
}

void deviceTemperatureSensorHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream){
    if (header == COMMAND_READ_TEMPERATURE_SENSOR) {
        ackCommand(outputStream, TEMPERATURE_SENSOR_DEVICE_HEADER, COMMAND_READ_TEMPERATURE_SENSOR);
        unsigned char value = (unsigned char) temperature->readSensorValue(temperature);
        appendHex2(outputStream, value);
    } else if (header == COMMAND_SET_TEMPERATURE_SENSOR_ALERT) {
        char temperatureSensorAlert = readHex2(inputStream);
        ackCommand(outputStream, TEMPERATURE_SENSOR_DEVICE_HEADER, COMMAND_SET_TEMPERATURE_SENSOR_ALERT);
        temperature->writeAlertLimit(temperature, temperatureSensorAlert);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTemperatureSensorInit,
    .deviceShutDown = &deviceTemperatureSensorShutDown,
    .deviceIsOk = &isTemperatureSensorDeviceOk,
    .deviceHandleRawData = &deviceTemperatureSensorHandleRawData,
};

DeviceDescriptor* getTemperatureSensorDeviceDescriptor(Temperature* temperatureParam) {
    temperature = temperatureParam;
    return &descriptor;
}
