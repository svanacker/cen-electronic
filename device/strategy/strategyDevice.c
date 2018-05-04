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

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameStrategyListDebug.h"
#include "../../robot/strategy/gameStrategyItem.h"

#include "../../robot/2018/strategy2018.h"
#include "../../robot/2018/strategy2018Utils.h"
#include "../../robot/config/robotConfig.h"

// Forward declaration
GameStrategyContext* getStrategyDeviceGameStrategyContext(void);

// DEVICE INTERFACE

void initStrategy(void) {
    initStrategy2018(getStrategyDeviceGameStrategyContext(), 0);
}

void stopStrategy(void) {

}

bool isStrategyDeviceOk(void) {
    return true;
}

void deviceStrategyHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
     if (commandHeader == COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION) {

        // data
        float x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        float y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);

        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();

        context->opponentRobotPosition->x = x;
        if (isGreen(context)) {
            context->opponentRobotPosition->y = y;
        }
        else {
            // Opponent Robot position is relative to violet !
            context->opponentRobotPosition->y = GAMEBOARD_HEIGHT - y;
        }
        updatePathsAvailability(context);

        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION);
    }
    else if (commandHeader == COMMAND_STRATEGY_SET_CONFIG) {
        // data
        int c = readHex4(inputStream);
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SET_CONFIG);

        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        
        // TODO : Provide non specific function
        int strategyIndex = (c & CONFIG_STRATEGY_MASK);
        context->strategyIndex = strategyIndex;
        appendStringAndDec(getInfoOutputStreamLogger(), "setStrategy:", strategyIndex);
        println(getInfoOutputStreamLogger());

        initStrategy2018(context, strategyIndex);
        if (c & CONFIG_COLOR_GREEN_MASK) {
            setColor(context, TEAM_COLOR_GREEN);
        }
        else {
            setColor(context, TEAM_COLOR_ORANGE);
        }
    }
	// List Strategies
	else if (commandHeader == COMMAND_STRATEGY_LIST) {
		OutputStream* debugOutputStream = getAlwaysOutputStreamLogger();
		ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_LIST);
        printGameStrategyTableList(debugOutputStream);
	}
	// Specific Strategy
	else if (commandHeader == COMMAND_STRATEGY_ITEM) {
		// int strategyIndex = readHex2(inputStream);
		// GameStrategy* gameStrategy = getGameStrategy(strategyIndex);
		// OutputStream* debugOutputStream = getAlwaysOutputStreamLogger();
		ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_ITEM);
		// TODO printGameStrategy(debugOutputStream, gameStrategy);
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
    else if (commandHeader == COMMAND_STRATEGY_SET_ROBOT_POSITION) {
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        // output before any notification !!
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SET_ROBOT_POSITION);
        
        // status
        unsigned int status = readHex2(inputStream);
        // separator
        checkIsSeparator(inputStream);
        // x
        context->robotPosition->x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        // separator
        checkIsSeparator(inputStream);
        // y
        context->robotPosition->y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        // separator
        checkIsSeparator(inputStream);
        // angle in ddeg
        context->robotAngle = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);

        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        appendStringAndDec(debugOutputStream, "\nStrategySetRobotPosition:status=", status);
        appendStringAndDecf(debugOutputStream, ", x=", context->robotPosition->x);
        appendStringAndDecf(debugOutputStream, ", y=", context->robotPosition->y);
        appendStringAndDecf(debugOutputStream, ", angle=", context->robotAngle);
        println(debugOutputStream);
    
        /*
        // After Robot position update, if the status corresponds to collision, handle collision
        if (status == NOTIFY_MOTION_ARG_OBSTACLE) {
            handleCollision();
        }
        */
    }
    // SCORE
    else if (commandHeader == COMMAND_STRATEGY_GET_GLOBAL_SCORE) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_GET_GLOBAL_SCORE);
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        appendHex4(outputStream, context->score);
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