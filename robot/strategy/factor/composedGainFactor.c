#include <stdlib.h>

#include "composedGainFactor.h"

#include "../../../robot/strategy/gameTarget.h"
#include "../../../robot/strategy/gameTargetAction.h"

float getComposedGainFactor(ComposedGainFactor* composedGainFactor,
        GameTarget* target,
        GameTargetAction* targetAction,
        float distanceToTargetAction,
        float currentMatchingTime,
        float opponentRobotX,
        float opponentRobotY) {
    float result;
    // Basic Gain
    float targetGainFactorValue = target->potentialGain;

    // Distance : TODO
    float distanceGainFactorValue = distanceToTargetAction;
    if (composedGainFactor->distanceGainFactor != NULL) {
        distanceGainFactorValue = composedGainFactor->distanceGainFactor(distanceToTargetAction, 1.0);
    }

    // Time : TODO : Constant to remove
    float timeToAchieve = targetAction->timeToAchieve;
    float timeFactorValue = timeToAchieve;
    if (composedGainFactor->timeGainFactor != NULL) {
        timeFactorValue = composedGainFactor->timeGainFactor(currentMatchingTime, 90000, timeToAchieve);
    }

    float obstacleGainFactorValue = 1.0;
    if (composedGainFactor->opponentRobotGainFactor != NULL) {
        obstacleGainFactorValue = composedGainFactor->opponentRobotGainFactor(opponentRobotX, opponentRobotY);
    }

    result = targetGainFactorValue * distanceGainFactorValue * obstacleGainFactorValue * timeFactorValue;

    return result;
}
