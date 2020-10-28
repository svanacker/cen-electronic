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


// LATERAL ARM

bool lightHouseLateralArmOn(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Arm On");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    if (isBlue2020(gameStrategyContext)) {
        // Left Arm
        lateralArm2020(servoList, 0x01);
    }
    else {
        // Right  Arm
        lateralArm2020(servoList, 0x02);
    }
    return true;
}


bool lightHouseLateralArmOff(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Arm Off");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    // Center lateral Arm
    lateralArm2020(servoList, 0x00);
    return true;
}


bool bigRobotPrepareFloorCenterCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Prepare Floor Center Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookPrepareFloorCenterAll(servoList);

    return true;
}

bool bigRobotPrepareFloorCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Prepare Floor Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookDownAll(servoList);

    return true;
}


bool bigRobotLockFloorCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Take Floor Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookLockFloorAll(servoList);

    return true;
}

bool bigRobotReleaseCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Drop Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookPrepareFloorAll(servoList);

    return true;
}


// 

bool bigRobotPrepareHook(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Prepare Hook");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookPrepareAll(servoList);
//    arm2020HookUpAll(servoList, false);
    
    return true;
}

bool bigRobotTakeCups(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Take Cups");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020TakeAndUpAll(servoList);

    return true;
}

bool bigRobotDropCupsPhase1(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Drop Cups 1");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020DownAndReleaseAll(servoList);

    return true;
}

bool bigRobotDropCupsPhase2(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Drop Cups 2");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;

    arm2020HookUpAll(servoList, 0);

    return true;
}
