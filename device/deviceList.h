#ifndef DEVICE_LIST_H
#define DEVICE_LIST_H

#include "device.h"
#include "deviceDescriptor.h"
#include "deviceInterface.h"

// Define the list of define used to include some part of code

// Activate or not the possibility of defining via the system device each Pin
// #define DEVICE_ENABLE_PIN
// Activate or not the possibility of controlling servo
// #define DEVICE_ENABLE_SERVO

/**
* Tre struct defining a list
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
 */
void initDeviceList(Device (*deviceListArray)[], unsigned char deviceListSize);

/**
* Get the list of devices.
* @return the list of devices
*/
DeviceList* getDeviceList();

/**
 * Add a local device : this device will respond to local calls.
 * @param deviceInterface the interface to describe the remote interface for device
 * @param deviceDescriptor the implementation of the device
 * @return a pointer on the Device
 */
Device* addLocalDevice(DeviceInterface* deviceInterface, DeviceDescriptor* deviceDescriptor);

/**
* Add a remote Device accessible via the i2c bus.
* @param deviceInterface the interface to describe the remote interface for device
* @param i2cAddress the address for the device
* @return a pointer on the Device
*/
Device* addI2CRemoteDevice(DeviceInterface* deviceInterface, int i2cAddress);

/**
 * Add a remote Device accessible via the zigbee bus.
 * @param interface the interface to describe the remote interface for device
 * @return a pointer on the Device
 */
Device* addZigbeeRemoteDevice(DeviceInterface* interface, char* addressString);

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
* Init the device descriptor list.
*/
void initDevices();

#endif

