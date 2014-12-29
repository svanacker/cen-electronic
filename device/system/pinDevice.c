#include "pinDevice.h"
#include "pinDeviceInterface.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"

#include "../../device/device.h"

void devicePinInit() {
}

void devicePinShutDown() {
}

bool devicePinIsOk() {
    return true;
}    

void devicePinHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_SET_PIN_VALUE) {
        int pinIndex = readHex2(inputStream);
        int pinValue = readHex2(inputStream);
        appendAck(outputStream);
        setPinValue(pinIndex, pinValue);
        append(outputStream, COMMAND_SET_PIN_VALUE);
    } else if (header == COMMAND_GET_PIN_VALUE) {
        int pinIndex = readHex2(inputStream);
        appendAck(outputStream);

        int pinValue = getPinValue(pinIndex);

        // Response
        append(outputStream, COMMAND_GET_PIN_VALUE);
        appendHex2(outputStream, pinValue);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &devicePinInit,
    .deviceShutDown = &devicePinShutDown,
    .deviceIsOk = &devicePinIsOk,
    .deviceHandleRawData = &devicePinHandleRawData,
};

DeviceDescriptor* getPinDeviceDescriptor() {
    return &descriptor;
}

