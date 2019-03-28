#include <stdlib.h>

#include "strategy2019.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../drivers/tof/tofList.h"

#include "../../motion/motion.h"
#include "../../motion/simple/simpleMotion.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/pathListDebug.h"
#include "../../navigation/navigation.h"

#include "../../client/motion/position/clientTrajectory.h"

#include "../../robot/config/robotConfig.h"

#include "../../robot/gameboard/gameboard.h"

#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameTargetActionItem.h"
#include "../../robot/strategy/gameTargetActionList.h"

#include "../../robot/tof/strategyTofSensorList.h"

#include "../../robot/2019/teamColor2019.h"
#include "../../robot/2019/strategy2019Utils.h"
#include "../../robot/2019/strategyConfig2019.h"


// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points
static Location* bigRobotStartAreaLocation;
static Location* smallRobotStartAreaLocation;
static Location* acceleratorFrontLocation;
static Location* acceleratorDropLocation;
static Location* goldeniumFrontLocation;
static Location* weighingMachineFrontLocation;
static Location* bigDistributorLine1FrontLocation;
static Location* bigDistributorLine2FrontLocation;
static Location* bigDistributorLine3FrontLocation;


// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Big Robot
PathData* bigRobotStartArea_to_bigDistributorLine1Front;
PathData* bigDistributorLine1Front_to_acceleratorDrop;
PathData* acceleratorDropLocation_to_bigDistributorLine2Front;
PathData* bigDistributorLine2Front_to_acceleratorDrop;
PathData* acceleratorDropLocation_to_bigDistributorLine3Front;
PathData* bigDistributorLine3Front_to_acceleratorDrop;

// Small Robot
PathData* smallRobotStartArea_to_accelerator_Path;
PathData* acceleratorFront_to_goldeniumFront_Path;
PathData* goldeniumFront_to_weighingMachineFront_Path;



// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List
static GameTarget acceleratorTarget;
static GameTarget goldeniumTakeTarget;
static GameTarget goldeniumDropTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

static GameTargetAction acceleratorTargetAction;
static GameTargetAction goldeniumTakeTargetAction;
static GameTargetAction goldeniumDropTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

static GameTargetActionItemList acceleratorTargetActionItemList;
static GameTargetActionItemList goldeniumTakeTargetActionItemList;
static GameTargetActionItemList goldeniumDropTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

static GameTargetActionItem acceleratorTargetActionItem;
static GameTargetActionItem goldeniumTakeTargetActionItem;
static GameTargetActionItem goldeniumDropTargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy
// Puck
static GameStrategy strategy1;
// Accelerator only
static GameStrategy strategy2;
// Accelerator + Goldenium (take + drop)
static GameStrategy strategy3;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items
static GameStrategyItem acceleratorStrategyItem;
static GameStrategyItem takeGoldeniumStrategyItem;
static GameStrategyItem dropGoldeniumStrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void initColorAndStartPosition2019(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);

    // Configure the color so that we could use isViolet after, could NOT be used before !
    if (configValue & CONFIG_COLOR_YELLOW_MASK) {
        gameStrategyContext->color = TEAM_COLOR_2019_YELLOW;
    }
    else {
        gameStrategyContext->color = TEAM_COLOR_2019_VIOLET;
    }
    float angleDeciDegree = ANGLE_DECI_DEG_90;
    enum RobotType robotType = robotConfig->robotType;
    if (robotType == ROBOT_TYPE_BIG) {
        gameStrategyContext->robotPosition->x = BIG_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = BIG_ROBOT_START_AREA_Y;
    }
    else if (robotType == ROBOT_TYPE_SMALL) {
        gameStrategyContext->robotPosition->x = SMALL_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = SMALL_ROBOT_START_AREA_Y;
    }
    // Symetry
	if (isViolet(gameStrategyContext)) {
        angleDeciDegree = -ANGLE_DECI_DEG_90;
        gameStrategyContext->robotPosition->y = GAMEBOARD_HEIGHT - gameStrategyContext->robotPosition->y;
	}
    float angleRadian = deciDegreeToRad(angleDeciDegree);
    gameStrategyContext->robotAngleRadian = angleRadian;
}

Location* addNavigationWithColors(enum TeamColor teamColor, Navigation* navigation, char* name, float x, float y) {
    LocationList* locationList = navigation->locationList;
    if (teamColor == TEAM_COLOR_2019_VIOLET) {
        y = GAMEBOARD_HEIGHT - y;
    }
    Location* result = addNamedLocation(locationList, name, x, y);
    return result;
}

