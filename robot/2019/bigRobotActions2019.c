#include "bigRobotActions2019.h"

#include "../../common/log/logger.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "fork2019.h"


bool bigDistributorLinePrepare(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "bigDistributorLinePrepare");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    fork2019Init(servoList);

    return true;
}

bool bigDistributorLineTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "bigDistributorLineTake");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    TofSensorList* tofSensorList = gameStrategyContext->tofSensorList;
    fork2019TakeSimplePuck(servoList, tofSensorList);

    return true;
}

bool acceleratorDrop(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "acceleratorDrop");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    fork2019AcceleratorDrop(servoList);

    return true;
}
