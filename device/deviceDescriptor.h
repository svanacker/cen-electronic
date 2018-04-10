#ifndef DEVICE_DESCRIPTOR_H
#define DEVICE_DESCRIPTOR_H

#include <stdbool.h>

#include "deviceDescriptor.h"

#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"

/**
* Defines the type for the function which init the component.
*/
typedef void deviceInitFunction(void);

/**
* Defines the type for the function which stop the component.
*/
typedef void deviceShutDownFunction(void);

/**
* Defines the function to know if a device is ok or not.
* @return true if the device is ok, false else
*/
typedef bool deviceIsOkFunction(void);

/**
* Function for handling raw data sent to the device.
* @param commandHeader the header char
* @param inputStream the input Stream where we can get commandHeader, and input parameters
* @param outputStream the output Stream where we can write some results, ack (with commandHeader)
* @param notificationOutputStream the output Stream in which we will write, but probably later by a callback
*/
typedef void deviceHandleRawDataFunction(char commandHeader,
                                         InputStream* inputStream,
                                         OutputStream* outputStream,
                                         OutputStream* notificationOutputStream);

/**
* Defines the structure used to describe a device descriptor.
*/
typedef struct DeviceDescriptor {
    /**
     * Gets the error Code during initialization, 0 if the device has no error.
     */
    unsigned int initErrorCode;
    /** A callback on the Function which must be used to initialized the device. */
    deviceInitFunction *deviceInit;
    /** A callback on the Function which must be used to shutdown the device. */
    deviceShutDownFunction *deviceShutDown;
    /** A callback on the Function which must be used to know if the device is ok (when it's used), can be called at every time, but at least after starting the device. */
    deviceIsOkFunction *deviceIsOk;
    /** A callback on the Function to handle the string data which are given (Ex : Mw2010 to Move the both motors). */
    deviceHandleRawDataFunction *deviceHandleRawData;
    /** A generic pointer to store parameter single object pointer or structure to manipulate some external objects. */
    int* object;
} DeviceDescriptor;

/**
 * Initializes a device descriptor with all data needed.
 */
void initDeviceDescriptor(DeviceDescriptor* deviceDescriptor, 
                        deviceInitFunction *deviceInit,
                        deviceShutDownFunction *deviceShutDown,
                        deviceIsOkFunction *deviceIsOk,
                        deviceHandleRawDataFunction *deviceHandleRawData,
                        int* object);

/**
 * Returns true if the device descriptor was initialized properly
 * @param deviceInterface
 * @return 
 */
bool isDeviceDescriptorInitializedProperly(DeviceDescriptor* deviceDescriptor);


#endif
