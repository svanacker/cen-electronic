#ifndef FILE_DEVICE_INTERFACE_H
#define FILE_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of FILE COMMAND HEADER

/**
* Defines the header to show the list of file
*/
#define COMMAND_SHOW_LIST_FILE         'l'

/**
* Writes the content of a file.
*/
#define COMMAND_SHOW_CONTENT_FILE       'r'

/**
* Creates a new empty file
*/
#define COMMAND_CREATE_NEW_FILE        'n'

/**
* Deletes a file
*/
#define COMMAND_DELETE_FILE             'd'

/**
* Interface for Device.
*/
DeviceInterface* getFileDeviceInterface();

#endif