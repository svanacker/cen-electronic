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
#include "../../robot/config/robotConfig.h"

// DEVICE INTERFACE

void initStrategy(void) {
    
}

void stopStrategy(void) {

}

unsigned int isStrategyDeviceOk(void) {
    return TRUE;
}

void deviceStrategyHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
 	if (header == COMMAND_SET_OPPONENT_ROBOT_POSITION) {

		// data
		int x = readHex4(inputStream);
		checkIsChar(inputStream, '-');
		int y = readHex4(inputStream);

		GameStrategyContext* context = getStrategyContext();
		context->opponentRobotPosition.x = x;
		context->opponentRobotPosition.y = y;

        appendAck(outputStream);
        append(outputStream, COMMAND_SET_OPPONENT_ROBOT_POSITION);
	}
	else if (header == COMMAND_SET_CONFIG) {
		// data
		int c = readHex4(inputStream);
		GameStrategyContext* context = getStrategyContext();
		if (c & CONFIG_DEBUG_MASK) {
			context->color = COLOR_VIOLET;
		}
		else {
			context->color = COLOR_RED;
		}
		// TODO : Provide non specific function
		initStrategy2012(0);
        appendAck(outputStream);
        append(outputStream, COMMAND_SET_CONFIG);
	}
	// Print Gameboard
	else if (header == COMMAND_PRINT_GAME_BOARD) {
		OutputStream* debugOutputStream = getOutputStreamLogger(ALWAYS);
		printGameboard(debugOutputStream);
        appendAck(outputStream);
        append(outputStream, COMMAND_PRINT_GAME_BOARD);
	}
	// next step
	else if (header == COMMAND_NEXT_STEP) {
		nextStep();
        appendAck(outputStream);
        append(outputStream, COMMAND_NEXT_STEP);
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
