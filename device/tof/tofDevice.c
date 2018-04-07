#include "tofDevice.h"
#include "tofDeviceInterface.h"

#include <stdbool.h>

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../drivers/tof/tof.h"
#include "../../drivers/tof/tofList.h"
#include "../../drivers/tof/tofDebug.h"

static TofSensorList* tofSensorList;

// DEVICE INTERFACE

void deviceTofInit(void) {
    // MUST ALREADY HAVE BEEN INIT BY THE CONSTRUCTOR of tofList
}

void deviceTofShutDown(void) {

}

bool isTofDeviceOk(void) {
    // SVA : TODO
    return true;
}

void deviceTofHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_TOF_GET_DISTANCE) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_GET_DISTANCE);
            unsigned char tofIndex = readHex2(inputStream);
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
        
        appendHex4(outputStream, distanceMM);
    }
    else if (commandHeader == COMMAND_TOF_DEBUG) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        tofSensorList->tofSensorListDebugTable(debugOutputStream, tofSensorList);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTofInit,
    .deviceShutDown = &deviceTofShutDown,
    .deviceIsOk = &isTofDeviceOk,
    .deviceHandleRawData = &deviceTofHandleRawData,
};

DeviceDescriptor* getTofDeviceDescriptor(TofSensorList* tofSensorListParam) {
    tofSensorList = tofSensorListParam;
    return &descriptor;
}
