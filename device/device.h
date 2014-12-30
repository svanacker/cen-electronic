#ifndef DEVICE_H
#define DEVICE_H

#include "transmitMode.h"
#include "deviceInterface.h"
#include "deviceDescriptor.h"

#include "../common/commons.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"

// forward declaration
struct Device;
typedef struct Device Device;

/**
* The function used to handle the data which are transmit asynchronously to the master.
* We don't have any OutputStream, because we don't want to have a ping-pong communication between client 
* and master without control. So it is mainly intended to update state, or forward to other card (for example PC)

* @param device the device from which data comes
* @param commandHeader header the command header which is called
* @param inputStream the inputStream to get data from the client
*/
typedef void deviceHandleNotificationFunction(const Device* device, 
                                                 const char commandHeader,
                                                  InputStream* inputStream);

/**
 * Send a ack, and add the deviceHeader, and the commandHeader.
 * @param deviceOutputStream outputStream for the deviceResponse
 * @param deviceHeader the char header for the Device (Ex : 'S' for System Device)
 * @param commandHeader the char header for the command specific to a Device (Ex : 'P' for Ping Command)
 */
void ackCommand(OutputStream* deviceOutputStream, const char deviceHeader, const char commandHeader);

/**
* Defines the structure used to describe a device.
*/
struct Device {
    /** The interface of the device for a remote caller (without implementation). */
    DeviceInterface* deviceInterface;
    /** Which bus the device use. */
    TransmitMode transmitMode;
    /** The address as char (useful for zigbee for example). */
    char* addressString;
    /** The address (only for remote transmitMode). In case of addressString, address contains a checksum of addressString. */
    int address;
    /** The real implementation of the device. */
    DeviceDescriptor* descriptor;
    /** The device callback function when Slave want to transmit something asynchronously to the master. */
    deviceHandleNotificationFunction* deviceHandleNotification;
};


/**
* Init the device with the information given by deviceDescriptor.
* We consider that there is a LCD03 on the I2C bus and a serial bus
* connected to send debug information.
* @param device the descriptor for the device.
* @return true if the device was successfully initialized, false else
*/
bool initDevice(const Device *device);

/**
* Stop the device with the information given by deviceDescriptor.
* We consider that there is a LCD03 on the I2C bus and a serial bus
* connected to send debug information.
* @param device the descriptor for the device.
*/
void stopDevice(const Device *device);

#endif

