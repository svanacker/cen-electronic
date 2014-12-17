#include <stdlib.h>

#include "deviceList.h"
#include "device.h"
#include "deviceDescriptor.h"
#include "deviceInterface.h"

#include "../common/commons.h"

#include "../common/error/error.h"

#include "../common/io/stream.h"
#include "../common/io/outputStream.h"

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
    deviceList.maxSize = deviceListSize;
}

/**
 * @private
 */
Device* addDevice(DeviceInterface* interface,
        DeviceDescriptor* descriptor,
        int transmitMode,
        int address,
        char* addressString) {
    if (&deviceList == NULL || deviceList.maxSize == 0) {
        writeError(DEVICES_LIST_NOT_INITIALIZED);
        return NULL;
    }

    unsigned char size = deviceList.size;
    if (size < deviceList.maxSize) {
        Device* device = getDevice(size);
        // get a pointer on a device already allocated (because we provide at init a pointer on an array of device
        device->deviceInterface = interface;
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

Device* addI2CRemoteDevice(DeviceInterface* interface, int i2cAddress) {
    return addDevice(interface, NULL, TRANSMIT_I2C, i2cAddress, NULL);
}

Device* addZigbeeRemoteDevice(DeviceInterface* interface, char* addressString) {
    int address = stringChecksum(addressString);
    return addDevice(interface, NULL, TRANSMIT_ZIGBEE, address, addressString);
}

Device* addLocalDevice(DeviceInterface* interface, DeviceDescriptor* descriptor) {
    return addDevice(interface, descriptor, TRANSMIT_LOCAL, 0, NULL);
}

Device* getDevice(int index) {
    // TODO : Check size
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
    int size = deviceList.size;
    int i;
    for (i = 0; i < size; i++) {
        Device* device = getDevice(i);
        initDevice(device);
    }
}

