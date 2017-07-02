#include <stdlib.h>

#include "device.h"
#include "deviceDebug.h"
#include "deviceList.h"
#include "transmitMode.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

#define DEVICE_DEBUG_NAME_COLUMN_LENGTH				25
#define DEVICE_DEBUG_HEADER_COLUMN_LENGTH			5
#define DEVICE_DEBUG_TRANSMIT_MODE_COLUMN_LENGTH	8
#define DEVICE_DEBUG_ADDRESS_COLUMN_LENGTH			9
#define DEVICE_DEBUG_ADDRESS_STRING_COLUMN_LENGTH	16
#define DEVICE_DEBUG_LAST_COLUMN_LENGTH             40

/**
 * Private.
 */
void printDeviceDebugHeader(OutputStream* outputStream) {
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "deviceName", DEVICE_DEBUG_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "cmd", DEVICE_DEBUG_HEADER_COLUMN_LENGTH);
	appendStringHeader(outputStream, "transmit", DEVICE_DEBUG_TRANSMIT_MODE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "address", DEVICE_DEBUG_ADDRESS_COLUMN_LENGTH);
	appendStringHeader(outputStream, "addString", DEVICE_DEBUG_ADDRESS_STRING_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, DEVICE_DEBUG_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printDeviceList(OutputStream* outputStream) {
    int size = getDeviceCount();
    appendStringAndDec(outputStream, ", deviceCount=", size);
    int i;
	println(outputStream);
	printDeviceDebugHeader(outputStream);
    for (i = 0; i < size; i++) {
        Device* device = getDevice(i);
		if (i > 0 && (i % 4) == 0) {
			appendTableHeaderSeparatorLine(outputStream);
		}
        printDevice(outputStream, device);
    }
	appendTableHeaderSeparatorLine(outputStream);
}

void printDevice(OutputStream* outputStream, const Device* device) {
    if (device != NULL) {
        DeviceInterface* deviceInterface = device->deviceInterface;
		appendStringTableData(outputStream, deviceInterface->deviceGetName(), DEVICE_DEBUG_NAME_COLUMN_LENGTH);

		appendCharTableData(outputStream, deviceInterface->deviceHeader, DEVICE_DEBUG_HEADER_COLUMN_LENGTH);

        TransmitMode transmitMode = device->transmitMode;
		const char* transmitModeAsString = getTransmitModeAsString(transmitMode);

		appendStringTableData(outputStream, transmitModeAsString, DEVICE_DEBUG_TRANSMIT_MODE_COLUMN_LENGTH);

		appendDecTableData(outputStream, device->address, DEVICE_DEBUG_ADDRESS_COLUMN_LENGTH);
		appendStringTableData(outputStream, device->addressString, DEVICE_DEBUG_ADDRESS_STRING_COLUMN_LENGTH);

		appendEndOfTableColumn(outputStream, DEVICE_DEBUG_LAST_COLUMN_LENGTH);
    }
}
