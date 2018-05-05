#include <stdbool.h>

#include "strategyDevice.h"
#include "strategyDeviceInterface.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

#include "../../navigation/navigation.h"
#include "../../navigation/locationList.h"
#include "../../navigation/locationListDebug.h"
#include "../../navigation/pathList.h"
#include "../../navigation/pathListDebug.h"

#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyContextDebug.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyDebug.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameStrategyListDebug.h"
#include "../../robot/strategy/gameStrategyItem.h"
#include "../../robot/strategy/gameTargetListDebug.h"

#include "../../robot/2018/strategy2018.h"
#include "../../robot/2018/strategy2018Utils.h"
#include "../../robot/config/robotConfig.h"

// Forward declaration
GameStrategyContext* getStrategyDeviceGameStrategyContext(void);

// DEVICE INTERFACE

void initStrategy(void) {
}

void stopStrategy(void) {

}

bool isStrategyDeviceOk(void) {
    return true;
}

void deviceStrategyHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_STRATEGY_GET_OPPONENT_ROBOT_POSITION) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_GET_OPPONENT_ROBOT_POSITION);
        // data
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        appendHexFloat4(outputStream, context->opponentRobotPosition->x, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, context->opponentRobotPosition->y, POSITION_DIGIT_MM_PRECISION);

    }
    else if (commandHeader == COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION) {

        // data
        float x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        float y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);

        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();

        context->opponentRobotPosition->x = x;
        context->opponentRobotPosition->y = y;
        updatePathsAvailability(context);

        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION);
    }
    // Debug
    else if (commandHeader == COMMAND_STRATEGY_DEBUG) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        printGameStrategyContext(debugOutputStream, context);
    }
	// List Strategies
	else if (commandHeader == COMMAND_STRATEGY_LIST_DEBUG) {
		OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_LIST_DEBUG);
        printGameStrategyTableList(debugOutputStream);
	}
	// Specific Strategy
	else if (commandHeader == COMMAND_STRATEGY_ITEM_DEBUG) {
		int strategyIndex = readHex2(inputStream);
		GameStrategy* gameStrategy = getGameStrategy(strategyIndex);
		OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_ITEM_DEBUG);
        printGameStrategyTable(debugOutputStream, gameStrategy);
	}
    // next step
    else if (commandHeader == COMMAND_STRATEGY_NEXT_STEP) {
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        // response
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_NEXT_STEP);
        // output arguments : we have only last information !
        appendHex2(outputStream, context->hasMoreNextSteps);

        // do the job synchronously to avoid problems of notification
        context->hasMoreNextSteps = nextStep(context);
    }
    // ROBOT POSITION
    else if (commandHeader == COMMAND_STRATEGY_GET_ROBOT_POSITION) {
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_GET_ROBOT_POSITION);
        // x
        appendHexFloat4(outputStream, context->robotPosition->x, POSITION_DIGIT_MM_PRECISION);
        // separator
        appendSeparator(outputStream);
        // y
        appendHexFloat4(outputStream, context->robotPosition->y, POSITION_DIGIT_MM_PRECISION);
        // separator
        appendSeparator(outputStream);
        // angle in decideg
        appendHexFloat4(outputStream, context->robotAngle, ANGLE_DIGIT_DEGREE_PRECISION);
    }
    else if (commandHeader == COMMAND_STRATEGY_SET_ROBOT_POSITION) {
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SET_ROBOT_POSITION);
        // x
        context->robotPosition->x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        // separator
        checkIsSeparator(inputStream);
        // y
        context->robotPosition->y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        // separator
        checkIsSeparator(inputStream);
        // angle in decideg
        context->robotAngle = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
    }
    // SCORE
    else if (commandHeader == COMMAND_STRATEGY_GET_GLOBAL_SCORE) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_GET_GLOBAL_SCORE);
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        appendHex4(outputStream, context->score);
    }
    // TARGET LIST
    else if (commandHeader == COMMAND_TARGET_LIST_DEBUG) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_TARGET_LIST_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        GameTargetList* gameTargetList = getGameTargetList();
        printGameTargetListTable(gameTargetList, debugOutputStream);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initStrategy,
    .deviceShutDown = &stopStrategy,
    .deviceIsOk = &isStrategyDeviceOk,
    .deviceHandleRawData = &deviceStrategyHandleRawData,
};

DeviceDescriptor* getStrategyDeviceDescriptor(GameStrategyContext* gameStrategyContext) {
    descriptor.object = (int*) gameStrategyContext;
    return &descriptor;
}

/**
* @private.
*/
GameStrategyContext* getStrategyDeviceGameStrategyContext(void) {
    return (GameStrategyContext*)(descriptor.object);
}