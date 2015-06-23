#ifndef DEVICE_INTERFACE_H
#define DEVICE_INTERFACE_H

#include <stdbool.h>

/**
* Definition of the functions and types shared by devices
*/
typedef int DeviceInterfaceMode;

/**
* Define the constant for device (input of device).
*/
#define DEVICE_MODE_INPUT 0

/**
* Define the constant for device (output of device).
*/
#define DEVICE_MODE_OUTPUT 1

/**
 * Define the constant for device (output of device).
 */
#define DEVICE_MODE_NOTIFY 2

// DEVICE HEADER

/**
 * The index in the buffer to get the device Header.
 */
#define DEVICE_HEADER_INDEX                        0

// COMMAND HEADER

/**
 * The index in the buffer to get the command Header for a specified Device Header (command header char is just after device header).
 */
#define COMMAND_HEADER_INDEX                        1

/**
 * Define the length of the ack (char).
 */
#define ACK_LENGTH                                1

/**
* Define the length used by the header length
*/
#define DEVICE_HEADER_LENGTH                    1

/**
 * Define the length used by the header length, and the command header.
 */
#define DEVICE_AND_COMMAND_HEADER_LENGTH         2

/**
 * Define the length used by the dispatcher Prefix ('j' + index of the dispatcher in hex) => 3 chars
 */
#define DISPATCHER_COMMAND_AND_INDEX_HEADER_LENGTH 3

// NOTIFICATION

/**
 * The index in the buffer to get the notify (command equivalent) Header for a specified Device Header.
 */
#define NOTIFY_HEADER_INDEX                            1

/**
 * Define the length used by the header length, and the notify header.
 */
#define DEVICE_AND_NOTIFY_HEADER_LENGTH         2

/**
* Define an argument.
*/
typedef struct DeviceArgument {
    /** The type of argument (see below). */
    char type;
    /** The name of argument. */
    char* name;
} DeviceArgument;

#define MAX_ARGUMENTS     25
#define MAX_RETURNS     25

/**
* Define the result of deviceGetRawDataHeaderFunction if the
* header is not handled
*/
#define DEVICE_HEADER_NOT_HANDLED -1

/**
* Define the argument list and returns list for a device.
*/
typedef struct DeviceMethodMetaData {
    /** The name of the function. */
    char* functionName;
    /** An array of arguments */
    DeviceArgument arguments[MAX_ARGUMENTS];
    /** The size of argument Size. */
    char argumentsSize;
    /** An array of return arguments */
    DeviceArgument results[MAX_RETURNS];
    /** The size of returns Size. */
    char resultsSize;
} DeviceMethodMetaData;

// LENGTH = 1

/** separator ('-'). */
#define DEVICE_ARG_SEPARATOR    1

/** unsigned char * 1 => */
#define DEVICE_ARG_UNSIGNED_CHAR_1 2

// LENGTH = 2

/** unsigned char * 2 => */
#define DEVICE_ARG_UNSIGNED_CHAR_2 3 

/** unsigned int => hex2 */
#define DEVICE_ARG_UNSIGNED_HEX_2 4

/** signed int => hex4 */
#define DEVICE_ARG_SIGNED_HEX_2 5

// LENGTH = 3

/** unsigned char * 3 => */
#define DEVICE_ARG_UNSIGNED_HEX_3 6

// LENGTH = 4

/** unsigned int => hex4 */
#define DEVICE_ARG_UNSIGNED_HEX_4 7
/** signed int => hex4 */
#define DEVICE_ARG_SIGNED_HEX_4 8

// LENGTH = 5

/** unsigned int => hex5 */
#define DEVICE_ARG_UNSIGNED_HEX_5 9
/** signed int => hex4 */
#define DEVICE_ARG_SIGNED_HEX_5 10

// LENGTH = 6

/** unsigned int => hex6 */
#define DEVICE_ARG_UNSIGNED_HEX_6     11
/** signed int => hex6 */
#define DEVICE_ARG_SIGNED_HEX_6     12

// LENGTH = 8
/** unsigned long => hex8 */
#define DEVICE_ARG_UNSIGNED_HEX_8 13
/** signed long => hex8 */
#define DEVICE_ARG_SIGNED_HEX_8 14

/** Array of 4 chars. */
#define DEVICE_ARG_FIXED_CHAR_ARRAY   15

// LENGTH = 9 

/** (used only for string aggregates values) */
#define DEVICE_ARG_UNSIGNED_HEX_9     18