void initLocations2019(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum RobotType robotType = robotConfig->robotType;

    if (robotType == ROBOT_TYPE_BIG) {
        bigRobotStartAreaLocation = addNavigationWithColors(teamColor, navigation, BIG_ROBOT_START_AREA, BIG_ROBOT_START_AREA_X, BIG_ROBOT_START_AREA_Y);
        acceleratorDropLocation = addNavigationWithColors(teamColor, navigation, ACCELERATOR_DROP, ACCELERATOR_DROP_X, ACCELERATOR_DROP_Y);
        bigDistributorLine1FrontLocation = addNavigationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_1, BIG_DISTRIBUTOR_LINE_1_X, BIG_DISTRIBUTOR_LINE_1_Y);
        bigDistributorLine2FrontLocation = addNavigationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_2, BIG_DISTRIBUTOR_LINE_2_X, BIG_DISTRIBUTOR_LINE_2_Y);
        bigDistributorLine3FrontLocation = addNavigationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_3, BIG_DISTRIBUTOR_LINE_3_X, BIG_DISTRIBUTOR_LINE_3_Y);
    }
    else {
        smallRobotStartAreaLocation = addNavigationWithColors(teamColor, navigation, SMALL_ROBOT_START_AREA, SMALL_ROBOT_START_AREA_X, SMALL_ROBOT_START_AREA_Y);
        acceleratorFrontLocation = addNavigationWithColors(teamColor, navigation, ACCELERATOR_FRONT, ACCELERATOR_FRONT_X, ACCELERATOR_FRONT_Y);
        goldeniumFrontLocation = addNavigationWithColors(teamColor, navigation, GOLDENIUM_FRONT, GOLDENIUM_FRONT_X, GOLDENIUM_FRONT_Y);
        weighingMachineFrontLocation = addNavigationWithColors(teamColor, navigation, WEIGHING_MACHINE_FRONT, WEIGHING_MACHINE_X, WEIGHING_MACHINE_Y);
    }
}

// PATHS

