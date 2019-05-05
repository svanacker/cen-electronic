#include "smallRobotActions2019.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/pwm/servo/servoList.h"

#include "../../robot/strategy/gameStrategyContext.h"

// 2019
#include "../../robot/2019/fork2019.h"
#include "../../robot/2019/strategy2019Utils.h"

bool acceleratorArmOn(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "Accelerator Arm On");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    if (isViolet(gameStrategyContext)) {
        // Right Arm
        arm2019On(servoList, FORK_2019_RIGHT_INDEX);
    }
    else {
        // Left Arm
        arm2019On(servoList, FORK_2019_LEFT_INDEX);
    }
    // TODO
    return true;
}

bool acceleratorArmOff(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "Accelerator Arm Off");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    if (isViolet(gameStrategyContext)) {
        // Right Arm
        arm2019Off(servoList, FORK_2019_RIGHT_INDEX);
    }
    else {
        // Left Arm
        arm2019Off(servoList, FORK_2019_LEFT_INDEX);
    }
    // TODO
    return true;
}

bool goldeniumPrepareTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "goldeniumPrepareTake");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    if (isViolet(gameStrategyContext)) {
        fork2019PrepareTakeGoldenium(servoList, FORK_2019_RIGHT_INDEX);
    }
    else {
        fork2019PrepareTakeGoldenium(servoList, FORK_2019_LEFT_INDEX);
    }
    return true;
}

bool goldeniumTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "goldeniumTake");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    TofSensorList* tofSensorList = gameStrategyContext->tofSensorList; 
    if (isViolet(gameStrategyContext)) {
        fork2019TakeGoldenium(servoList, tofSensorList, FORK_2019_RIGHT_INDEX);
    }
    else {
        fork2019TakeGoldenium(servoList, tofSensorList, FORK_2019_LEFT_INDEX);
    }

    return true;
}

bool goldeniumPrepareDrop(int* context) {
    /*
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "goldeniumPrepareDrop");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    */

    // WHAT TO DO ?

    return true;
}

bool goldeniumDrop(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "goldeniumDrop");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    if (isViolet(gameStrategyContext)) {
        fork2019DropGoldenium(servoList, FORK_2019_RIGHT_INDEX);
    }
    else {
        fork2019DropGoldenium(servoList, FORK_2019_LEFT_INDEX);
    }
    return true;
}
