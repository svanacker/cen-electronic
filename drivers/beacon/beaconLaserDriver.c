#include "beaconLaserDriver.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../device/beacon/laserBeaconDeviceInterface.h"
#include "../../device/beacon/commonBeaconDeviceInterface.h"
#include "../../device/beacon/beaconReceiverDeviceInterface.h"

bool beaconLaserDriverServoStart() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_REMOTE_BEACON_SERVO_RUN);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool beaconLaserDriverServoStop() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_REMOTE_BEACON_SERVO_STOP);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

void appendRobotPosition(OutputStream* outputStream, char header, Point* point) {
    // out Data will be ?XXXX-YYYY, where ? will be replaced by the header
    append(outputStream, header);
    appendHex4(outputStream, point->x);
    append(outputStream, '-');
    appendHex4(outputStream, point->y);
}

bool notifyRobotPosition(Point* point) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    appendRobotPosition(outputStream, COMMAND_SET_OPPONENT_ROBOT_POSITION_FROM_LASER_TO_RECEIVER, point);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}
