#include "lightHouseDevice2020.h"

#include "lightHouse2020.h"
#include "lightHouse2020Actions.h"
#include "lightHouse2020Debug.h"
#include "lightHouseDeviceInterface2020.h"

#include <stdbool.h>

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/pwm/servo/servoList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/deviceConstants.h"
#include "lightHouse2020Workflow.h"

static LightHouse2020* lightHouse;

void deviceLightHouse2020Init(void) {

}

void deviceLightHouse2020ShutDown(void) {

}

bool deviceLightHouse2020IsOk(void) {
    return true;
}

void deviceLightHouse2020HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // DEBUG
    if (commandHeader == COMMAND_LIGHT_HOUSE_2020_DEBUG) {
        ackCommand(outputStream, LIGHT_HOUSE_2020_DEVICE_HEADER, COMMAND_LIGHT_HOUSE_2020_DEBUG);
        lightHouse2020Debug(lightHouse, getDebugOutputStreamLogger());
    }// UP
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_UP) {
        ackCommand(outputStream, LIGHT_HOUSE_2020_DEVICE_HEADER, COMMAND_LIGHT_HOUSE_2020_UP);
        lightHouse2020Up(lightHouse);
    }// BOTTOM
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_BOTTOM) {
        ackCommand(outputStream, LIGHT_HOUSE_2020_DEVICE_HEADER, COMMAND_LIGHT_HOUSE_2020_BOTTOM);
        lightHouse2020Bottom(lightHouse);
    }// INIT
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_INIT) {
        ackCommand(outputStream, LIGHT_HOUSE_2020_DEVICE_HEADER, COMMAND_LIGHT_HOUSE_2020_INIT);
        lightHouse2020ResetWorkflow(lightHouse);
    }
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_SHOW) {
        ackCommand(outputStream, LIGHT_HOUSE_2020_DEVICE_HEADER, COMMAND_LIGHT_HOUSE_2020_SHOW);
        lightHouse2020RotationOn(lightHouse);
        lightHouse2020On(lightHouse);
    }
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_OFF) {
        ackCommand(outputStream, LIGHT_HOUSE_2020_DEVICE_HEADER, COMMAND_LIGHT_HOUSE_2020_OFF);
        lightHouse2020RotationOff(lightHouse);
        lightHouse2020Off(lightHouse);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLightHouse2020Init,
    .deviceShutDown = &deviceLightHouse2020ShutDown,
    .deviceIsOk = &deviceLightHouse2020IsOk,
    .deviceHandleRawData = &deviceLightHouse2020HandleRawData,
};

DeviceDescriptor* getLightHouse2020DeviceDescriptor(LightHouse2020* lightHouseParam) {
    lightHouse = lightHouseParam;
    return &descriptor;
}
