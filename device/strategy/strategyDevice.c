#include <stdbool.h>

#include "strategyDevice.h"
#include "strategyDeviceInterface.h"

#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/timer/delayTimer.h"

#include "../../common/math/cenMath.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

#include "../../navigation/navigation.h"
#include "../../navigation/locationList.h"
#include "../../navigation/locationListDebug.h"
#include "../../navigation/pathList.h"
#include "../../navigation/pathListDebug.h"

#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyCollisionHandler.h"
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyContextDebug.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyDebug.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameStrategyListDebug.h"
#include "../../robot/strategy/gameStrategyItem.h"
#include "../../robot/strategy/gameTargetListDebug.h"
#include "../../robot/strategy/gameStrategyHandler.h"

#include "../../robot/2019/strategy2019.h"
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

void deviceStrategyHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
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
    else if (commandHeader == COMMAND_STRATEGY_SHOW_TOF_LIST_WITH_PROJECTION) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SHOW_TOF_LIST_WITH_PROJECTION);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        TofSensorList* tofSensorList = context->tofSensorList;
        Point* robotPosition = context->robotPosition;
        float robotAngleRadian = context->robotAngleRadian;
        tofSensorList->tofSensorListDebugTable(debugOutputStream, tofSensorList, robotPosition, robotAngleRadian);
    }
    else if (commandHeader == COMMAND_STRATEGY_SEARCH_IF_COLLIDING) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SEARCH_IF_COLLIDING);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        TofSensorList* tofSensorList = context->tofSensorList;
        unsigned int tofIndex = readHex2(inputStream);
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        unsigned int i;
        for (i = 0; i < 100; i++) {
            timerDelayMilliSeconds(100);
            if (i % 10 == 0) {
                appendCRLF(debugOutputStream);
            }
            tofSensor->tofGetDistanceMM(tofSensor);
            bool detection = isTofDistanceUnderThreshold(tofSensor);
            if (detection) {
                append(debugOutputStream, '.');
            }
        }
    }
    // Debug
    else if (commandHeader == COMMAND_STRATEGY_DEBUG) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_DEBUG);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        printGameStrategyContext(debugOutputStream, context);
    }
	// List Strategies
	else if (commandHeader == COMMAND_STRATEGY_LIST_DEBUG) {
		OutputStream* debugOutputStream = getInfoOutputStreamLogger();
		ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_LIST_DEBUG);
        printGameStrategyTableList(debugOutputStream);
	}
	// Specific Strategy
	else if (commandHeader == COMMAND_CURRENT_STRATEGY_ITEM_LIST_DEBUG) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_CURRENT_STRATEGY_ITEM_LIST_DEBUG);
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        GameStrategy* gameStrategy = context->gameStrategy;
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        if (gameStrategy == NULL) {
            appendString(debugOutputStream, "Strategy 0 => NO STRATEGY");
            return;
        }
        // Index are 0-based
        printGameStrategyTable(debugOutputStream, gameStrategy);
	}
    // next step
    else if (commandHeader == COMMAND_STRATEGY_NEXT_STEP) {
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        // response
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_NEXT_STEP);

        // do the job synchronously for actions, and asynchronously for move (ask the MOTOR_BOARD)
        bool hasDoneSomeAction = nextStep(context);
        appendBool(outputStream, hasDoneSomeAction);
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
        appendHexFloat4(outputStream, radToDeg(context->robotAngleRadian), ANGLE_DIGIT_DEGREE_PRECISION);
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
        context->robotAngleRadian = degToRad(readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION));
        // Must call the motor Board to synchronized the both positions !
        updateRobotPositionFromMainBoardToMotorBoard(context);
    }
    else if (commandHeader == COMMAND_STRATEGY_SET_ROBOT_POSITION_AS_FIRST_LOCATION_OF_PATH_INDEX) {
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_SET_ROBOT_POSITION_AS_FIRST_LOCATION_OF_PATH_INDEX);
        unsigned pathIndex = readHex2(inputStream);
        PathData* path = getPath(context->navigation->paths, pathIndex);
        Location* location1 = path->location1;
        context->robotPosition->x = location1->x;
        context->robotPosition->y = location1->y;
        context->robotAngleRadian = path->angleRadian1;
#ifndef _MSC_VER
        // Must call the motor Board to synchronized the both positions !
        updateRobotPositionFromMainBoardToMotorBoard(context);
#endif // !_MSC_VER
    }
    // DO ALL TARGET ACTION ITEM OF AN ACTION
    else if (commandHeader == COMMAND_TARGET_ACTION_DO_ALL_ITEMS) {
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_TARGET_ACTION_DO_ALL_ITEMS);
        // target Index
        unsigned char targetIndex = readHex2(inputStream);
        GameTarget* gameTarget = getGameTarget(targetIndex);
        // separator
        checkIsSeparator(inputStream);
        // target Action
        unsigned char targetActionIndex = readHex2(inputStream);
        GameTargetAction* gameTargetAction = getGameTargetAction(&(gameTarget->actionList), targetActionIndex);

        doGameTargetAction(gameTargetAction, (int*)context);
    }
    
    // SCORE
    else if (commandHeader == COMMAND_STRATEGY_GET_GLOBAL_SCORE) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_STRATEGY_GET_GLOBAL_SCORE);
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        appendHex4(outputStream, context->score);
    }
    // TARGET 
    else if (commandHeader == COMMAND_TARGET_LIST_DEBUG) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_TARGET_LIST_DEBUG);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        GameTargetList* gameTargetList = getGameTargetList();
        printGameTargetListTable(gameTargetList, debugOutputStream);
    }
    else if (commandHeader == COMMAND_TARGET_NEXT) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_TARGET_NEXT);
        GameStrategyContext* context = getStrategyDeviceGameStrategyContext();
        GameTarget* gameTarget = findNextTarget(context);
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        if (gameTarget != NULL) {
            appendString(debugOutputStream, gameTarget->name);
        }
        else {
            appendString(debugOutputStream, "TARGET IS NULL !");
        }
    }
    else if (commandHeader == COMMAND_TARGET_SET_STATUS) {
        ackCommand(outputStream, STRATEGY_DEVICE_HEADER, COMMAND_TARGET_SET_STATUS);
        // target Index
        unsigned char targetIndex = readHex2(inputStream);
        GameTarget* gameTarget = getGameTarget(targetIndex);
        // separator
        checkIsSeparator(inputStream);
        // target Status
        enum GameTargetStatus targetStatus = (enum GameTargetStatus) readHex(inputStream);
        gameTarget->status = targetStatus;
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