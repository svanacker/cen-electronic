#include <stdlib.h>

#include "beaconReceiverDevice.h"
#include "beaconReceiverDeviceInterface.h"
#include "commonBeaconDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/2d/2d.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../drivers/jennic/jennic5139Driver.h"

/** Robot opponent point. */
static Point opponentRobotPosition;

void clearOpponentRobotPosition() {
    opponentRobotPosition.x = 0;
    opponentRobotPosition.y = 0;
}

void beaconReceiverDeviceInit() {
    clearOpponentRobotPosition();
}

void beaconReceiverDeviceShutDown() {

}

bool beaconReceiverDeviceIsOk() {
    return true;
}

void beaconReceiverDeviceHandleRawData(char commandHeader,
                             InputStream* inputStream,
                             OutputStream* outputStream) {
    // init Jennic Router
    if (commandHeader == COMMAND_INIT_JENNIC_AS_ROUTER) {
        // data
        appendAck(outputStream);
        append(outputStream, COMMAND_INIT_JENNIC_AS_ROUTER);

        initJennic5139Router();
    }
    // Receive Network status
    else if (commandHeader == COMMAND_GET_RECEIVER_NETWORK_STATUS) {
        appendAck(outputStream);
        append(outputStream, COMMAND_GET_RECEIVER_NETWORK_STATUS);
        appendHex2(outputStream, getJennicNetworkStatus());
    }
    // Handle the notification sent by the beacon Main Board via Zigbee
    else if (commandHeader == COMMAND_SET_OPPONENT_ROBOT_POSITION_FROM_LASER_TO_RECEIVER) {
        appendAck(outputStream);
        append(outputStream, COMMAND_SET_OPPONENT_ROBOT_POSITION_FROM_LASER_TO_RECEIVER);

        opponentRobotPosition.x = readHex4(inputStream);
        checkIsSeparator(inputStream);
        opponentRobotPosition.y = readHex4(inputStream);
    }
    // Ask the opponent Robot position stored by the receiver
    else if (commandHeader == COMMAND_GET_OPPONENT_ROBOT_POSITION) {
        // data
        appendAck(outputStream);
        append(outputStream, COMMAND_GET_OPPONENT_ROBOT_POSITION);

        // Write Data
        appendHex4(outputStream, opponentRobotPosition.x);
        appendSeparator(outputStream);
        appendHex4(outputStream, opponentRobotPosition.y);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &beaconReceiverDeviceInit,
    .deviceShutDown = &beaconReceiverDeviceShutDown,
    .deviceIsOk = &beaconReceiverDeviceIsOk,
    .deviceHandleRawData = &beaconReceiverDeviceHandleRawData
};

DeviceDescriptor* getBeaconReceiverDeviceDescriptor() {
    return &descriptor;
}

