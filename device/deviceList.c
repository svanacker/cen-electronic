#include <stdlib.h>

#include "deviceList.h"
#include "device.h"
#include "deviceDescriptor.h"
#include "deviceInterface.h"

#include "../common/commons.h"

#include "../common/error/error.h"

#include "../common/io/stream.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../common/math/cenMath.h"

// Singleton
static DeviceList deviceList;

DeviceList* getDeviceList() {
    return &deviceList;
}

/**
 * @private
 */
void addDevice(Device* device, DeviceInterface* interface,
        DeviceDescriptor* descriptor,
        int transmitMode,
        int address,
		char* addressString) {
    unsigned char size = deviceList.size;
    if (size < MAX_DEVICE) {
        deviceList.devices[size] = device;
        // get a device already allocated
        device->interface = interface;
        device->descriptor = descriptor;
        device->transmitMode = transmitMode;
        device->address = address;
		device->addressString = addressString;
        deviceList.size++;
    } else {
        writeError(TOO_MUCH_DEVICES);
    }
}

int getDeviceResponseSize(int commandHeader) {
    int i;
    for (i = 0; i < deviceList.size; i++) {
        Device* device = getDevice(i);
        DeviceInterface* deviceInterface = device->interface;
        int valueCount = deviceInterface->deviceGetInterface(commandHeader, DEVICE_MODE_OUTPUT, NULL);
        if (valueCount != DEVICE_HEADER_NOT_HANDLED) {
            return valueCount;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

void addI2CRemoteDevice(Device* device, DeviceInterface* interface, int i2cAddress) {
    addDevice(device, interface, NULL, TRANSMIT_I2C, i2cAddress, NULL);
}

void addZigbeeRemoteDevice(Device* device, DeviceInterface* interface, char* addressString) {
	int address = stringChecksum(addressString);
    addDevice(device, interface, NULL, TRANSMIT_ZIGBEE, address, addressString);
}

void addLocalDevice(Device* device, DeviceInterface* interface, DeviceDescriptor* descriptor) {
    addDevice(device, interface, descriptor, TRANSMIT_LOCAL, 0, NULL);
}

Device* getDevice(int index) {
    return deviceList.devices[index];
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

