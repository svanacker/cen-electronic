#include "test2Device.h"
#include "test2DeviceInterface.h"

#include <stdbool.h>

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"
#include "../../drivers/test/testDriver.h"

void deviceTest2Init(void) {
}

void deviceTest2ShutDown(void) {
}

bool deviceTest2IsOk(void) {
    return true;
}

void deviceTest2HandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_TEST2) {
        int arg1 = readHex2(inputStream);
        int arg2 = readHex2(inputStream);
        int result = arg1 + arg2;

        ackCommand(outputStream, TEST2_DEVICE_HEADER, COMMAND_TEST2);
        // data
        appendHex2(outputStream, result);
    }
    else if (commandHeader == COMMAND_INTENSIVE_TEST_DRIVER) {
        ackCommand(outputStream, TEST2_DEVICE_HEADER, COMMAND_INTENSIVE_TEST_DRIVER);
        unsigned int count = readHex4(inputStream);
        testDriverIntensive(count);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTest2Init,
    .deviceShutDown = &deviceTest2ShutDown,
    .deviceIsOk = &deviceTest2IsOk,
    .deviceHandleRawData = &deviceTest2HandleRawData
};

DeviceDescriptor* getTest2DeviceDescriptor(void) {
    return &descriptor;
}

