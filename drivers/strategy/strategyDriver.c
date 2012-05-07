#include "strategyDriver.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/strategy/strategyDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

BOOL sendStrategyConfiguration(int configuration) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_SET_CONFIG);
    appendHex4(outputStream, configuration);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL sendStrategyNextStep() {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_NEXT_STEP);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL sendStrategyOpponentRobotPosition(int x, int y) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_SET_OPPONENT_ROBOT_POSITION);
    appendHex4(outputStream, x);
    appendSeparator(outputStream);
    appendHex4(outputStream, x);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}
