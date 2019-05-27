#include "bigRobotActions2019.h"

#include "../../../common/log/logger.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../robot/strategy/gameStrategyContext.h"
#include "../../../robot/2019/strategy/strategy2019Utils.h"

#include "../../../robot/2019/commonRobot/commonRobotActions2019.h"
#include "../../../robot/2019/fork/fork2019.h"
#include "../../../robot/2019/fork/forkAccelerator2019.h"
#include "../../../robot/2019/distributor/distributor2019.h"

bool bigDistributorLinePrepare(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> bigDistributorLinePrepare");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    distributor2019PrepareTake(servoList);

    return true;
}

bool bigDistributorLineTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "-> bigDistributorLineTake");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    TofSensorList* tofSensorList = gameStrategyContext->tofSensorList;
    distributor2019Take(servoList, tofSensorList);

    return true;
}

bool bigDistributorAcceleratorDrop(int* context) {
    return acceleratorDrop(context, " -> big Distributor Accelerator Drop");
}