PathData* addNavigationPathWithColor(
    enum TeamColor teamColor,
    Navigation* navigation,
    Location* location1,
    Location* location2,
    float cost,
    float controlPointDistance1,
    float controlPointDistance2,
    float angle1,
    float angle2,
    float accelerationFactor,
    float speedFactor) {
    PathData* pathData = addPath(navigation->paths);

    if (teamColor == TEAM_COLOR_2019_VIOLET) {
        angle1 = mod2PI(-angle1);
        angle2 = mod2PI(-angle2);
    }

    initPathData(pathData, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    return pathData;
}

void initPaths2019(GameStrategyContext* gameStrategyContext, int index) {
    Navigation* navigation = gameStrategyContext->navigation;
    
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum TeamColor teamColor = gameStrategyContext->color;
    float aFactor = getAccelerationFactor(robotConfig);
    float speedFactor = getSpeedFactor(robotConfig);

    enum RobotType robotType = robotConfig->robotType;

    if (robotType == ROBOT_TYPE_SMALL) {
        // -> Small Robot
        smallRobotStartArea_to_accelerator_Path = addNavigationPathWithColor(teamColor,
                                                     navigation,
                                                     smallRobotStartAreaLocation, 
                                                     acceleratorFrontLocation,
                                                     SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_COST,
                                                     SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CP1, 
                                                     SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CP2,
                                                     deciDegreeToRad(SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG),
                                                     deciDegreeToRad(ACCELERATOR_FRONT_DECI_DEG),
                                                     aFactor * SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_ACCELERATION_FACTOR,
                                                     speedFactor * SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_SPEED_FACTOR);

        acceleratorFront_to_goldeniumFront_Path = addNavigationPathWithColor(teamColor,
                                                    navigation,
                                                    acceleratorFrontLocation,
                                                    goldeniumFrontLocation,
                                                    ACCELERATOR_TO_GOLDENIUM_COST,
                                                    ACCELERATOR_TO_GOLDENIUM_CP1,
                                                    ACCELERATOR_TO_GOLDENIUM_CP2,
                                                    deciDegreeToRad(ACCELERATOR_FRONT_DECI_DEG),
                                                    deciDegreeToRad(GOLDENIUM_FRONT_ANGLE_DECI_DEG),
                                                    aFactor * GOLDENIUM_TO_WEIGHING_MACHINE_ACCELERATION_FACTOR,
                                                    speedFactor * GOLDENIUM_TO_WEIGHING_MACHINE_SPEED_FACTOR);

        goldeniumFront_to_weighingMachineFront_Path = addNavigationPathWithColor(teamColor,
                                                    navigation,
                                                    goldeniumFrontLocation,
                                                    weighingMachineFrontLocation,
                                                    GOLDENIUM_TO_WEIGHING_MACHINE_COST,
                                                    GOLDENIUM_TO_WEIGHING_MACHINE_CP1,
                                                    GOLDENIUM_TO_WEIGHING_MACHINE_CP2,
                                                    deciDegreeToRad(GOLDENIUM_FRONT_ANGLE_DECI_DEG),
                                                    deciDegreeToRad(WEIGHING_MACHINE_ANGLE_DECI_DEG),
                                                    aFactor * GOLDENIUM_TO_WEIGHING_MACHINE_ACCELERATION_FACTOR,
                                                    speedFactor * GOLDENIUM_TO_WEIGHING_MACHINE_SPEED_FACTOR);
    }
    else if (robotType == ROBOT_TYPE_BIG) {
    // Big Robot
    bigRobotStartArea_to_bigDistributorLine1Front = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                bigRobotStartAreaLocation,
                                                bigDistributorLine1FrontLocation,
                                                BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_COST,
                                                BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_CP1,
                                                BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_CP2,
                                                deciDegreeToRad(BIG_ROBOT_START_AREA_ANGLE_DECI_DEG),
                                                deciDegreeToRad(BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG),
                                                aFactor * BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_ACCELERATION_FACTOR,
                                                speedFactor * BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_SPEED_FACTOR);

    bigDistributorLine1Front_to_acceleratorDrop = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                bigDistributorLine1FrontLocation,
                                                acceleratorDropLocation,
                                                BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_COST,
                                                BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_CP1,
                                                BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_CP2,
                                                deciDegreeToRad(BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG),
                                                deciDegreeToRad(ACCELERATOR_DROP_DECI_DEG),
                                                aFactor * BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR,
                                                speedFactor * BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_SPEED_FACTOR);


    acceleratorDropLocation_to_bigDistributorLine2Front = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                acceleratorDropLocation,
                                                bigDistributorLine2FrontLocation,
                                                ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_COST,
                                                ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_CP1,
                                                ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_CP2,
                                                deciDegreeToRad(ACCELERATOR_DROP_DECI_DEG),
                                                deciDegreeToRad(BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG),
                                                aFactor * ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_ACCELERATION_FACTOR,
                                                speedFactor * ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_SPEED_FACTOR);

    bigDistributorLine2Front_to_acceleratorDrop = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                bigDistributorLine2FrontLocation,
                                                acceleratorDropLocation,
                                                BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_COST,
                                                BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_CP1,
                                                BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_CP2,
                                                deciDegreeToRad(BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG),
                                                deciDegreeToRad(ACCELERATOR_DROP_DECI_DEG),
                                                aFactor * BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR,
                                                speedFactor * BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_SPEED_FACTOR);

    acceleratorDropLocation_to_bigDistributorLine3Front = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                acceleratorDropLocation,
                                                bigDistributorLine2FrontLocation,
                                                ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_COST,
                                                ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_CP1,
                                                ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_CP2,
                                                deciDegreeToRad(ACCELERATOR_DROP_DECI_DEG),
                                                deciDegreeToRad(BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG),
                                                aFactor * ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_ACCELERATION_FACTOR,
                                                speedFactor * ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_SPEED_FACTOR);

    bigDistributorLine3Front_to_acceleratorDrop = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                bigDistributorLine3FrontLocation,
                                                acceleratorDropLocation,
                                                BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_COST,
                                                BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_CP1,
                                                BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_CP2,
                                                deciDegreeToRad(BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG),
                                                deciDegreeToRad(ACCELERATOR_DROP_DECI_DEG),
                                                aFactor * BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR,
                                                speedFactor * BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_SPEED_FACTOR);
    }
}

void initTargets2019(GameStrategyContext* gameStrategyContext) {
	clearGameTargets();

    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum RobotType robotType = robotConfig->robotType;
    if (robotType == ROBOT_TYPE_BIG) {
        // TODO
    }
    else if (robotType == ROBOT_TYPE_SMALL) {
        addGameTarget(&acceleratorTarget, "ACC_TARGET", SCORE_POINT_2019_LAUNCH_BLUIUM_IN_ACCELERATOR, acceleratorFrontLocation);
        addGameTarget(&goldeniumTakeTarget, "GOLD_TAKE_TARGET", SCORE_POINT_2019_EXTRACT_GOLDENIUM, goldeniumFrontLocation);
        addGameTarget(&goldeniumDropTarget, "GOLD_DROP_TARGET", SCORE_POINT_2019_WEIGHING_MACHINE_GOLDENIUM, weighingMachineFrontLocation);
    }
}

