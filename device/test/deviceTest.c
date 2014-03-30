#include "deviceTest.h"
#include "deviceTestInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

// TO DELETE
#include "../../main/motorboard/motorboard.h"

void deviceTestInit() {
}

void deviceTestShutDown() {
}

bool deviceTestIsOk() {
    return TRUE;
}

void deviceTestHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_TEST) {
        int arg1 = readHex2(inputStream);
		int arg2 = readHex2(inputStream);
        int result = arg1 + arg2;
        // data
        appendAck(outputStream);
        append(outputStream, COMMAND_TEST);
        appendHex2(outputStream, result);
    }
    /* TODO
    else if (header == COMMAND_NOTIFY_TEST) {
            int argument = readHex2(inputStream);
            argument *= 2;

            Buffer* buffer = getI2CSlaveOutputBuffer();
            OutputStream* i2cOutputStream = getOutputStream(buffer);

            // Add the value to I2C
            append(i2cOutputStream, COMMAND_NOTIFY_TEST);
            appendHex2(i2cOutputStream, argument);
		
            // Response to the call
            appendAck(outputStream);
            append(outputStream, COMMAND_NOTIFY_TEST);
            appendHex2(outputStream, argument);
    }
     */
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTestInit,
    .deviceShutDown = &deviceTestShutDown,
    .deviceIsOk = &deviceTestIsOk,
    .deviceHandleRawData = &deviceTestHandleRawData
};

DeviceDescriptor* getTestDeviceDescriptor() {
    return &descriptor;
}

