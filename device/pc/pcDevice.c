#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

/** The stream in which we will write the content of a file */
static OutputStream* commandOutputStream;

void devicePcInit(void) {
}

void devicePcShutDown(void) {
} 

bool devicePcIsOk(void) {
    return true;
}

void devicePcHandleRawData(unsigned char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (header == COMMAND_PIPE_LIST) {
        // data
        ackCommand(outputStream, PC_DEVICE_HEADER, COMMAND_PIPE_LIST);
        // TODO : PipeList
    }
    else if (header == COMMAND_LOAD_COMMAND_FILE) {
        // data
        ackCommand(outputStream, PC_DEVICE_HEADER, COMMAND_LOAD_COMMAND_FILE);
        int c;
        FILE *file;
        file = fopen("C:/dev/git/svanacker/cen-electronic-data/command.txt", "r");
        if (file != NULL) {
            while ((c = getc(file)) != EOF) {
                append(commandOutputStream, c);
            }
            fclose(file);
        }
        else {
            writeError(PC_FILE_NOT_FOUND);
        }
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &devicePcInit,
    .deviceShutDown = &devicePcShutDown,
    .deviceIsOk = &devicePcIsOk,
    .deviceHandleRawData = &devicePcHandleRawData,
};

DeviceDescriptor* getPcDeviceDescriptor(OutputStream* outputStream) {
    commandOutputStream = outputStream;
    return &descriptor;
}
