#include <stdlib.h>

#include "device.h"
#include "deviceDebug.h"
#include "deviceList.h"
#include "transmitMode.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

#define DEVICE_DEBUG_TABLE_HEADER_LENGTH	66

void printDeviceHeader(OutputStream* outputStream) {
	appendRepeatedDash(outputStream, DEVICE_DEBUG_TABLE_HEADER_LENGTH);
	println(outputStream);
	appendStringHeader(outputStream, "deviceName         ");
	appendStringHeader(outputStream, "header");
	appendStringHeader(outputStream, "transmitMode");
	appendStringHeader(outputStream, "addString");
	appendStringHeader(outputStream, "addr");
	appendTableSeparator(outputStream);
	println(outputStream);
	appendRepeatedDash(outputStream, DEVICE_DEBUG_TABLE_HEADER_LENGTH);
}

void printDeviceList(OutputStream* outputStream) {
    int size = getDeviceCount();
    appendStringAndDec(outputStream, ", deviceCount=", size);
    int i;
	println(outputStream);
	printDeviceHeader(outputStream);
    println(outputStream);
    for (i = 0; i < size; i++) {
        Device* device = getDevice(i);
        printDevice(outputStream, device);
    }
	appendRepeatedDash(outputStream, DEVICE_DEBUG_TABLE_HEADER_LENGTH);
}

void printDevice(OutputStream* outputStream, const Device* device) {
    if (device != NULL) {
        DeviceInterface* deviceInterface = device->deviceInterface;
		appendStringTableData(outputStream, deviceInterface->deviceGetName(), 19);

		appendCharTableData(outputStream, deviceInterface->deviceHeader, 7);

        TransmitMode transmitMode = device->transmitMode;
		char* transmitModeAsString = getTransmitModeAsString(transmitMode);

		appendStringTableData(outputStream, transmitModeAsString, 12);

		appendStringTableData(outputStream, device->addressString, 9);

		// TODO : Replace by appendDecTableData
		appendTableSeparator(outputStream);
		int length = appendDec(outputStream, device->address);
		appendSpaces(outputStream, 6 - length);
		appendTableSeparator(outputStream);

		println(outputStream);
    }
}