void initTargetActions2019(GameStrategyContext* gameStrategyContext) {
    // ACCELERATOR TARGET
    addTargetAction(&(acceleratorTarget.actionList), &acceleratorTargetAction, acceleratorFrontLocation, acceleratorFrontLocation, ACCELERATOR_ACTION_TIME_TO_ACHIEVE, NULL, &acceleratorTargetActionItemList);
    // GOLDENIUM TAKE TARGET
    addTargetAction(&(goldeniumTakeTarget.actionList), &goldeniumTakeTargetAction, goldeniumFrontLocation, goldeniumFrontLocation, GOLDENIUM_TAKE_TIME_TO_ACHIEVE, NULL, &goldeniumTakeTargetActionItemList);
    // GOLDENIUM DROP TARGET
    addTargetAction(&(goldeniumDropTarget.actionList), &goldeniumDropTargetAction, weighingMachineFrontLocation, weighingMachineFrontLocation, GOLDENIUM_DROP_TIME_TO_ACHIEVE, NULL, &goldeniumDropTargetActionItemList);
}

bool acceleratorArmOn(int* context) {
    // TODO
    return true;
}

bool goldeniumTake(int* context) {
    return true;
}

bool goldeniumDrop(int* context) {
    return true;
}

void initTargetActionsItems2019(GameStrategyContext* gameStrategyContext) {
    addTargetActionItem(&acceleratorTargetActionItemList, &acceleratorTargetActionItem, &acceleratorArmOn, "ACC ARM ON");
    addTargetActionItem(&goldeniumTakeTargetActionItemList, &goldeniumTakeTargetActionItem, &goldeniumTake, "GOLD TAKE");
    addTargetActionItem(&goldeniumDropTargetActionItemList, &goldeniumDropTargetActionItem, &goldeniumDrop, "GOLD DROP");
}

/**
* @private.
*/
void initStrategies2019(GameStrategyContext* gameStrategyContext) {
	clearGameStrategies();
	addGameStrategy(&strategy1, "SIMPLE PUCK");
    addGameStrategy(&strategy2, "ACCELERATOR");
    addGameStrategy(&strategy3, "ACC / TAKE GOLD / DROP GOLD");
}

GameStrategy* initStrategiesItems2019(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyIndex = gameStrategyContext->strategyIndex;
    if (strategyIndex == NO_STRATEGY_INDEX) {
        return NULL;
    }
    else if (strategyIndex == STRATEGY_1_SIMPLE_PUCK) {
        // TODO
        return &strategy1;
    }
    else if (strategyIndex == STRATEGY_2_ACCELERATOR) {
        addGameStrategyItem(&strategy2, &acceleratorStrategyItem, &acceleratorTarget);
        return &strategy2;
    }
    else if (strategyIndex == STRATEGY_3_ACCELERATOR_GOLDENIUM) {
        addGameStrategyItem(&strategy3, &acceleratorStrategyItem, &acceleratorTarget);
        addGameStrategyItem(&strategy3, &takeGoldeniumStrategyItem, &goldeniumTakeTarget);
        addGameStrategyItem(&strategy3, &dropGoldeniumStrategyItem, &goldeniumDropTarget);
        return &strategy3;
    }
    return NULL;
}

void initStrategy2019(GameStrategyContext* gameStrategyContext) {
    initColorAndStartPosition2019(gameStrategyContext);
    float tofDistanceFactor = getSonarDistanceCheckFactor(gameStrategyContext->robotConfig);
    setTofListOrientationAngle(gameStrategyContext->tofSensorList, tofDistanceFactor);
    showGameStrategyContextTeamColorAndStrategy(gameStrategyContext);

	initLocations2019(gameStrategyContext);
	initPaths2019(gameStrategyContext, gameStrategyContext->strategyIndex);

	initTargets2019(gameStrategyContext);
	initTargetActions2019(gameStrategyContext);
	initTargetActionsItems2019(gameStrategyContext);

	initStrategies2019(gameStrategyContext);
	

	GameStrategy* strategy = initStrategiesItems2019(gameStrategyContext);
    gameStrategyContext->gameStrategy = strategy;
    gameStrategyContext->maxTargetToHandle = getGameTargetList()->size;

	// opponent
	Point* p = gameStrategyContext->opponentRobotPosition;
	p->x = 0;
	p->y = 0;

	// obstacle
	p = gameStrategyContext->lastObstaclePosition;
	p->x = 0;
	p->y = 0;

    gameStrategyContext->hasMoreNextSteps = true;

	// reinitialize the game board to change elements / targets ...
}
