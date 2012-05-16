#include "strategyDevice.h"
#include "strategyDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyContext.h"

#include "../../robot/gameboard/gameboard.h"

#include "../../robot/2012/strategy2012.h"
#include "../../robot/2012/strategy2012Utils.h"
#include "../../robot/config/robotConfig.h"

// DEVICE INTERFACE

void initStrategy(void) {
    
}

void stopStrategy(void) {

}

BOOL isStrategyDeviceOk(void) {
    return TRUE;
}

void deviceStrategyHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
 	if (header == COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION) {

		// data
		int x = readHex4(inputStream);
		checkIsChar(inputStream, '-');
		int y = readHex4(inputStream);

		GameStrategyContext* context = getStrategyContext();

		context->opponentRobotPosition.x = x;
		if (isViolet()) {
			context->opponentRobotPosition.y = y;
		}
		else {
			// Opponent Robot position is relative to violet !
			context->opponentRobotPosition.y = GAMEBOARD_HEIGHT - y;
		}
		updatePathsAvailability();

        appendAck(outputStream);
        append(outputStream, COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION);
	}
	else if (header == COMMAND_STRATEGY_SET_CONFIG) {
		// data
		int c = readHex4(inputStream);
		GameStrategyContext* context = getStrategyContext();
		
		// TODO : Provide non specific function
		int strategyIndex = (c & CONFIG_STRATEGY_MASK);
		context->strategyIndex = strategyIndex;
		appendStringAndDec(getOutputStreamLogger(INFO), "setStrategy:", strategyIndex);
		println(getOutputStreamLogger(INFO));

		initStrategy2012(strategyIndex);
		if (c & CONFIG_COLOR_BLUE_MASK) {
			setColor(COLOR_VIOLET);
		}
		else {
			setColor(COLOR_RED);
		}

        appendAck(outputStream);
        append(outputStream, COMMAND_STRATEGY_SET_CONFIG);
	}
	// Print Gameboard
	else if (header == COMMAND_STRATEGY_PRINT_GAME_BOARD) {
		OutputStream* debugOutputStream = getOutputStreamLogger(ALWAYS);
		printStrategyAllDatas(debugOutputStream);
		printGameboard(debugOutputStream);
        appendAck(outputStream);
        append(outputStream, COMMAND_STRATEGY_PRINT_GAME_BOARD);
	}
	// next step
	else if (header == COMMAND_STRATEGY_NEXT_STEP) {
		GameStrategyContext* context = getStrategyContext();
        appendAck(outputStream);
        append(outputStream, COMMAND_STRATEGY_NEXT_STEP);
		// arguments
		if (context->hasMoreNextSteps) {
			context->mustDoNextStep = TRUE;
			appendHex2(outputStream, 1);
		}
		else {
			appendHex2(outputStream, 0);
		}
	}
	else if (header == COMMAND_STRATEGY_SET_ROBOT_POSITION) {
		GameStrategyContext* context = getStrategyContext();
		
		// status
		readHex2(inputStream);
		// separator
		checkIsChar(inputStream, '-');
		// x
		context->robotPosition.x = readHex4(inputStream);
		// separator
		checkIsChar(inputStream, '-');
		// y
		context->robotPosition.y = readHex4(inputStream);
		// separator
		checkIsChar(inputStream, '-');
		// angle in ddeg
		context->robotAngle = readHex4(inputStream);

		// output
        appendAck(outputStream);
        append(outputStream, COMMAND_STRATEGY_SET_ROBOT_POSITION);
	}
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initStrategy,
    .deviceShutDown = &stopStrategy,
    .deviceIsOk = &isStrategyDeviceOk,
    .deviceHandleRawData = &deviceStrategyHandleRawData,
};

DeviceDescriptor* getStrategyDeviceDescriptor() {
    return &descriptor;
}
