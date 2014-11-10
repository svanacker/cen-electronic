#ifndef DEVICE_DESCRIPTOR_H
#define DEVICE_DESCRIPTOR_H

#include "deviceDescriptor.h"

#include "../common/commons.h"
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
* @param header the header char
* @param inputStream the input Stream where we can get commandHeader, and input parameters
* @param outputStream the output Stream where we can write some results, ack (with commandHeader)
*/
typedef void deviceHandleRawDataFunction(char header,
                                         InputStream* inputStream,
                                         OutputStream* outputStream);

/**
* Defines the structure used to describe a device descriptor.
*/
typedef struct DeviceDescriptor {
    /** A callback on the Function which must be used to initialized the device. */
    deviceInitFunction *deviceInit;
	/** A callback on the Function which must be used to shutdown the device. */
    deviceShutDownFunction *deviceShutDown;
	/** A callback on the Function which must be used to know if the device is ok (when it's used), can be called at every time, but at least after starting the device. */
    deviceIsOkFunction *deviceIsOk;
	/** A callback on the Function to handle the string data which are given (Ex : Mw2010 to Move the both motors). */
    deviceHandleRawDataFunction *deviceHandleRawData;
} DeviceDescriptor;


#endif
