#include <stdbool.h>
#include <stdlib.h>

#include "batteryDevice.h"
#include "batteryDeviceInterface.h"

#include "../../common/clock/clock.h"
#include "../../common/error/error.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../drivers/battery/battery.h"

static Battery* battery;

void _deviceBatteryCheckInitialized() {
    if (battery == NULL) {
        writeError(BATTERY_NULL);
    }
    if (!isBatteryInitialized(battery)) {
        writeError(BATTERY_NOT_INITIALIZED);
    }
}

void deviceBatteryInit(void) {
    _deviceBatteryCheckInitialized();
}

void deviceBatteryShutDown(void) {
}

bool isBatteryDeviceOk(void) {
    return true;
}

void deviceBatteryHandleRawData(unsigned char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    _deviceBatteryCheckInitialized();
    if (header == COMMAND_READ_BATTERY) {
        ackCommand(outputStream, BATTERY_DEVICE_HEADER, COMMAND_READ_BATTERY);
        int batteryValue = battery->readBatteryValue(battery);
        appendHex4(outputStream, batteryValue);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceBatteryInit,
    .deviceShutDown = &deviceBatteryShutDown,
    .deviceIsOk = &isBatteryDeviceOk,
    .deviceHandleRawData = &deviceBatteryHandleRawData,
};

DeviceDescriptor* getBatteryDeviceDescriptor(Battery* batteryParam) {
    battery = batteryParam;
    return &descriptor;
}
