#include <stdlib.h>
#include <stdbool.h>

#include "deviceUsage.h"

#include "device.h"
#include "deviceInterface.h"
#include "deviceList.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/nullOutputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

// Length of different columns

#define DEVICE_USAGE_HEADER_COLUMN_LENGTH     3
#define DEVICE_USAGE_NAME_COLUMN_LENGTH       28
#define DEVICE_USAGE_IO_COLUMN_LENGTH		  4
#define DEVICE_USAGE_IO_SIZE_COLUMN_LENGTH    3
#define DEVICE_USAGE_PARAM_NAME_COLUMN_LENGTH  16
#define DEVICE_USAGE_PARAM_SIZE_COLUMN_LENGTH  3
#define DEVICE_USAGE_PARAM_TYPE_COLUMN_LENGTH  7

char* getTypeAsString(OutputStream* outputStream, int parameterType) {
    switch (parameterType) {
        case DEVICE_ARG_SEPARATOR : return "-";
        case DEVICE_ARG_UNSIGNED_CHAR_1 : return "u1";
        case DEVICE_ARG_UNSIGNED_CHAR_2 : return "u_2";
        case DEVICE_ARG_UNSIGNED_HEX_2 : return "hex_u_2";
        case DEVICE_ARG_SIGNED_HEX_2 : return "hex_s_2";
        case DEVICE_ARG_UNSIGNED_HEX_3 : return "hex_u_3";
        case DEVICE_ARG_UNSIGNED_HEX_4 : return "hex_u_4";
        case DEVICE_ARG_SIGNED_HEX_4 : return "hex_s_4";
        case DEVICE_ARG_UNSIGNED_HEX_5 : return "hex_u_5";
        case DEVICE_ARG_SIGNED_HEX_5 : return "hex_s_5";
        case DEVICE_ARG_UNSIGNED_HEX_6 : return "hex_u_6";
        case DEVICE_ARG_FIXED_CHAR_ARRAY: return "charArray4_length_8";
        case DEVICE_ARG_SIGNED_HEX_6 : return "hex_s_6";
        case DEVICE_ARG_UNSIGNED_HEX_8 : return "hex_u_8";
        case DEVICE_ARG_SIGNED_HEX_8 : return "hex_s_8";
        case DEVICE_ARG_UNSIGNED_HEX_9 : return "hex_u_9";
        case DEVICE_ARG_UNSIGNED_HEX_10 : return "hex_u_10";
        case DEVICE_ARG_UNSIGNED_HEX_12 : return "hex_u_12";
    }
	// TODO
    writeError(DEVICE_INTERFACE_PROBLEM);
	return "??????";
}

/**
 * @private.
 * Print Argument Or Result
 * @return the size of the argument
 */
unsigned int printArgument(OutputStream* outputStream, DeviceArgument* deviceArgument, int argumentIndex) {
	appendStringTableData(outputStream, "", DEVICE_USAGE_HEADER_COLUMN_LENGTH);
	appendStringTableData(outputStream, "", DEVICE_USAGE_NAME_COLUMN_LENGTH);
	appendStringTableData(outputStream, "", DEVICE_USAGE_IO_COLUMN_LENGTH);
	appendStringTableData(outputStream, "", DEVICE_USAGE_IO_SIZE_COLUMN_LENGTH);

    char* argumentName = deviceArgument->name;
	appendStringTableData(outputStream, argumentName, DEVICE_USAGE_PARAM_NAME_COLUMN_LENGTH);

    char type = deviceArgument->type;

	unsigned int result = getLengthOfType(type);
	appendDecTableData(outputStream, result, DEVICE_USAGE_PARAM_SIZE_COLUMN_LENGTH);
	if (result == -1) {
		writeError(DEVICE_INTERFACE_PROBLEM);
	}

	const char* typeAsString = getTypeAsString(outputStream, type);
	appendStringTableData(outputStream, typeAsString, DEVICE_USAGE_PARAM_TYPE_COLUMN_LENGTH);
	appendTableSeparator(outputStream);
	println(outputStream);
   
    return result;
}

/**
 * @private
 * @return true if it's ok, false if there is an error
 */
