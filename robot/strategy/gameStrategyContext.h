#ifndef GAME_STRATEGY_CONTEXT_H
#define GAME_STRATEGY_CONTEXT_H

#include "../../common/2d/2d.h"

#include "../../common/timer/cenTimer.h"
#include "gameStrategy.h"
#include "gameTarget.h"
#include "gameTargetAction.h"

#include "teamColor.h"

#include "../../drivers/tof/tofList.h"

#include "../../navigation/navigation.h"
#include "../../navigation/location.h"
#include "../../navigation/locationList.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/match/endMatch.h"

#include "../../motion/position/trajectoryType.h"

// Forward declaration
struct GameStrategyContext;
typedef struct GameStrategyContext GameStrategyContext;

// Index if no Strategy
#define NO_STRATEGY_INDEX                                                        0
#define STRATEGY_1_SIMPLE_PUCK                                                   1
#define STRATEGY_2_ACCELERATOR                                                   2
#define STRATEGY_3_ACCELERATOR_GOLDENIUM                                         3

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
    /** Position of robot. */
    Point* robotPosition;
    /** Angle of the robot in radians. */
    float robotAngleRadian;
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
    /** Strategy index. If strategy = -1 => NO_STRATEGY */
    signed int strategyIndex;
    /** Max target to handle. */
    unsigned char maxTargetToHandle;
    /** Score*/
    unsigned int score;
    // End Match to avoid to do thing without timer
    EndMatch* endMatch;
    /** TofSensorList tof Sensor List */
    TofSensorList* tofSensorList;
    /** Indicates if the robot is moving (to know if we must stop the robot */
    enum TrajectoryType trajectoryType;
    /** dummy Counter*/
    unsigned instructionCounter;
};

/**
 * Initializes the Game Strategy Context.
 */
void initGameStrategyContext(GameStrategyContext* gameStrategyContext,
                             RobotConfig* robotConfig,
                             Navigation* navigation,
                             EndMatch* endMatch,
                             TofSensorList* tofSensorList,
                             Point* robotPosition,
                             Point* opponentRobotPosition,
                             Point* lastObstaclePosition);


/**
 * Show on all Debug (specifically LCD) which color was chosen.
 */
void showGameStrategyContextTeamColorAndStrategy(GameStrategyContext* gameStrategyContext);


#endif

