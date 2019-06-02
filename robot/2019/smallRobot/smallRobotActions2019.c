#include "smallRobotActions2019.h"

#include "../../../common/math/cenMath.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../common/log/logger.h"

#include "../../../common/pwm/servo/servoList.h"

#include "../../../robot/strategy/gameStrategyContext.h"

#include "../../../client/motion/simple/clientMotion.h"

// 2019
#include "../../../robot/2019/navigation/angle2019.h"
#include "../../../robot/2019/arm/arm2019.h"
#include "../../../robot/2019/commonRobot/commonRobotActions2019.h"
#include "../../../robot/2019/elevator/elevator2019.h"
#include "../../../robot/2019/fork/fork2019.h"
#include "../../../robot/2019/goldenium/goldenium2019.h"
#include "../../../robot/2019/strategy/strategy2019Utils.h"
#include "../../../robot/2019/distributor/distributor2019.h"

#define SMALL_DISTRIBUTOR_PREPARE_ACTION_LOG_NAME     "-> smallDistributorLinePrepare"
#define SMALL_DISTRIBUTOR_TAKE_ACTION_LOG_NAME        "-> smallDistributorLineTake"
#define SMALL_DISTRIBUTOR_DROP_ACTION_LOG_NAME        " -> smallDistributorDrop "

#define BIG_DISTRIBUTOR_LINE_3_PREPARE_ACTION_LOG_NAME     "-> bigDistributorLine3Prepare"
#define BIG_DISTRIBUTOR_LINE_3_TAKE_ACTION_LOG_NAME        "-> bigDistributorLine3Take"
#define BIG_DISTRIBUTOR_LINE_3_DROP_ACTION_LOG_NAME        "-> bigDistributorDrop3"

#define BIG_DISTRIBUTOR_LINE_2_PREPARE_ACTION_LOG_NAME     "-> bigDistributorLine2Prepare"
#define BIG_DISTRIBUTOR_LINE_2_TAKE_ACTION_LOG_NAME        "-> bigDistributorLine2Take"
#define BIG_DISTRIBUTOR_LINE_2_DROP_ACTION_LOG_NAME        "-> bigDistributorDrop2"

// -------------------------------------------- ARM & ACCELERATOR -----------------------------------------------

bool acceleratorArmOn(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Accelerator Arm On");
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
    // We will take the goldenium just after
    moveElevatorToScanGoldenium(servoList, false);
    // TODO
    return true;
}

bool acceleratorRotationIfNeeded(int* context) {
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    appendStringCRLF(getDebugOutputStreamLogger(), "-> acceleratorRotationIfNeeded");
    if (isViolet(gameStrategyContext)) {
        // Left
        if (gameStrategyContext->simulateMove) {
            gameStrategyContext->robotAngleRadian += degToRad(DEG_90);
        }
        else {
            if (gameStrategyContext->robotAngleRadian >= degToRad(-10.0f) && gameStrategyContext->robotAngleRadian <= degToRad(10.0f)) {
                motionDriverLeft(DEG_90);
                timerDelayMilliSeconds(2000);
            }
        }
    }
    else {
        // Right
        if (gameStrategyContext->simulateMove) {
            gameStrategyContext->robotAngleRadian -= degToRad(DEG_90);
        }
        else {
            if ((gameStrategyContext->robotAngleRadian >= degToRad(170.0f) && gameStrategyContext->robotAngleRadian <= degToRad(190.0f)))
            {
                motionDriverRight(DEG_90);
                timerDelayMilliSeconds(2000);
            }
        }
    }
    return true;
}

bool acceleratorArmOff(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> Accelerator Arm Off");
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

// -------------------------------------------- GOLDENIUM  -----------------------------------------------

bool goldeniumPrepareTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> goldeniumPrepareTake");
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
    appendStringCRLF(debugOutputStream, "-> goldeniumTake");
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
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> goldeniumPrepareDrop");
    /*
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    */

    // WHAT TO DO ?

    return true;
}

bool goldeniumDrop(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> goldeniumDrop");
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

// -------------------------------------------- SMALL DISTRIBUTOR  -----------------------------------------------


bool smallDistributorLinePrepare(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, SMALL_DISTRIBUTOR_PREPARE_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    distributor2019PrepareTake(servoList);

    return true;
}

bool smallDistributorLineTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, SMALL_DISTRIBUTOR_TAKE_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    TofSensorList* tofSensorList = gameStrategyContext->tofSensorList;
    
    if (isViolet(gameStrategyContext)) {
        distributor2019Take(servoList, tofSensorList, FORK_2019_RIGHT_INDEX);
    }
    else {
        distributor2019Take(servoList, tofSensorList, FORK_2019_LEFT_INDEX);
    }

    return true;
}

bool smallDistributorAcceleratorDrop(int* context) {
    return acceleratorDrop(context, SMALL_DISTRIBUTOR_DROP_ACTION_LOG_NAME);
}

// -------------------------------------------- BIG DISTRIBUTOR LINE 3 / REDIUM GREENIUM 

bool bigDistributorLine3Prepare(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, BIG_DISTRIBUTOR_LINE_3_PREPARE_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    distributor2019PrepareTake(servoList);

    return true;
}

bool bigDistributorLine3Take(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, BIG_DISTRIBUTOR_LINE_3_TAKE_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    TofSensorList* tofSensorList = gameStrategyContext->tofSensorList;
    
    if (isViolet(gameStrategyContext)) {
        distributor2019Take(servoList, tofSensorList, FORK_2019_RIGHT_INDEX);
    }
    else {
        distributor2019Take(servoList, tofSensorList, FORK_2019_LEFT_INDEX);
    }

    return true;
}

bool bigDistributorLine3Drop(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, BIG_DISTRIBUTOR_LINE_3_DROP_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, true);

    return true;
}

// -------------------------------------------- BIG DISTRIBUTOR LINE 2 / BLUEIUM / GREENIUM

bool bigDistributorLine2Prepare(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, BIG_DISTRIBUTOR_LINE_2_PREPARE_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    distributor2019PrepareTake(servoList);

    return true;
}

bool bigDistributorLine2Take(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, BIG_DISTRIBUTOR_LINE_2_TAKE_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    TofSensorList* tofSensorList = gameStrategyContext->tofSensorList;
    
    if (isViolet(gameStrategyContext)) {
        distributor2019Take(servoList, tofSensorList, FORK_2019_RIGHT_INDEX);
    }
    else {
        distributor2019Take(servoList, tofSensorList, FORK_2019_LEFT_INDEX);
    }
    
    // The last move, and we don't want to hurt the Big Robot => We disabled the tof
    tofSensorListSetEnableUsageType(tofSensorList, TOF_SENSOR_USAGE_TYPE_COLLISION, false);

    return true;
}

bool bigDistributorLine2Drop(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, BIG_DISTRIBUTOR_LINE_2_DROP_ACTION_LOG_NAME);
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, true);

    return true;
}
