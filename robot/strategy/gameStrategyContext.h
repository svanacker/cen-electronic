#ifndef GAME_STRATEGY_CONTEXT_H
#define GAME_STRATEGY_CONTEXT_H

#include "../../common/2d/2d.h"
#include "../../common/pwm/servo/servoList.h"
#include "../../common/timer/cenTimer.h"

#include "gameStrategy.h"
#include "gameTarget.h"
#include "gameTargetAction.h"

#include "../../common/timer/cenTimer.h"

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
#define NO_STRATEGY_INDEX                                                      0

// SMALL ROBOT STRATEGY
#define SMALL_ROBOT_STRATEGY_1_ACCELERATOR                                     1
#define SMALL_ROBOT_STRATEGY_2_ACCELERATOR_TAKE_GOLDENIUM                      2
#define SMALL_ROBOT_STRATEGY_3_ACCELERATOR_TAKE_DROP_GOLDENIUM                 3
#define SMALL_ROBOT_STRATEGY_4_ACCELERATOR_TAKE_DROP_GOLDENIUM_SMALL_DIST      4
#define SMALL_ROBOT_STRATEGY_5_ACCELERATOR_CENTER_GOLDENIUM_SMALL_DIST         5


// BIG ROBOT STRATEGY
#define BIG_ROBOT_STRATEGY_1_CHAOS                                             1
#define BIG_ROBOT_STRATEGY_2_BIG_DISTRIBUTOR_LINE_1                            2
#define BIG_ROBOT_STRATEGY_3_BIG_DISTRIBUTOR_LINE_1_2_3                        3
#define BIG_ROBOT_STRATEGY_4_CHAOS_BIG_DISTRIBUTOR_LINE_1_2_3                  4

/**
 * Encapsulates the context of the strategy.
 */
struct GameStrategyContext {
    /** Configuration of the robot. */
    RobotConfig* robotConfig;
    /** Navigation object with the list of location, paths ...*/
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
    /** current Target. */
    GameTarget* currentTarget;
    /** Color. */
    enum TeamColor color;
    /** Strategy Id. If strategy = 0 => NO_STRATEGY. Be careful, strategy Id <> strategy Index in strategy List */
    signed int strategyId;
    // End Match to avoid to do thing without timer
    EndMatch* endMatch;
    /** TofSensorList tof Sensor List */
    TofSensorList* tofSensorList;
    /** Indicates if the robot is moving (to know if we must stop the robot */
    enum TrajectoryType trajectoryType;
    /** Do we simulate move (useful for PC) .*/
    bool simulateMove;
    /** The timer used to decrease the obstacle Cost */
    Timer* obstacleTimer;
    /**. Default acceleration Factor (comes from RobotConfig). */
    float defaultAccelerationFactor;
    /**. Default speed Factor (comes from RobotConfig). */
    float defaultSpeedFactor;
    /** The servo List. */
    ServoList* servoList;
    /** If the game Strategy must automatically loop target and actions .*/
    bool loopTargetAndActions;
    /** If we consider that we must update the position (by timer). */
    bool robotPositionToUpdateInterruptFlag;
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
                             Point* lastObstaclePosition,
                             ServoList* servoList);




/**
 * Show on all Debug (specifically LCD) which color was chosen.
 */
void showGameStrategyContextTeamColorAndStrategy(GameStrategyContext* gameStrategyContext);


#endif

