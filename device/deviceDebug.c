#include <stdlib.h>

#include "device.h"
#include "deviceDebug.h"
#include "deviceList.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

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

void printDevice(OutputStream* outputStream, const Device* device) {
    if (device != NULL) {
        DeviceInterface* deviceInterface = device->interface;
        appendString(outputStream, "deviceName=");
        appendString(outputStream, deviceInterface->deviceGetName());
        appendStringAndDec(outputStream, ", header=", deviceInterface->deviceHeader);

        appendStringAndDec(outputStream, ", transmitMode=", device->transmitMode);
        appendKeyAndName(outputStream, ", addressString=", device->addressString);
        appendStringAndDec(outputStream, ", address=", device->address);
        println(outputStream);
    }
}
