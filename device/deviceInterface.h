#ifndef DEVICE_INTERFACE_H
#define DEVICE_INTERFACE_H

#include "../common/commons.h"

/**
* Definition of the functions and types shared by devices
*/

/**
* Define the constant for device (input of device).
*/
#define DEVICE_MODE_INPUT 0

/**
* Define the constant for device (output of device).
*/
#define DEVICE_MODE_OUTPUT 1

/**
* Define an argument.
*/
typedef struct DeviceArgument {
	/** The type of argument (see below). */
	char type;
	/** The name of argument. */
	char* name;
} DeviceArgument;

#define MAX_ARGUMENTS 11

/**
* Define the result of deviceGetRawDataHeaderFunction if the
* header is not handled
*/
#define DEVICE_HEADER_NOT_HANDLED -1

/**
* Define the argument list for a device.
*/
typedef struct DeviceArgumentList {
	/** An array of arguments */
	DeviceArgument args[MAX_ARGUMENTS];
	/** The name of the function. */
	char* functionName;
	/** The size of list. */
	char size;
} DeviceArgumentList;


// LENGTH = 1

/** separator ('-'). */
#define DEVICE_ARG_SEPARATOR	2

/** unsigned char * 1 => */
#define DEVICE_ARG_UNSIGNED_CHAR_1 2

// LENGTH = 2

/** unsigned char * 2 => */
#define DEVICE_ARG_UNSIGNED_CHAR_2 4 

/** unsigned int => hex2 */
#define DEVICE_ARG_UNSIGNED_HEX_2 4

/** signed int => hex4 */
#define DEVICE_ARG_SIGNED_HEX_2 5

// LENGTH = 3

/** unsigned char * 3 => */
#define DEVICE_ARG_UNSIGNED_HEX_3 6

// LENGTH = 4

/** unsigned int => hex4 */
#define DEVICE_ARG_UNSIGNED_HEX_4 8
/** signed int => hex4 */
#define DEVICE_ARG_SIGNED_HEX_4 9

// LENGTH = 5

/** unsigned int => hex5 */
#define DEVICE_ARG_UNSIGNED_HEX_5 10
/** signed int => hex4 */
#define DEVICE_ARG_SIGNED_HEX_5 11

// LENGTH = 6

/** unsigned int => hex6 */
#define DEVICE_ARG_UNSIGNED_HEX_6 	12
/** signed int => hex6 */
#define DEVICE_ARG_SIGNED_HEX_6 	13

// LENGTH = 8
/** unsigned long => hex8 */
#define DEVICE_ARG_UNSIGNED_HEX_8 16
/** signed long => hex8 */
#define DEVICE_ARG_SIGNED_HEX_8 17

// LENGTH = 9 

/** (used only for string aggregates values) */
#define DEVICE_ARG_UNSIGNED_HEX_9 	18

// LENGTH = 10 

/** (used only for string aggregates values) */
#define DEVICE_ARG_UNSIGNED_HEX_10 	20

// LENGTH = 12 

/** (used only for string aggregates values) */
#define DEVICE_ARG_UNSIGNED_HEX_12 	24

// ARGUMENT LIST

/**
* Singleton of DeviceArgumentList
*/
DeviceArgumentList* getDeviceArgumentList();

/**
* Set the function Name and the size of all argument list for that function.
*/
void setFunction(char* functionName, int size);

/**
* Set the function Name and the size of all argument to 0.
*/
void setFunctionNoArgument(char* functionName);

/**
* Set the argument of the deviceArgumentList with index for type/name
*/
void setArgument(int index, int type, char* name);

/**
* Set the argument of the deviceArgumentList with index for name
*/
void setArgumentUnsignedChar1(int index, char* name);

/**
* Set the argument of the deviceArgumentList with index for name
*/
void setArgumentUnsignedHex2(int index, char* name);

/**
* Set the argument of the deviceArgumentList with index for name
*/
void setArgumentSignedHex2(int index, char* name);

/**
* Set the argument of the deviceArgumentList with index for name
*/
void setArgumentUnsignedHex4(int index, char* name);

/**
* Set argument with index to a separator ("-")
*/
void setArgumentSeparator(int index);

/**
* Defines the function to know the name of the device.
*/
typedef const char* deviceGetNameFunction(void);

/**
* Defines the function to know the software revision of a device.
*/
typedef unsigned int deviceGetSoftwareRevisionFunction(void);

/**
* @param header the character which is the header
* @param mode either MODE_INPUT to know the length of the inputBuffer to handle the command of the header
* @param fillDeviceArgumentList if TRUE, the function will update the argumentList
* Returns a value >= 0 if the device handle this char, and -1, if it's not handled
*/
typedef int deviceGetInterfaceFunction(char header,
								int mode,
								BOOL fillDeviceArgumentList);



/**
* Defines the structure used to describe the remote commands accepted by the device.
*/
typedef struct DeviceInterface{
	/** Function returning the name of the device. */
	deviceGetNameFunction *deviceGetName;
	/** Function returning the software revision of the device. */
	// deviceGetSoftwareRevisionFunction *deviceGetSoftwareRevision;
	/** Function returning information about interface. */
	deviceGetInterfaceFunction* deviceGetInterface;
} DeviceInterface;

#endif
