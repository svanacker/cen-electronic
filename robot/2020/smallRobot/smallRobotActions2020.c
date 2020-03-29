#include "smallRobotActions2020.h"

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

// LATERAL ARM

bool lateralArmOn(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Arm On");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*) context;
    ServoList* servoList = gameStrategyContext->servoList;

    if (isBlue2020(gameStrategyContext)) {
        // Left Arm
        lateralArm2020(servoList, 0x01);
    } else {
        // Right  Arm
        lateralArm2020(servoList, 0x02);
    }
    return true;
}


bool lateralArmOff(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Arm Off");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*) context;
    ServoList* servoList = gameStrategyContext->servoList;
	// Center lateral Arm
    lateralArm2020(servoList, 0x00);
    return true;
}

// 

bool prepareHook(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Prepare Hook");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookPrepareAll(servoList);

    return true;
}

bool takeCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Take Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020TakeAndUpAll(servoList);

    return true;
}

bool dropCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Drop Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020DownAndReleaseAll(servoList);

    return true;
}
