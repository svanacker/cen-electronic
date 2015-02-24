#include <stdbool.h>

#include "temperatureSensor.h"
#include "temperatureSensorDevice.h"
#include "temperatureSensorDeviceInterface.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/i2c/i2cCommon.h"

#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../device/device.h"

static I2cBus* temperatureI2cBus;

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
        unsigned char value = getTemperatureSensor(temperatureI2cBus);
        appendHex2(outputStream, value);
    } else if (header == COMMAND_SET_TEMPERATURE_SENSOR_ALERT) {
        char temperatureSensorAlert = readHex2(inputStream);
        ackCommand(outputStream, TEMPERATURE_SENSOR_DEVICE_HEADER, COMMAND_SET_TEMPERATURE_SENSOR_ALERT);
        setTemperatureAlertLimit(temperatureI2cBus, temperatureSensorAlert);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTemperatureSensorInit,
    .deviceShutDown = &deviceTemperatureSensorShutDown,
    .deviceIsOk = &isTemperatureSensorDeviceOk,
    .deviceHandleRawData = &deviceTemperatureSensorHandleRawData,
};

DeviceDescriptor* getTemperatureSensorDeviceDescriptor(I2cBus* i2cBus) {
    // TODO : Remove Static value
    temperatureI2cBus = i2cBus;
    return &descriptor;
}
