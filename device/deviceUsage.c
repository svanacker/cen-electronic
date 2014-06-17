#include "deviceUsage.h"

#include "device.h"
#include "deviceInterface.h"
#include "deviceList.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

// Main

#define ARGUMENTS_SEPARATOR 				", "

#define DEVICE_INPUT_MODE_SEPARATOR_NAME 	':'

#define DEVICE_NAME_AND_HEADER_SEPARATOR 	':'

#define DEVICE_HEADER_AND_TYPE_SEPARATOR	':'

// Arguments

#define ARGUMENTS_START_CHAR  				'('

#define ARGUMENTS_NAME_AND_TYPE_SEPARATOR	' '

#define ARGUMENTS_STOP_CHAR 		 		')'

#define ARGUMENTS_AND_RESULTS_SEPARATOR		" => "

/**
 * 
 */
void printArgument(OutputStream* outputStream, DeviceMethodMetaData* deviceMethodMetaData, int argumentIndex) {
	if (argumentIndex > 0) {
		appendString(outputStream, ARGUMENTS_SEPARATOR);
	}
	
	DeviceArgument deviceArgument = deviceMethodMetaData->arguments[argumentIndex];
	char* argumentName = deviceArgument.name;
	
	// type and length
	char type = deviceArgument.type;
	// last bit used for signed / unsigned
	if ((type & 1) != 0) {
		append(outputStream, 's');
	} else {
		append(outputStream, 'u');
	}
	char argumentLength = (type >> 1) & 0xFE;
	appendDec(outputStream, argumentLength);
	
	// Argument name
	append(outputStream, ARGUMENTS_NAME_AND_TYPE_SEPARATOR);
	appendString(outputStream, argumentName);
}

/**
 * @private
 */
bool printMethodMetaData(OutputStream* outputStream, DeviceInterface* deviceInterface, char commandHeader, char headerLength, char inputMode) {
	if (headerLength != DEVICE_HEADER_NOT_HANDLED) {
		DeviceMethodMetaData* deviceMethodMetaData = getDeviceMethodMetaData();
		char deviceHeader = deviceInterface->deviceHeader;

		// Input/Output Mode
        append(outputStream, inputMode);
		append(outputStream, DEVICE_INPUT_MODE_SEPARATOR_NAME);

		// DeviceName
        const char* deviceName = deviceInterface->deviceGetName();
        appendString(outputStream, deviceName);
        append(outputStream, DEVICE_NAME_AND_HEADER_SEPARATOR);

		// Header
		append(outputStream, deviceHeader);
        append(outputStream, commandHeader);
        append(outputStream, DEVICE_HEADER_AND_TYPE_SEPARATOR);

		// functionName
        appendString(outputStream, deviceMethodMetaData->functionName);
        append(outputStream,  ARGUMENTS_START_CHAR);

		// arguments
        int argumentCount = deviceMethodMetaData->argumentsSize;
        int argumentIndex;
        for (argumentIndex = 0; argumentIndex < argumentCount; argumentIndex++) {
			printArgument(outputStream, deviceMethodMetaData, argumentIndex);
        }
        append(outputStream,  ARGUMENTS_STOP_CHAR);

		appendString(outputStream, ARGUMENTS_AND_RESULTS_SEPARATOR);

		// results
        append(outputStream,  ARGUMENTS_START_CHAR);
        int resultCount = deviceMethodMetaData->resultsSize;
        int resultIndex;
        for (resultIndex = 0; resultIndex < resultCount; resultIndex++) {
			printArgument(outputStream, deviceMethodMetaData, resultIndex);
        }
		if (resultCount == 0) {
			appendString(outputStream, "void");
		}
        append(outputStream,  ARGUMENTS_STOP_CHAR);

        println(outputStream);

		return true;
    }
	return false;
}

/**
 * @private
 */
void printDeviceUsageLine(OutputStream* outputStream, char header, Device* device) {
    DeviceInterface* deviceInterface = device->interface;

    // input Argument
    int headerLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_INPUT, true);
    printMethodMetaData(outputStream, deviceInterface, header, headerLength, 'i');
}

void printDeviceUsage(OutputStream* outputStream, Device* device) {
    char header;
    // We start after special caracters and use only ANSI chars
    for (header = 32; header < 127; header++) {
        printDeviceUsageLine(outputStream, header, device);
    }
}

void printDeviceListUsage(OutputStream* outputStream) {
    println(outputStream);
    int deviceCount = getDeviceCount();
    int deviceIndex;
    for (deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++) {
        Device* device = getDevice(deviceIndex);
        printDeviceUsage(outputStream, device);
    }
}
