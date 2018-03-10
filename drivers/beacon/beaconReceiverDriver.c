#include "beaconReceiverDriver.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/beacon/beaconReceiverDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

bool updateOpponentRobotPosition(Point* opponentRobotPosition) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, BEACON_RECEIVER_DEVICE_HEADER);
    append(outputStream, COMMAND_GET_OPPONENT_ROBOT_POSITION);

    bool result = transmitFromDriverRequestBuffer();

    opponentRobotPosition->x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
    // separator    
    readHex(inputStream);
    opponentRobotPosition->y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);

    return result;
}
