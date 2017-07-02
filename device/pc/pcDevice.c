#include <stdbool.h>
#include <stdlib.h>

#include "pcDevice.h"
#include "pcDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/error/error.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/loggerDebug.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../../device/device.h"
#include "../../device/deviceDescriptor.h"
#include "../../device/deviceList.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"
#include "../../device/transmitMode.h"

void devicePcInit(void) {
}

void devicePcShutDown(void) {
} 

bool devicePcIsOk(void) {
    return true;
}

void devicePcHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_PIPE_LIST) {
        // data
        ackCommand(outputStream, PC_DEVICE_HEADER, COMMAND_PIPE_LIST);
        // TODO : PipeList
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &devicePcInit,
    .deviceShutDown = &devicePcShutDown,
    .deviceIsOk = &devicePcIsOk,
    .deviceHandleRawData = &devicePcHandleRawData,
};

DeviceDescriptor* getPcDeviceDescriptor(void) {
    return &descriptor;
}
