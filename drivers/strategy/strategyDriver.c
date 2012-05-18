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
#include "../../common/timer/timerList.h"

#include "../../device/strategy/strategyDeviceInterface.h"
#include "../../robot/match/startMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDevice.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../robot/opponent/opponentRobot.h"

#define STRATEGY_DRIVER_TIMER_INDEX			25

/**
 * Define the timer diviser to have a timer at approximatively 1,5 Hertz.
 * Use primer number to avoid synchronization problem
 */
#define TIME_DIVISER_1_5_HERTZ 				18181
#define FORCE_ROBOT_NEXT_STEP_COUNTER		5		

static unsigned int strategyDriverInterruptCounter;

void strategyDriverTimerCallback() {
	// enabled only if robot started
	if (!isStarted()) {
		return;
	}
	// disabled after end
	if (isEnd()) {
		return;
	}
	strategyDriverInterruptCounter++;
}

void forceRobotNextStepIfNecessary() {
	if (strategyDriverInterruptCounter >= FORCE_ROBOT_NEXT_STEP_COUNTER) {
		appendString(getOutputStreamLogger(ERROR), "forceRobotNextStepIfNecessary\n");
		strategyDriverInterruptCounter = 0;
		robotNextStep();
	}
}

/**
 * Initialize the strategy Driver and a timer used to send next Step in case of problem.
 */
void initStrategyDriver() {
	addTimer(STRATEGY_DRIVER_TIMER_INDEX, TIME_DIVISER_1_5_HERTZ, &strategyDriverTimerCallback);
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

BOOL sendStrategyConfiguration(int configuration) {
	appendString(getOutputStreamLogger(INFO), "sendStrategyConfiguration\n");

    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_STRATEGY_SET_CONFIG);
    appendHex4(outputStream, configuration);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL sendStrategyNextStep() {
	appendString(getOutputStreamLogger(INFO), "sendStrategyNextStep\n");

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
	OutputStream* debugOutputStream = getOutputStreamLogger(INFO);
	appendString(debugOutputStream, "sendStrategyOpponentRobotPosition: ");

    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION);
    appendHex4(outputStream, opponentRobotPosition->x);
    appendSeparator(outputStream);
    appendHex4(outputStream, opponentRobotPosition->y);

	appendStringAndDec(debugOutputStream, " x=", opponentRobotPosition->x);
	appendStringAndDec(debugOutputStream, ", y=", opponentRobotPosition->y);
	println(debugOutputStream);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL sentStrategyRobotPosition(unsigned char status, unsigned int x, unsigned int y, int angleInDeciDegree) {
	OutputStream* debugOutputStream = getOutputStreamLogger(INFO);
	appendString(debugOutputStream, "sentStrategyRobotPosition:");

    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, COMMAND_STRATEGY_SET_ROBOT_POSITION);
    appendHex2(outputStream, status);
    appendSeparator(outputStream);

    appendHex4(outputStream, x);
    appendSeparator(outputStream);

    appendHex4(outputStream, y);
    appendSeparator(outputStream);

    appendHex4(outputStream, angleInDeciDegree);

	appendStringAndDec(debugOutputStream, "status=", status);
	appendStringAndDec(debugOutputStream, ", x=", x);
	appendStringAndDec(debugOutputStream, ", y=", y);
	appendStringAndDec(debugOutputStream, ", angle=", angleInDeciDegree);
	println(debugOutputStream);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}
