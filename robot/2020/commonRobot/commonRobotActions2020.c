#include "commonRobotActions2020.h"

#include "../../../common/log/logger.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/pwm/servo/servoList.h"

#include "../../../robot/strategy/gameStrategyContext.h"
#include "../../../robot/2020/strategy/strategy2020Utils.h"

bool commonAreActionsFinished(int* context) {
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    ServoList* servoList = gameStrategyContext->servoList;
    return !servoListStillWorking(servoList);
}