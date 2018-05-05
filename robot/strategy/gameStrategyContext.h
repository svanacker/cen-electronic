#ifndef GAME_STRATEGY_CONTEXT_H
#define GAME_STRATEGY_CONTEXT_H

#include "../../common/2d/2d.h"

#include "../../common/timer/cenTimer.h"
#include "gameStrategy.h"
#include "gameTarget.h"
#include "gameTargetAction.h"

#include "teamColor.h"

#include "../../navigation/navigation.h"
#include "../../navigation/location.h"
#include "../../navigation/locationList.h"

#include "../../robot/config/robotConfig.h"

// Forward declaration
struct GameStrategyContext;
typedef struct GameStrategyContext GameStrategyContext;

/**
 * Encapsulates the context of the strategy.
 */
struct GameStrategyContext {
    /** Configuration of the robot. */
    RobotConfig* robotConfig;
    /** Navigation object with the list of loation, paths ...*/
    Navigation* navigation;
    /** Time in seconds since last collision. */
    float timeSinceLastCollision;
    /** The chosen gameStrategy. */
    GameStrategy* gameStrategy;
    /** The elapsedMatchTime in seconds .*/
    float elapsedMatchTime;
    /** Position of robot. */
    Point* robotPosition;
    /** Angle of the robot in degrees. */
    float robotAngle;
    /** The nearestLocation of the robot. */
    Location* nearestLocation;
    // Opponent Robot.
    Point* opponentRobotPosition;
    // Obstacle position.
    Point* lastObstaclePosition;
    /** Flag indicating that the opponent's position has changed. */
    bool opponentRobotMoved;
    /** current Target. */
    GameTarget* currentTarget;
    /** current Target Action. */
    GameTargetAction* currentTargetAction;
    /** TODO : Remove and Use Linked Pointer with current Point : Previously current trajectory of the robot. */
    LocationList* currentTrajectory;
    /** Color. */
    enum TeamColor color;
    /** Go to next Step. */
//    bool mustDoNextStep;
    /** Step status. */
    bool hasMoreNextSteps;
    /** Strategy index. */
    unsigned char strategyIndex;
    /** Max target to handle. */
    unsigned char maxTargetToHandle;
    /** Score*/
    unsigned int score;
    // Strategy timer
    Timer* strategyTimer;
};

/**
 * Initializes the Game Strategy Context.
 */
void initGameStrategyContext(GameStrategyContext* gameStrategyContext,
                             RobotConfig* robotConfig,
                             Navigation* navigation,
                             Timer* strategyTimer,
                             Point* robotPosition,
                             Point* opponentRobotPosition,
                             Point* lastObstaclePosition);


/**
 * Show on all Debug (specifically LCD) which color was chosen.
 */
void showGameStrategyContextTeamColor(GameStrategyContext* gameStrategyContext);

#endif

