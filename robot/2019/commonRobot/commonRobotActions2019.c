#include "commonRobotActions2019.h"

#include "../../../common/log/logger.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../robot/strategy/gameStrategyContext.h"
#include "../../../robot/2019/strategy/strategy2019Utils.h"

#include "../../../robot/2019/fork/fork2019.h"
#include "../../../robot/2019/fork/forkAccelerator2019.h"

bool acceleratorDrop(int* context, const char* logName) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, logName);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    if (isViolet(gameStrategyContext)) {
        fork2019AcceleratorDrop(servoList, FORK_2019_RIGHT_INDEX, FORK_2019_LEFT_INDEX);
    }
    else {
        fork2019AcceleratorDrop(servoList, FORK_2019_LEFT_INDEX, FORK_2019_RIGHT_INDEX);
    }

    return true;
}
