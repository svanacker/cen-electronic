#include <stdlib.h>
#include <stdbool.h>

#include "deviceList.h"
#include "device.h"
#include "deviceDescriptor.h"
#include "deviceInterface.h"
#include "transmitMode.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../common/math/cenMath.h"

// Singleton
static DeviceList deviceList;

DeviceList* getDeviceList() {
    return &deviceList;
}

void initDeviceList(Device (*deviceListArray)[], unsigned char deviceListSize) {
    // TODO : Check Illegal Arguments
    deviceList.devices = deviceListArray;
    deviceList.size = 0;
    deviceList.maxSize = deviceListSize;
}

void clearDeviceList(void) {
    deviceList.devices = NULL;
    deviceList.size = 0;
    deviceList.maxSize = 0;
}

/**
 * @private
 */
Device* addDevice(DeviceInterface* deviceInterface,
        DeviceDescriptor* descriptor,
        TransmitMode transmitMode,
        int address,
        char* addressString) {
    if (deviceList.maxSize == 0) {
        writeError(DEVICES_LIST_NOT_INITIALIZED);
        return NULL;
    }

    unsigned char size = deviceList.size;
    if (size < deviceList.maxSize) {
        Device* device = getDevice(size);
        // get a pointer on a device already allocated (because we provide at init a pointer on an array of device
        device->deviceInterface = deviceInterface;
        device->descriptor = descriptor;
        device->transmitMode = transmitMode;
        device->address = address;
        device->addressString = addressString;
        deviceList.size++;
        return device;
    } else {
        writeError(TOO_MUCH_DEVICES);
        return NULL;
    }
}

Device* addI2cRemoteDevice(DeviceInterface* deviceInterface, unsigned char i2cAddress) {
    return addDevice(deviceInterface, NULL, TRANSMIT_I2C, i2cAddress, NULL);
}

Device* addUartRemoteDevice(DeviceInterface* deviceInterface, unsigned char serialIndex) {
    return addDevice(deviceInterface, NULL, TRANSMIT_UART, serialIndex, NULL);
}

Device* addUartRemoteDeviceWithNotification(DeviceInterface* deviceInterface, unsigned char serialIndex, DeviceHandleNotificationFunction* notificationFunction) {
    Device* result = addDevice(deviceInterface, NULL, TRANSMIT_UART, serialIndex, NULL);
    result->deviceHandleNotification = notificationFunction;
    
    return result;
}

Device* addZigbeeRemoteDevice(DeviceInterface* interface, char* addressString) {
    int address = stringChecksum(addressString);
    return addDevice(interface, NULL, TRANSMIT_ZIGBEE, address, addressString);
}

Device* addLocalDevice(DeviceInterface* interface, DeviceDescriptor* descriptor) {
    return addDevice(interface, descriptor, TRANSMIT_LOCAL, 0, NULL);
}

Device* getDevice(int index) {
    if (deviceList.maxSize == 0) {
        writeError(DEVICES_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= deviceList.maxSize) {
        writeError(DEVICE_ILLEGAL_INDEX);
        return NULL;
    }
    Device* result = (Device*) deviceList.devices;
    // we don't need use sizeof because our pointer is a Device* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

int getDeviceCount() {
    return deviceList.size;
}

void initDevices() {
    OutputStream* logStream = getInfoOutputStreamLogger();
    appendStringCRLF(logStream, "Init Devices ...");
    int size = deviceList.size;
    int i;
    for (i = 0; i < size; i++) {
        Device* device = getDevice(i);
        initDevice(device);
    }
}

