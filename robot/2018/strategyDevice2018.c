#include "strategyDevice2018.h"

#include "strategyDeviceInterface2018.h"
#include "distributor2018.h"
#include "distributorDebug2018.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/color/colorDebug.h"

static Distributor* distributor;

void deviceStrategy2018Init(void) {

}

void deviceStrategy2018ShutDown(void) {

}

bool deviceStrategy2018IsOk(void) {
    return true;
}

void deviceStrategy2018HandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == STRATEGY_2018_GET_SCORE) {
        OutputStream* infoOutputStream = getInfoOutputStreamLogger();
        printDistributor2018Score(infoOutputStream, distributor);
        ackCommand(outputStream, STRATEGY_2018_DEVICE_HEADER, STRATEGY_2018_GET_SCORE);
    } else if (commandHeader == STRATEGY_2018_DISTRIBUTOR_DEBUG_COMMAND) {
        OutputStream* infoOutputStream = getInfoOutputStreamLogger();
        ackCommand(outputStream, STRATEGY_2018_DEVICE_HEADER, STRATEGY_2018_DISTRIBUTOR_DEBUG_COMMAND);
        appendHex2(outputStream, distributor->score);
        printDistributor2018(infoOutputStream, distributor);
    } else if (commandHeader == STRATEGY_2018_READ_BALL_COLOR_TYPE) {
        OutputStream* infoOutputStream = getInfoOutputStreamLogger();
        ColorSensor* colorSensor = distributor->colorSensor;
        enum ColorType colorType = colorSensorFindColorType2018(colorSensor);
        printColorType(infoOutputStream, colorType);
        ackCommand(outputStream, STRATEGY_2018_DEVICE_HEADER, STRATEGY_2018_READ_BALL_COLOR_TYPE);
    } else if (commandHeader == STRATEGY_2018_UNICOLOR_COMMAND) {
        loadUnicolorDistributorWithColorCheck(distributor);
        ackCommand(outputStream, STRATEGY_2018_DEVICE_HEADER, STRATEGY_2018_UNICOLOR_COMMAND);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceStrategy2018Init,
    .deviceShutDown = &deviceStrategy2018ShutDown,
    .deviceIsOk = &deviceStrategy2018IsOk,
    .deviceHandleRawData = &deviceStrategy2018HandleRawData,
};

DeviceDescriptor* getStrategy2018DeviceDescriptor(Distributor* distributorParam) {
    distributor = distributorParam;
    return &descriptor;
}