// LENGTH = 10 

/** (used only for string aggregates values) */
#define DEVICE_ARG_UNSIGNED_HEX_10     20

// LENGTH = 12 

/** (used only for string aggregates values) */
#define DEVICE_ARG_UNSIGNED_HEX_12     24

// ARGUMENT LIST

/**
* Singleton of DeviceInterfaceMetaData.
* @return the singleton of DeviceInterfaceMetaData
*/
DeviceMethodMetaData* getDeviceMethodMetaData();

/**
 * Returns the length of the type when we mashall it as string.
 * Ex : unsigned int (16 bits) will be converted as hexadecimal value, so it will use 4 chars as hexadecimal.
 * @param parameterType parameter Type (see all constants DEVICE_ARGS ...)
 * @return the length of the type when we mashall it as string.
 */
int getLengthOfType(int parameterType);

/**
* Set the function Name and the size of all argument list for that function.
* @param functionName the name of the function (as remote method name)
* @param argumentsSize the number of arguments (NOT the length of the marshalled string !)
* @param resultsSize the number of results (NOT the length of the marshalled string !)
*/
void setFunction(char* functionName, int argumentsSize, int resultsSize);

/**
 * Set the notification name and the size of all arguments.
 * Internally, use the same structure than the Function.
 */
void setNotification(char* notificationName, int notificationArguments);

/**
* Set the function Name and the size of all argument to 0.
* @param functionName the name of the function (as remote method name)
*/
void setFunctionNoArgumentAndNoResult(char* functionName);

/**
 * Returns depending on the input mode, the input length or the outputLength.
 * It avoids to returns a structure, because we cares often only about input or ouput result.
 */
int commandLengthValueForMode(DeviceInterfaceMode mode, int inputResult, int outputResult);

// ARGUMENTS MANAGEMENT

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
* Set the argument of the deviceArgumentList with index for name
*/
void setArgumentSignedHex4(int index, char* name);

/**
* Set the argument of the deviceArgumentList with index for name
*/
void setArgumentUnsignedHex6(int index, char* name);

/**
 * Set the argument of the deviceArgumentList with index for name.
 */
void setArgumentFixedCharArray(int index, char* name);

/**
* Set argument with index to a separator ("-")
*/
void setArgumentSeparator(int index);

// RESULTS MANAGEMENT

/**
* Set the result of the deviceMethodMetaData with index for type/name
*/
void setResult(int index, int type, char* name);

/**
* Set the argument of the deviceMethodMetaData with index for name
*/
void setResultUnsignedChar1(int index, char* name);

/**
* Set the result of the deviceMethodMetaData with index for name
*/
void setResultUnsignedHex2(int index, char* name);

/**
* Set the result of the deviceMethodMetaData with index for name
*/
void setResultSignedHex2(int index, char* name);

/**
* Set the result of the deviceMethodMetaData with index for name
*/
void setResultUnsignedHex4(int index, char* name);

/**
* Set the result of the deviceMethodMetaData with index for name
*/
void setResultUnsignedHex6(int index, char* name);

/**
*  Set the result of the deviceMethodMetaData with index for name
*/
void setResultFixedCharArray(int index, char* name);

/**
* Set result with index to a separator ("-")
*/
void setResultSeparator(int index);

/**
* Defines the function to know the name of the device.
*/
typedef const char* deviceGetNameFunction(void);

/**
* @param commandHeader the character which is the header of the command
* @param mode either MODE_INPUT to know the length of the inputBuffer to handle the command of the header, either MODE_OUTPUT to know the length of the outputBuffer to get results
* @param fillDeviceArgumentList if true, the function will update the argumentList
* Returns a value >= 0 if the device handle this char, and -1, if it's not handled
*/
typedef int deviceGetInterfaceFunction(char commandHeader,
                                        DeviceInterfaceMode mode,
                                        bool fillDeviceArgumentList);



/**
* Defines the structure used to describe the remote commands accepted by the device.
*/
typedef struct DeviceInterface{
    /**
     * The header of the Device. Each device must have its own name.
     * @see https://github.com/svanacker/cen-electronic/wiki/Device-Header-List
     */
    char deviceHeader;
    /** Function returning the name of the device. */
    deviceGetNameFunction *deviceGetName;
    /** Function returning information about interface. */
    deviceGetInterfaceFunction* deviceGetInterface;
} DeviceInterface;

#endif