bool printMethodOrNotificationMetaData(OutputStream* outputStream, DeviceInterface* deviceInterface, char commandHeader, char argumentLength, char resultLength, bool notification) {
    bool result = true;
    if (argumentLength != DEVICE_HEADER_NOT_HANDLED) {
        DeviceMethodMetaData* deviceMethodMetaData = getDeviceMethodMetaData();

        // Function Header
		appendCharTableData(outputStream, commandHeader, DEVICE_USAGE_HEADER_COLUMN_LENGTH);

        // functionName
		const char* functionName = deviceMethodMetaData->functionName;
		appendStringTableData(outputStream, functionName, DEVICE_USAGE_NAME_COLUMN_LENGTH);

        // arguments
		appendStringTableData(outputStream, "IN", DEVICE_USAGE_IO_COLUMN_LENGTH);
		int argumentCount = deviceMethodMetaData->argumentsSize;
		int argumentIndex;
		int realArgumentLength = 0;
		for (argumentIndex = 0; argumentIndex < argumentCount; argumentIndex++) {
			DeviceArgument deviceArgument = deviceMethodMetaData->arguments[argumentIndex];
			realArgumentLength += getLengthOfType(deviceArgument.type);
		}
		appendDecTableData(outputStream, realArgumentLength, DEVICE_USAGE_IO_SIZE_COLUMN_LENGTH);

		// param name empty
		appendStringTableData(outputStream, "", DEVICE_USAGE_PARAM_NAME_COLUMN_LENGTH);
		appendStringTableData(outputStream, "", DEVICE_USAGE_PARAM_SIZE_COLUMN_LENGTH);
		appendStringTableData(outputStream, "", DEVICE_USAGE_PARAM_TYPE_COLUMN_LENGTH);
		appendTableSeparator(outputStream);
		println(outputStream);

		for (argumentIndex = 0; argumentIndex < argumentCount; argumentIndex++) {
			DeviceArgument deviceArgument = deviceMethodMetaData->arguments[argumentIndex];
			printArgument(outputStream, &deviceArgument, argumentIndex);
		}
		/*
		// TODO : Error must be check at the beginning of the function and not Inside
        if (argumentLength != realArgumentLength) {
            writeError(DEVICE_INTERFACE_PROBLEM);
            result = false;
            appendString(outputStream, "Arguments Definition ERROR !!!!!!\n");
            appendCRLF(outputStream);
            appendStringAndDec(outputStream, "argumentCount=", argumentCount);
            appendCRLF(outputStream);
            appendStringAndDec(outputStream, "argumentLength=", argumentLength);
            appendCRLF(outputStream);
            appendStringAndDec(outputStream, "realArgumentLength=", realArgumentLength);
            appendCRLF(outputStream);
        }
		*/
        // results
        if (!notification) {

			appendStringTableData(outputStream, "", DEVICE_USAGE_HEADER_COLUMN_LENGTH);
			appendStringTableData(outputStream, "", DEVICE_USAGE_NAME_COLUMN_LENGTH);
			appendStringTableData(outputStream, "OUT", DEVICE_USAGE_IO_COLUMN_LENGTH);

			int resultCount = deviceMethodMetaData->resultsSize;
			int realResultLength = 0;
			int resultIndex;
			for (resultIndex = 0; resultIndex < resultCount; resultIndex++) {
				DeviceArgument resultArgument = deviceMethodMetaData->results[resultIndex];
				realResultLength += getLengthOfType(resultArgument.type);
			}
			appendDecTableData(outputStream, realResultLength, DEVICE_USAGE_IO_SIZE_COLUMN_LENGTH);

			appendStringTableData(outputStream, "", DEVICE_USAGE_PARAM_NAME_COLUMN_LENGTH);
			appendStringTableData(outputStream, "", DEVICE_USAGE_PARAM_SIZE_COLUMN_LENGTH);
			appendStringTableData(outputStream, "", DEVICE_USAGE_PARAM_TYPE_COLUMN_LENGTH);
			appendTableSeparator(outputStream);
			println(outputStream);

            for (resultIndex = 0; resultIndex < resultCount; resultIndex++) {
                DeviceArgument resultArgument = deviceMethodMetaData->results[resultIndex];
                printArgument(outputStream, &resultArgument, resultIndex);
            }
			/*
            if (resultLength != realResultLength) {
                result = false;
                writeError(DEVICE_INTERFACE_PROBLEM);
                appendString(outputStream, "Result Parameters Definition ERROR !!!!!!");
                appendCRLF(outputStream);
                appendStringAndDec(outputStream, "resultCount=", resultCount);
                appendCRLF(outputStream);
                appendStringAndDec(outputStream, "resultLength=", resultLength);
                appendCRLF(outputStream);
                appendStringAndDec(outputStream, "realResultLength=", realResultLength);
                appendCRLF(outputStream);
            }

            if (resultCount == 0) {
                appendString(outputStream, "void");
            }
			*/
        }
		appendTableHeaderSeparatorLine(outputStream);
    }
    return result;
}

