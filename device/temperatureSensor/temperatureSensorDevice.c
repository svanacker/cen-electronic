#include "temperatureSensor.h"
#include "temperatureSensorDevice.h"
#include "temperatureSensorDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

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
        appendDec(outputStream, getTemperatureSensor());
    } else if (header == COMMAND_SET_TEMPERATURE_SENSOR_ALERT) {
        char TemperatureSensorAlert = readHex2(inputStream);
        ackCommand(outputStream, TEMPERATURE_SENSOR_DEVICE_HEADER, COMMAND_SET_TEMPERATURE_SENSOR_ALERT);
        setTemperatureAlertLimit(TemperatureSensorAlert);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTemperatureSensorInit,
    .deviceShutDown = &deviceTemperatureSensorShutDown,
    .deviceIsOk = &isTemperatureSensorDeviceOk,
    .deviceHandleRawData = &deviceTemperatureSensorHandleRawData,
};

DeviceDescriptor* getTemperatureSensorDeviceDescriptor() {
    return &descriptor;
}
