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


// Main

#define ARGUMENTS_SEPARATOR                 ", "

#define DEVICE_NAME_AND_HEADER_SEPARATOR     ':'

#define DEVICE_HEADER_AND_TYPE_SEPARATOR    ':'

// Arguments

#define ARGUMENTS_START_CHAR                  '('

#define ARGUMENTS_NAME_AND_TYPE_SEPARATOR    ' '

#define ARGUMENTS_STOP_CHAR                  ')'

#define ARGUMENTS_AND_RESULTS_SEPARATOR        " => "


void printTypeAsString(OutputStream* outputStream, int parameterType) {
    switch (parameterType) {
        case DEVICE_ARG_SEPARATOR : return;
        case DEVICE_ARG_UNSIGNED_CHAR_1 : appendString(outputStream, "u1"); return;
        case DEVICE_ARG_UNSIGNED_CHAR_2 : appendString(outputStream, "u_2"); return;
        case DEVICE_ARG_UNSIGNED_HEX_2 : appendString(outputStream, "hex_u_2"); return;
        case DEVICE_ARG_SIGNED_HEX_2 : appendString(outputStream, "hex_s_2"); return;
        case DEVICE_ARG_UNSIGNED_HEX_3 : appendString(outputStream, "hex_u_3"); return;
        case DEVICE_ARG_UNSIGNED_HEX_4 : appendString(outputStream, "hex_u_4"); return;
        case DEVICE_ARG_SIGNED_HEX_4 : appendString(outputStream, "hex_s_4"); return;
        case DEVICE_ARG_UNSIGNED_HEX_5 : appendString(outputStream, "hex_u_5"); return;
        case DEVICE_ARG_SIGNED_HEX_5 : appendString(outputStream, "hex_s_5"); return;
        case DEVICE_ARG_UNSIGNED_HEX_6 : appendString(outputStream, "hex_u_6"); return;
        case DEVICE_ARG_FIXED_CHAR_ARRAY: appendString(outputStream, "charArray4_length_8"); return;
        case DEVICE_ARG_SIGNED_HEX_6 : appendString(outputStream, "hex_s_6"); return;
        case DEVICE_ARG_UNSIGNED_HEX_8 : appendString(outputStream, "hex_u_8"); return;
        case DEVICE_ARG_SIGNED_HEX_8 : appendString(outputStream, "hex_s_8"); return;
        case DEVICE_ARG_UNSIGNED_HEX_9 : appendString(outputStream, "hex_u_9"); return;
        case DEVICE_ARG_UNSIGNED_HEX_10 : appendString(outputStream, "hex_u_10"); return;
        case DEVICE_ARG_UNSIGNED_HEX_12 : appendString(outputStream, "hex_u_12"); return;
    }
    writeError(DEVICE_INTERFACE_PROBLEM);
    appendString(outputStream, "??????"); return;
}

/**
 * @private.
 * Print Argument Or Result
 * @return the size of the argument
 */
unsigned int printArgument(OutputStream* outputStream, DeviceArgument* deviceArgument, int argumentIndex) {
    if (argumentIndex > 0) {
        appendString(outputStream, ARGUMENTS_SEPARATOR);
    }    
    char* argumentName = deviceArgument->name;
    char type = deviceArgument->type;
    unsigned int result = getLengthOfType(type);
    if (result == -1) {
        writeError(DEVICE_INTERFACE_PROBLEM);
        appendStringAndDec(outputStream, "type length Problem !!! : ", type);
    }

    printTypeAsString(outputStream, type);
   
    // Argument name
    append(outputStream, ARGUMENTS_NAME_AND_TYPE_SEPARATOR);
    appendString(outputStream, argumentName);
    
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
        char deviceHeader = deviceInterface->deviceHeader;

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
        int realArgumentLength = 0;
        for (argumentIndex = 0; argumentIndex < argumentCount; argumentIndex++) {
            DeviceArgument deviceArgument = deviceMethodMetaData->arguments[argumentIndex];
            realArgumentLength += printArgument(outputStream, &deviceArgument, argumentIndex);
        }
        append(outputStream,  ARGUMENTS_STOP_CHAR);

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

        // results
        if (!notification) {
            appendString(outputStream, ARGUMENTS_AND_RESULTS_SEPARATOR);
            append(outputStream,  ARGUMENTS_START_CHAR);
            int resultCount = deviceMethodMetaData->resultsSize;
            int realResultLength = 0;
            int resultIndex;
            for (resultIndex = 0; resultIndex < resultCount; resultIndex++) {
                DeviceArgument resultArgument = deviceMethodMetaData->results[resultIndex];
                realResultLength += printArgument(outputStream, &resultArgument, resultIndex);
            }

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
        }
        append(outputStream,  ARGUMENTS_STOP_CHAR);
        appendString(outputStream, ":");
        appendDec(outputStream, argumentLength);
        appendString(outputStream, "=>");
        appendDec(outputStream, resultLength);
        println(outputStream);
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

void printDeviceUsage(OutputStream* outputStream, Device* device, bool showOnlyProblem) {
    char header;
    // We start after special characters and use only ANSI chars
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
