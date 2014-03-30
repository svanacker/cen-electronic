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
*/
typedef bool deviceIsOkFunction(void);

/**
* Function for handling raw data sent to the device.
* @param header the header char
* @param data the data to be handled
*/
typedef void deviceHandleRawDataFunction(char header,
										 InputStream* inputStream,
										 OutputStream* outputStream);

/**
* Defines the structure used to describe a device.
*/
typedef struct DeviceDescriptor {
	deviceInitFunction *deviceInit;
	deviceShutDownFunction *deviceShutDown;
	deviceIsOkFunction *deviceIsOk;
	deviceHandleRawDataFunction *deviceHandleRawData;
} DeviceDescriptor;


#endif
