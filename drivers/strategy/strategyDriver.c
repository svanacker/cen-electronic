#include "strategyDriver.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/strategy/strategyDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

BOOL sendStrategyConfiguration(int configuration) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_STRATEGY_SET_CONFIG);
    appendHex4(outputStream, configuration);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL sendStrategyNextStep() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, COMMAND_STRATEGY_NEXT_STEP);

    BOOL result = transmitFromDriverRequestBuffer();
    if (result) {
        int result = readHex2(inputStream);
		return result;
    }
    return FALSE;
}

BOOL sendStrategyOpponentRobotPosition(Point* opponentRobotPosition) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION);
    appendHex4(outputStream, opponentRobotPosition->x);
    appendSeparator(outputStream);
    appendHex4(outputStream, opponentRobotPosition->y);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL sentStrategyRobotPosition(unsigned char status, unsigned int x, unsigned int y, int angleInDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_STRATEGY_SET_ROBOT_POSITION);
    appendHex2(outputStream, status);
    appendSeparator(outputStream);

    appendHex4(outputStream, x);
    appendSeparator(outputStream);

    appendHex4(outputStream, y);
    appendSeparator(outputStream);

    appendHex4(outputStream, angleInDeciDegree);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}
