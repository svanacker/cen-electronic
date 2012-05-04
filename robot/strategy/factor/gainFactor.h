#ifndef GAIN_FACTOR_H
#define GAIN_FACTOR_H

#include "gainFactor.h"
#include "composedGainFactor.h"
#include "../../../robot/strategy/gameTarget.h"
#include "../../../robot/strategy/gameTargetAction.h"

#define DEFAULT_GAIN 		1.0f

float getGainFunction(	  GameTarget* target,
						  GameTargetAction* targetAction,
						  float distanceToTargetAction,
						  float currentMatchingTime,
						  float opponentRobotX,
						  float opponentRobotY);

#endif
