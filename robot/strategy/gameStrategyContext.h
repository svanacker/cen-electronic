#ifndef GAME_STRATEGY_CONTEXT_H
#define GAME_STRATEGY_CONTEXT_H

#include "../../common/2d/2d.h"

#include "gameStrategy.h"
#include "gameTarget.h"
#include "gameTargetAction.h"

#include "../../robot/match/teamColor.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"

/**
 * Encapsulates the context of the strategy.
 */
typedef struct GameStrategyContext {
	/** The choosen gameStrategy. */
	GameStrategy* gameStrategy;
	/** The elapsedMatchTime in seconds .*/
	float elapsedMatchTime;
	/** Position of robot. */
	Point robotPosition;
	/** The nearestLocation of the robot. */
	Location* nearestLocation;
	// Opponent Robot.
	Point opponentRobotPosition;
	/** current Target. */
	GameTarget* currentTarget;
	/** current Target Action. */
	GameTargetAction* currentTargetAction;
	/** current trajectory of the robot. */
	LocationList currentTrajectory;
	/** Color. */
	TEAM_COLOR color;
} GameStrategyContext;

/**
 * Print the context of the game Strategy.
 */
void printGameStrategyContext(OutputStream* outputStream, GameStrategyContext* context);

#endif

