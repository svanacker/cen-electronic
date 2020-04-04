#include "bigRobotActions2020.h"

#include "../../../common/log/logger.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../robot/strategy/gameStrategyContext.h"
#include "../../../robot/2020/strategy/strategy2020Utils.h"

#include "../../../robot/2020/commonRobot/commonRobotActions2020.h"

#include "../../../common/math/cenMath.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../common/log/logger.h"

#include "../../../common/pwm/servo/servoList.h"

#include "../../../robot/strategy/gameStrategyContext.h"

#include "../../../client/motion/simple/clientMotion.h"

// 2020
#include "../../../robot/2020/arm/arm2020.h"
#include "../../../robot/2020/navigation/angle2020.h"
#include "../../../robot/2020/strategy/strategy2020Utils.h"
#include "../../../robot/2020/commonRobot/commonRobotActions2020.h"

// 

bool bigRobotPrepareFloorCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Prepare Floor Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookPrepareFloorAll(servoList, false);

    return true;
}

bool bigRobotLockFloorCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Take Floor Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookLockFloorAll(servoList, true);

    return true;
}

bool bigRobotReleaseCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Drop Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookPrepareFloorAll(servoList, true);

    return true;
}
