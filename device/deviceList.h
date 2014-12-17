#ifndef DEVICE_LIST_H
#define DEVICE_LIST_H

#include "device.h"
#include "deviceDescriptor.h"
#include "deviceInterface.h"

/**
* The struct defining a list of devices.
*/
typedef struct DeviceList {
    /** An array of pointer on device. */
    Device (*devices)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;
} DeviceList;

/**
 * Initializes the Devices List with an array and the size of the array to avoid big and uniform
 * array length.
 * @param deviceListArray the array of pointer device to add.
 * @param deviceListSize the size of the array of pointer to add.
 */
void initDeviceList(Device (*deviceListArray)[], unsigned char deviceListSize);

/**
* Get the list of devices.
* @return the list of devices.
*/
DeviceList* getDeviceList();

/**
 * Add a local device : this device will respond to local calls.
 * @param deviceInterface the interface to describe the remote interface for device
 * @param deviceDescriptor the implementation of the device
 * @return a pointer on the Device accessible locally
 */
Device* addLocalDevice(DeviceInterface* deviceInterface, DeviceDescriptor* deviceDescriptor);

/**
* Add a remote Device accessible via the i2c bus.
* @param deviceInterface the interface to describe the remote interface for device
* @param i2cAddress the address for the device
* @return a pointer on the Device accessible by I2C
*/
Device* addI2CRemoteDevice(DeviceInterface* deviceInterface, int i2cAddress);

/**
 * @deprecated we don't use zigbee anymore
 * Add a remote Device accessible via the zigbee bus.
 * @param interface1 the interface to describe the remote interface for device
 * @return a pointer on the Device
 */
Device* addZigbeeRemoteDevice(DeviceInterface* interface1, char* addressString);

/**
* Get the device of index;
* @param index the index of the device
* @return a pointer on the Device
*/
Device* getDevice(int index);

/**
* Get the count of device.
* @result the count of device
*/
int getDeviceCount();

/**
* Init the device descriptor list by initializing each devices.
*/
void initDevices();

#endif

