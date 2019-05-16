#include "tofDevice.h"
#include "tofDeviceInterface.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/timer/delayTimer.h"

#include "../../device/device.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../drivers/tof/tof.h"
#include "../../drivers/tof/tofList.h"
#include "../../drivers/tof/tofDebug.h"

// Forward declaration
TofSensorList* getTofDeviceTofSensorList(void);

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

void deviceTofHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_TOF_GET_DISTANCE) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_GET_DISTANCE);
        unsigned char tofIndex = readHex2(inputStream);
        TofSensorList* tofSensorList = getTofDeviceTofSensorList();
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
        
        appendHex4(outputStream, distanceMM);
    }
    else if (commandHeader == COMMAND_TOF_DEBUG) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_DEBUG);
        TofSensorList* tofSensorList = getTofDeviceTofSensorList();
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        // On this device, we dont't have access to the Point of View
        // See StrategyDevice to have it !
        tofSensorList->tofSensorListDebugTable(debugOutputStream, tofSensorList, NULL, 0.0f);
    }
    else if (commandHeader == COMMAND_TOF_BEEP_ON) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_BEEP_ON);
        TofSensorList* tofSensorList = getTofDeviceTofSensorList();
        tofSensorListBeep(tofSensorList, true);
    }
    else if (commandHeader == COMMAND_TOF_BEEP_OFF) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_BEEP_OFF);
        TofSensorList* tofSensorList = getTofDeviceTofSensorList();
        tofSensorListBeep(tofSensorList, false);
    }
    else if (commandHeader == COMMAND_TOF_SEARCH_IF_COLLIDING) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_SEARCH_IF_COLLIDING);
        TofSensorList* tofSensorList = getTofDeviceTofSensorList();

        unsigned int tofIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned int durationSeconds = readHex2(inputStream);
        unsigned int startTofIndex = 0;
        unsigned int endTofIndex = getTofSensorListSize(tofSensorList) - 1;
        if (tofIndex != 0xFF) {
            TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
            if (tofSensor == NULL) {
                return;
            }
            startTofIndex = tofIndex;
            endTofIndex = tofIndex;
        }
        Timer* timerDelay = timerDelayMark();
        while (!timerDelayTimeout(timerDelay, 1000 * durationSeconds)) {
            bool detected = false;
            for (tofIndex = startTofIndex; tofIndex <= endTofIndex; tofIndex++) {
                TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
                tofSensor->tofGetDistanceMM(tofSensor);
                if (isTofDistanceUnderThreshold(tofSensor)) {
                    detected = true;
                    break;
                }
            }
            tofSensorListBeep(tofSensorList, detected);
        }
        // Off the beep at the end
        tofSensorListBeep(tofSensorList, false);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTofInit,
    .deviceShutDown = &deviceTofShutDown,
    .deviceIsOk = &isTofDeviceOk,
    .deviceHandleRawData = &deviceTofHandleRawData,
};

TofSensorList* getTofDeviceTofSensorList(void) {
    return (TofSensorList*) descriptor.object;
}

DeviceDescriptor* getTofDeviceDescriptor(TofSensorList* tofSensorListParam) {
    descriptor.object = (int*)tofSensorListParam;
    return &descriptor;
}
