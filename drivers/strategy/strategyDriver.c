#include <stdlib.h>
#include "strategyDriver.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerConstants.h"
#include "../../common/timer/timerList.h"

#include "../../device/deviceConstants.h"
#include "../../device/strategy/strategyDeviceInterface.h"
#include "../../robot/match/startMatchDevice.h"
#include "../../robot/match/endMatchDetectorDevice.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../robot/opponent/opponentRobot.h"


/**
 * Define the timer divider to have a timer at approximatively 1,5 Hertz.
 * Use primer number to avoid synchronization problem
 */
#define TIME_DIVIDER_1_5_HERTZ                 18181
#define FORCE_ROBOT_NEXT_STEP_COUNTER        5        

static unsigned int strategyDriverInterruptCounter;

void strategyDriverTimerCallback(Timer* timer) {
    /* TODO
    // enabled only if robot started
    if (!isStarted()) {
        return;
    }
    // disabled after end
    if (isEnd()) {
        return;
    }
    strategyDriverInterruptCounter++;
    */
}

void forceRobotNextStepIfNecessary() {
    if (strategyDriverInterruptCounter >= FORCE_ROBOT_NEXT_STEP_COUNTER) {
        appendString(getErrorOutputStreamLogger(), "forceRobotNextStepIfNecessary\n");
        strategyDriverInterruptCounter = 0;
        robotNextStep();
    }
}

/**
 * Initialize the strategy Driver and a timer used to send next Step in case of problem.
 */
void initStrategyDriver() {
    addTimer(STRATEGY_DRIVER_TIMER_INDEX, TIME_DIVIDER_1_5_HERTZ, &strategyDriverTimerCallback, "STRATEGY", NULL);
}

void robotNextStep() {
    // Clear interrupt counter
    strategyDriverInterruptCounter = 0;
    Point* opponentRobotPosition = getLastOpponentRobotPosition();

    // Send strategy opponent Robot position
    sendStrategyOpponentRobotPosition(opponentRobotPosition );

    // Send next Step
    sendStrategyNextStep();
}

bool sendStrategyConfiguration(int configuration) {
    appendString(getInfoOutputStreamLogger(), "sendStrategyConfiguration\n");

    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, STRATEGY_DEVICE_HEADER);
    append(outputStream, COMMAND_STRATEGY_SET_CONFIG);
    appendHex4(outputStream, configuration);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool sendStrategyNextStep() {
    appendString(getInfoOutputStreamLogger(), "sendStrategyNextStep\n");

    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, STRATEGY_DEVICE_HEADER);
    append(outputStream, COMMAND_STRATEGY_NEXT_STEP);

    bool resultFromDriver = transmitFromDriverRequestBuffer();
    if (resultFromDriver) {
        int result = readHex2(inputStream);
        return result;
    }
    return false;
}

bool sendStrategyOpponentRobotPosition(Point* opponentRobotPosition) {
    OutputStream* debugOutputStream = getInfoOutputStreamLogger();
    appendString(debugOutputStream, "sendStrategyOpponentRobotPosition: ");

    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, STRATEGY_DEVICE_HEADER);
    append(outputStream, COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION);
    appendHex4(outputStream, (signed int) opponentRobotPosition->x);
    appendSeparator(outputStream);
    appendHex4(outputStream, (signed int) opponentRobotPosition->y);

    appendStringAndDecf(debugOutputStream, " x=", opponentRobotPosition->x);
    appendStringAndDecf(debugOutputStream, ", y=", opponentRobotPosition->y);
    println(debugOutputStream);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool sentStrategyRobotPosition(unsigned char status, float x, float y, float angleDegree) {
    OutputStream* debugOutputStream = getInfoOutputStreamLogger();
    appendString(debugOutputStream, "sentStrategyRobotPosition:");

    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, STRATEGY_DEVICE_HEADER);
    append(outputStream, COMMAND_STRATEGY_SET_ROBOT_POSITION);
    appendHex2(outputStream, status);
    appendSeparator(outputStream);

    appendHexFloat4(outputStream, x, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);

    appendHexFloat4(outputStream, y, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);

    appendHexFloat4(outputStream, angleDegree, ANGLE_DIGIT_DEGREE_PRECISION);

    appendStringAndDecf(debugOutputStream, "status=", status);
    appendStringAndDecf(debugOutputStream, ", x=", x);
    appendStringAndDecf(debugOutputStream, ", y=", y);
    appendStringAndDecf(debugOutputStream, ", angle=", angleDegree);
    println(debugOutputStream);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}
