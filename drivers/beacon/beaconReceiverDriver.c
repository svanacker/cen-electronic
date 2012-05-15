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

BOOL updateOpponentRobotPosition(Point* opponentRobotPosition) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, COMMAND_GET_OPPONENT_ROBOT_POSITION);

    BOOL result = transmitFromDriverRequestBuffer();

	opponentRobotPosition->x = readHex4(inputStream);
	// separator	
	readHex(inputStream);
	opponentRobotPosition->y = readHex4(inputStream);

    return result;
}
