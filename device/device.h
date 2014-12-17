#ifndef DEVICE_H
#define DEVICE_H

#include "deviceInterface.h"
#include "deviceDescriptor.h"

#include "../common/commons.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"

// forward declaration
struct Device;
typedef struct Device Device;

/**
* The function used to handle the data which are transmit aynchronously to the master.
* We don't have any OutputStream, because we don't want to have a ping-pong communication between client 
* and master without control. So it is mainly intended to update state, or forward to other card (for example PC)

* @param device the device from which data comes
* @param command header the command header which is called
* @param inputStream the inputStream to get data from the client
*/
typedef void deviceHandleCallbackRawDataFunction(const Device* device, 
                                                 char commandHeader,
                                                  InputStream* inputStream);

/**
* Helper method to forward data to an outputStream (Ex : PC).
* @param inputStream the inputStream containing data from Slave
* @param outputStream the outputStream in which we forward (Ex : PC, debug ...)
* @param device the device which causes the callback
* @param commandHeader the header of the message
* @param mode ??? (TODO Documentation)
*/
void forwardCallbackRawDataTo(InputStream* inputStream,
                              OutputStream* outputStream,
                              const Device* device,
                              const char commandHeader,
                              int mode);

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
    int transmitMode;
    /** The address as char (useful for zigbee for example). */
    char* addressString;
    /** The address (only for remote transmitMode). In case of addressString, address contains a checksum of addressString. */
    int address;
    /** The real implementation of the device. */
    DeviceDescriptor* descriptor;
    /** The device callback function when Slave want to transmit something asynchronously to the master. */
    deviceHandleCallbackRawDataFunction *deviceHandleCallbackRawData;
};


/**
* Init the device with the information given by deviceDescriptor.
* We consider that there is a LCD03 on the I2C bus and a serial bus
* connected to send debug information.
* @param device the descriptor for the device.
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

