#include "deviceUsage.h"

#include "device.h"
#include "deviceInterface.h"
#include "deviceList.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#define ARGUMENT_LIST_SEPARATOR '|'

#define ARGUMENT_SEPARATOR ';'

/**
 * @private
 */
void printArgumentList(OutputStream* outputStream, DeviceInterface* deviceInterface, char header, char headerLength, char inputMode) {
	if (headerLength != DEVICE_HEADER_NOT_HANDLED) {
		DeviceArgumentList* deviceArgumentList = getDeviceArgumentList();
        const char* deviceName = deviceInterface->deviceGetName();
        int argumentCount = deviceArgumentList->size;
        append(outputStream, inputMode);
        append(outputStream, ARGUMENT_LIST_SEPARATOR);
        appendString(outputStream, deviceName);
        append(outputStream, ARGUMENT_LIST_SEPARATOR);
        append(outputStream, header);
        int argumentIndex;
        append(outputStream, ARGUMENT_LIST_SEPARATOR);
        appendString(outputStream, deviceArgumentList->functionName);
        for (argumentIndex = 0; argumentIndex < argumentCount; argumentIndex++) {
            DeviceArgument deviceArgument = deviceArgumentList->args[argumentIndex];
            append(outputStream, ARGUMENT_LIST_SEPARATOR);
            char* argumentName = deviceArgument.name;
            appendString(outputStream, argumentName);
            append(outputStream, ARGUMENT_SEPARATOR);
            char type = deviceArgument.type;
            char argumentLength = (type >> 1) & 0xFE;
            appendDec(outputStream, argumentLength);
            append(outputStream, ARGUMENT_SEPARATOR);
            // last bit used for signed / unsigned
            if ((type & 1) != 0) {
                append(outputStream, 's');
            } else {
                append(outputStream, 'u');
            }
        }
        appendCRLF(outputStream);
    }
}

/**
 * @private
 */
void printDeviceUsageLine(OutputStream* outputStream, char header, Device* device) {
    DeviceInterface* deviceInterface = device->interface;
    // input Argument
    int headerLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_INPUT, TRUE);
    printArgumentList(outputStream, deviceInterface, header, headerLength, 'i');
    // output Argument
    headerLength = deviceInterface->deviceGetInterface(header, DEVICE_MODE_OUTPUT, TRUE);
    printArgumentList(outputStream, deviceInterface, header, headerLength, 'o');
}

void printDeviceUsage(OutputStream* outputStream, Device* device) {
    unsigned char header;
    // We start after special caracters and use only ANSI chars
    for (header = 32; header < 128; header++) {
        printDeviceUsageLine(outputStream, header, device);
    }
}

void printDeviceListUsage(OutputStream* outputStream) {
    appendCRLF(outputStream);
    int deviceCount = getDeviceCount();
    int deviceIndex;
    for (deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++) {
        Device* device = getDevice(deviceIndex);
        printDeviceUsage(outputStream, device);
    }
}
