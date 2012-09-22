#include "deviceDebug.h"
#include <stdlib.h>

#include "device.h"
#include "deviceList.h"

#include "../common/commons.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"


// DEBUG
void printDeviceList(OutputStream* outputStream) {
    int size = getDeviceCount();
	appendStringAndDec(outputStream, ", deviceCount=", size);
    int i;
	println(outputStream);
    for (i = 0; i < size; i++) {
        Device* device = getDevice(i);
        printDevice(outputStream, device);
    }
}

/**
 * Print the device information.
 */
void printDevice(OutputStream* outputStream, const Device* device) {
	if (device != NULL) {
		appendStringAndDec(outputStream, ", transmitMode=", device->transmitMode);
		appendKeyAndName(outputStream, ", addressString=", device->addressString);
		appendStringAndDec(outputStream, ", address=", device->address);
		println(outputStream);
	}
}
