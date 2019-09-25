#ifndef COMPOSED_GAIN_FACTOR_H
#define COMPOSED_GAIN_FACTOR_H

#include "gainFactor.h"
#include "distanceGainFactor.h"
#include "opponentRobotGainFactor.h"
#include "timeGainFactor.h"

#include "../gameTarget.h"
#include "../gameTargetAction.h"


/**
 * A Basic implementation of target gain which takes into account different sub
 * target gain factor strategy.
 */
typedef struct ComposedGainFactor {
    /** Reference to time gain factor function. */
    getTimeGainFactorFunction* timeGainFactor;
    /** Reference to distance gain factor function. */
    getDistanceGainFactorFunction* distanceGainFactor;
    /** Reference to opponent Robot gain factor function. */
    getOpponentRobotGainFactorFunction* opponentRobotGainFactor;
} ComposedGainFactor;

float getComposedGainFactor(ComposedGainFactor* composedGainFactor,
                              GameTarget* target,
                              GameTargetAction* targetAction,
                              float distanceToTargetAction,
                              float currentMatchingTime,
                              float opponentRobotX,
                              float opponentRobotY);

#endif