// Usage

/**
 * @private
 */
void printDeviceUsageLine(OutputStream* outputStream, char header, Device* device, bool showOnlyProblem) {
    DeviceInterface* deviceInterface = device->deviceInterface;

    int argumentLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_INPUT, true);
    int resultLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_OUTPUT, true);
    if (showOnlyProblem) {
        OutputStream nullOutputStream;
        initNullOutputStream(&nullOutputStream);
        bool ok = printMethodOrNotificationMetaData(&nullOutputStream, deviceInterface, header, argumentLength, resultLength, false);
        // If there is a problem, we relaunch with a real outputStream
        if (!ok) {
            printMethodOrNotificationMetaData(outputStream, deviceInterface, header, argumentLength, resultLength, false);
        }
    }
    else{
        printMethodOrNotificationMetaData(outputStream, deviceInterface, header, argumentLength, resultLength, false);
    }
}

void printDeviceHeader(OutputStream* outputStream, Device* device) {
	DeviceInterface* deviceInterface = device->deviceInterface;;
	const char* deviceName = deviceInterface->deviceGetName();

	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	int length = appendStringTableData(outputStream, deviceName, 0);
	char deviceHeader = deviceInterface->deviceHeader;
	appendString(outputStream, " : ");
	append(outputStream, deviceHeader);
	appendSpaces(outputStream, PRINT_TABLE_WRITER_DEFAULT_PAGE_CHAR_WIDTH - length - 5);
	appendTableSeparator(outputStream);
	println(outputStream);

	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "h", DEVICE_USAGE_HEADER_COLUMN_LENGTH);
	appendStringHeader(outputStream, "name", DEVICE_USAGE_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "I/0", DEVICE_USAGE_IO_COLUMN_LENGTH);
	appendStringHeader(outputStream, "L ", DEVICE_USAGE_IO_SIZE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "param/res name", DEVICE_USAGE_PARAM_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "L", DEVICE_USAGE_PARAM_SIZE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "type", DEVICE_USAGE_PARAM_TYPE_COLUMN_LENGTH);
	appendTableSeparator(outputStream);
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
}

void printDeviceUsage(OutputStream* outputStream, Device* device, bool showOnlyProblem) {
	printDeviceHeader(outputStream, device);
    char header;
    // We start after special characters and use only ANSI chars
	// We must search, because there is no list of header provided, we provide a char, and after this is catch (or not) by the device
    for (header = 32; header < 127; header++) {
        printDeviceUsageLine(outputStream, header, device, showOnlyProblem);
    }
}

void printDeviceListUsage(OutputStream* outputStream, bool showOnlyProblem) {
    println(outputStream);
    int deviceCount = getDeviceCount();
    int deviceIndex;
    for (deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++) {
        Device* device = getDevice(deviceIndex);
        printDeviceUsage(outputStream, device, showOnlyProblem);
    }
}

// Notification

/**
 * @private
 */
void printDeviceNotificationLine(OutputStream* outputStream, char header, Device* device) {
    DeviceInterface* deviceInterface = device->deviceInterface;

    int argumentLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_NOTIFY, true);
    printMethodOrNotificationMetaData(outputStream, deviceInterface, header, argumentLength, 0, true);
}

/**
 * @private
 */
void printDeviceNotification(OutputStream* outputStream, Device* device) {
	char header;
	// Not all Device have notification, so we check it before
	for (header = 32; header < 127; header++) {
		DeviceInterface* deviceInterface = device->deviceInterface;
		int argumentLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_NOTIFY, true);
		if (argumentLength != DEVICE_HEADER_NOT_HANDLED) {
			printDeviceHeader(outputStream, device);
			break;
		}
	}

    // We start after special characters and use only ANSI chars
    for (header = 32; header < 127; header++) {
        printDeviceNotificationLine(outputStream, header, device);
    }
}

void printDeviceListNotification(OutputStream* outputStream, bool showOnlyProblem) {
    println(outputStream);
    int deviceCount = getDeviceCount();
    int deviceIndex;
    for (deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++) {
        Device* device = getDevice(deviceIndex);
        printDeviceNotification(outputStream, device);
    }
}
