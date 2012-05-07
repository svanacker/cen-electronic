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
// Activate or not the possibility of changing log Level
// #define DEVICE_ENABLE_CHANGE_LEVEL

/** The max limit of device list. */
#define MAX_DEVICE 17

/**
* Tre struct defining a list
*/
typedef struct DeviceList {
	/** An array of pointer on device. */
	Device* devices[MAX_DEVICE];
	/** the size of the list. */
	unsigned char size;
} DeviceList;

/**
* Get the list of devices.
*/
DeviceList* getDeviceList();

/**
 * Add a local device : this device will respond to local calls.
 * @param interface the interface to describe the remote interface for device
 * @param device the implementation of the device
 */
void addLocalDevice(Device* device, DeviceInterface* interface,
					  DeviceDescriptor* deviceDescriptor);

/**
* Add a remote Device accessible via the i2c bus.
* @param interface the interface to describe the remote interface for device
* @param i2cAddress the address for the device
*/
void addI2CRemoteDevice(Device* device, DeviceInterface* interface, int i2cAddress);

/**
 * Add a remote Device accessible via the zigbee bus.
 * @param interface the interface to describe the remote interface for device
 */
void addZigbeeRemoteDevice(Device* device, DeviceInterface* interface, char* addressString);

/**
* Get the device of index + 1;
*/
Device* getDevice(int index);

/**
* Get the count of device.
*/
int getDeviceCount();

/**
* Init the device descriptor list.
*/
void initDevices();

/**
* Get the size which must be sent by the device (local or distant)
* with the given commandHeader
* @param commandHeader the header of the command
*/
int getDeviceResponseSize(int commandHeader);

#endif

