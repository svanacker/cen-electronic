#include <stdbool.h>
#include <stdlib.h>

#include "systemDevice.h"
#include "systemDeviceInterface.h"

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

#include "../../common/system/system.h"

#include "../../device/device.h"
#include "../../device/deviceList.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"
#include "../../device/transmitMode.h"

void deviceSystemInit(void) {
}

void deviceSystemShutDown(void) {
} 

bool deviceSystemIsOk(void) {
    return true;
}

void deviceSystemHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_PING) {
        // data
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_PING);
        
        // Read and write in output the pingIndex (to control that it's the right which does the response)
        unsigned char pingIndex = readHex2(inputStream);
        appendHex2(outputStream, pingIndex);
    }
    else if (header == COMMAND_GET_LAST_ERROR) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_GET_LAST_ERROR);
        unsigned int lastError = getLastError();
        appendHex4(outputStream, lastError);
    }
    else if (header == COMMAND_CLEAR_LAST_ERROR) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_CLEAR_LAST_ERROR);
        clearLastError();
    }
    else if (header == COMMAND_DEVICE_LIST) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_DEVICE_LIST);
        printDeviceList(getInfoOutputStreamLogger());
    } else if (header == COMMAND_USAGE) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_USAGE);
        printDeviceListUsage(getInfoOutputStreamLogger());
    }
     else if (header == COMMAND_USAGE_SPECIFIC_DEVICE) {
         ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_USAGE_SPECIFIC_DEVICE);
         char deviceHeader = readBinaryChar(inputStream);
         int size = getDeviceCount();
         int i;
         for (i = 0; i < size; i++) {
             Device* device = getDevice(i);
             if (deviceHeader == device->deviceInterface->deviceHeader) {
                 println(getInfoOutputStreamLogger());
                 printDeviceUsage(getInfoOutputStreamLogger(), device);
                 return;
             }
         }
         appendString(getErrorOutputStreamLogger(), "Device Not Found ! ");
    } else if (header == COMMAND_USAGE) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_USAGE);
        printDeviceListUsage(getInfoOutputStreamLogger());
    }
    else if (header == COMMAND_NOTIFICATION) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_NOTIFICATION);
        printDeviceListNotification(getInfoOutputStreamLogger());
    } else if (header == COMMAND_WAIT) {
        appendAck(outputStream);
        int mSec = readHex4(inputStream);
        delaymSec(mSec);
        append(outputStream, SYSTEM_DEVICE_HEADER);
        append(outputStream, COMMAND_WAIT);
    } else if (header == COMMAND_PIC_NAME) {
        appendString(getAlwaysOutputStreamLogger(), getPicName());
        println(getAlwaysOutputStreamLogger());
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_PIC_NAME);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSystemInit,
    .deviceShutDown = &deviceSystemShutDown,
    .deviceIsOk = &deviceSystemIsOk,
    .deviceHandleRawData = &deviceSystemHandleRawData,
};

DeviceDescriptor* getSystemDeviceDescriptor(void) {
    return &descriptor;
}
