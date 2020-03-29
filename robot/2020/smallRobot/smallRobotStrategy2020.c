#include "smallRobotStrategy2020.h"

#include <stdlib.h>

#include "../strategy/strategy2020.h"

#include "../../../common/error/error.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../common/pwm/servo/servoList.h"

#include "../../../drivers/tof/tofList.h"

#include "../../../motion/motion.h"
#include "../../../motion/simple/simpleMotion.h"
#include "../../../motion/extended/bsplineMotion.h"

#include "../../../navigation/locationList.h"
#include "../../../navigation/path.h"
#include "../../../navigation/pathList.h"
#include "../../../navigation/pathListDebug.h"
#include "../../../navigation/navigation.h"

#include "../../../client/motion/position/clientTrajectory.h"

#include "../../../robot/config/robotConfig.h"

#include "../../../robot/gameboard/gameboard.h"

#include "../../../robot/strategy/gameStrategy.h"
#include "../../../robot/strategy/gameStrategyHandler.h"
#include "../../../robot/strategy/gameStrategyList.h"
#include "../../../robot/strategy/gameTargetList.h"
#include "../../../robot/strategy/gameTarget.h"
#include "../../../robot/strategy/gameTargetAction.h"
#include "../../../robot/strategy/gameTargetActionItem.h"
#include "../../../robot/strategy/gameTargetActionList.h"

#include "../../../robot/tof/strategyTofSensorList.h"

#include "../../../robot/2020/arm/arm2020.h"

#include "../../../robot/2020/navigation/angle2020.h"
#include "../../../robot/2020/navigation/location2020.h"
#include "../../../robot/2020/navigation/path2020.h"

#include "../../../robot/2020/commonRobot/commonRobotLocations2020.h"

#include "../../../robot/2020/smallRobot/smallRobotActions2020.h"
#include "../../../robot/2020/smallRobot/smallRobotLocation2020.h"
#include "../../../robot/2020/smallRobot/smallRobotPath2020.h"
#include "../../../robot/2020/smallRobot/smallRobotStrategy2020.h"

#include "../../../robot/2020/strategy/strategy2020Utils.h"
#include "../../../robot/2020/strategy/strategyConfig2020.h"
#include "../../../robot/2020/strategy/teamColor2020.h"

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------

static Location* smallRobotStartAreaLocation;
static Location* flag1Location;
static Location* flag2Location;
static Location* reefFrontLocation;
static Location* cupDropRightLocation;
static Location* cupDropLeftLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Small Robot
PathData* smallRobotStartArea_to_flag1_Path;
PathData* smallRobotStartArea_to_flag2_Path;
PathData* flag2_to_reefFront_Path;
PathData* reefFront_to_rightCupDropRight_Path;
PathData* rightCupLeftDrop_to_rightCupDropLeft_Path;

// ------------------------------------------------------- TARGET -------------------------------------------------------------------------

static GameTarget flag1Target;
static GameTarget flag2Target;
static GameTarget rightCupTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// Flag 1
static GameTargetAction flag1PrepareTargetAction;
static GameTargetAction flag1DropTargetAction;

// Flag 2
static GameTargetAction flag2PrepareTargetAction;
static GameTargetAction flag2DropTargetAction;

// Right Cup
static GameTargetAction rightCupPrepareTargetAction;
static GameTargetAction rightCupTakeTargetAction;
static GameTargetAction rightCupLeftDropTargetAction;
static GameTargetAction rightCupRightDropTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Flag
static GameTargetActionItemList flag1PrepareTargetActionItemList;
static GameTargetActionItemList flag1DropTargetActionItemList;
static GameTargetActionItemList flag2PrepareTargetActionItemList;
static GameTargetActionItemList flag2DropTargetActionItemList;

// Cup
static GameTargetActionItemList rightCupPrepareTargetActionItemList;
static GameTargetActionItemList rightCupTakeTargetActionItemList;
static GameTargetActionItemList rightCupLeftDropTargetActionItemList;
static GameTargetActionItemList rightCupRightDropTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEMS  -------------------------------------------------------

// Flag
static GameTargetActionItem flag1PrepareTargetActionItem1;
static GameTargetActionItem flag1DropTargetActionItem1;
static GameTargetActionItem flag2PrepareTargetActionItem1;
static GameTargetActionItem flag2DropTargetActionItem1;

// Cup
static GameTargetActionItem rightCupPrepareTargetActionItem;
static GameTargetActionItem rightCupTakeTargetActionItem;
static GameTargetActionItem rightCupLeftDropTargetActionItem;
static GameTargetActionItem rightCupRightDropTargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

// SMALL ROBOT
static GameStrategy smallRobotStrategyFlag1;
static GameStrategy smallRobotStrategyFlag2;
static GameStrategy smallRobotStrategyFlag2Reef;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items

// -> Flag
static GameStrategyItem flag1StrategyItem;
static GameStrategyItem flag2StrategyItem;

// -> Cup
static GameStrategyItem rightCupStrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void initSmallRobotLocations2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    smallRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, SMALL_ROBOT_START_AREA, SMALL_ROBOT_START_AREA_LABEL, SMALL_ROBOT_START_AREA_X, SMALL_ROBOT_START_AREA_Y);
    flag1Location = addLocationWithColors(teamColor, navigation, FLAG_1_FRONT, FLAG_1_FRONT_LABEL, FLAG_1_FRONT_X, FLAG_1_FRONT_Y);
    flag2Location = addLocationWithColors(teamColor, navigation, FLAG_2_FRONT, FLAG_2_FRONT_LABEL, FLAG_2_FRONT_X, FLAG_2_FRONT_Y);
    reefFrontLocation = addLocationWithColors(teamColor, navigation, REEF_RIGHT_FRONT, REEF_RIGHT_FRONT_LABEL, REEF_RIGHT_FRONT_X, REEF_RIGHT_FRONT_Y);
    cupDropRightLocation = addLocationWithColors(teamColor, navigation, DROP_RIGHT_FRONT, DROP_RIGHT_FRONT_LABEL, DROP_RIGHT_FRONT_X, DROP_RIGHT_FRONT_Y);
    cupDropLeftLocation = addLocationWithColors(teamColor, navigation, DROP_LEFT_FRONT, DROP_LEFT_FRONT_LABEL, DROP_LEFT_FRONT_X, DROP_LEFT_FRONT_Y);
}

void initSmallRobotPaths2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;
    float aFactor = gameStrategyContext->defaultAccelerationFactor;
    float speedFactor = gameStrategyContext->defaultSpeedFactor;

    smallRobotStartArea_to_flag1_Path = addNavigationPathWithColor(teamColor,
        navigation,
        smallRobotStartAreaLocation,
        flag1Location,
        SMALL_ROBOT_STARTAREA_TO_FLAG_1_COST,
        SMALL_ROBOT_STARTAREA_TO_FLAG_1_CP1,
        SMALL_ROBOT_STARTAREA_TO_FLAG_1_CP2,
        deciDegreeToRad(SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG),
        deciDegreeToRad(FLAG_1_FRONT_DECI_DEG),
        aFactor * SMALL_ROBOT_STARTAREA_TO_FLAG_1_ACC_FACTOR,
        speedFactor * SMALL_ROBOT_STARTAREA_TO_FLAG_1_SPEED_FACTOR);

    smallRobotStartArea_to_flag2_Path = addNavigationPathWithColor(teamColor,
        navigation,
        smallRobotStartAreaLocation,
        flag2Location,
        SMALL_ROBOT_STARTAREA_TO_FLAG_2_COST,
        SMALL_ROBOT_STARTAREA_TO_FLAG_2_CP1,
        SMALL_ROBOT_STARTAREA_TO_FLAG_2_CP2,
        deciDegreeToRad(SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG),
        deciDegreeToRad(FLAG_2_FRONT_DECI_DEG),
        aFactor * SMALL_ROBOT_STARTAREA_TO_FLAG_2_ACC_FACTOR,
        speedFactor * SMALL_ROBOT_STARTAREA_TO_FLAG_2_SPEED_FACTOR);

    flag2_to_reefFront_Path = addNavigationPathWithColor(teamColor,
        navigation,
        flag2Location,
        reefFrontLocation,
        SMALL_ROBOT_FLAG_2_TO_REEF_FRONT_COST,
        SMALL_ROBOT_FLAG_2_TO_REEF_FRONT_CP1,
        SMALL_ROBOT_FLAG_2_TO_REEF_FRONT_CP2,
        deciDegreeToRad(FLAG_2_FRONT_DECI_DEG),
        deciDegreeToRad(REEF_RIGHT_FRONT_DECI_DEG),
        aFactor * SMALL_ROBOT_FLAG_2_TO_REEF_FRONT_ACC_FACTOR,
        speedFactor * SMALL_ROBOT_FLAG_2_TO_REEF_FRONT_SPEED_FACTOR);

    reefFront_to_rightCupDropRight_Path = addNavigationPathWithColor(teamColor,
        navigation,
        reefFrontLocation,
        cupDropRightLocation,
        SMALL_ROBOT_REEF_FRONT_TO_DROP_RIGHT_FRONT_COST,
        SMALL_ROBOT_REEF_FRONT_TO_DROP_RIGHT_FRONT_CP1,
        SMALL_ROBOT_REEF_FRONT_TO_DROP_RIGHT_FRONT_CP2,
        deciDegreeToRad(REEF_RIGHT_FRONT_DECI_DEG),
        deciDegreeToRad(DROP_RIGHT_FRONT_DECI_DEG),
        aFactor * SMALL_ROBOT_REEF_FRONT_TO_DROP_RIGHT_FRONT_ACC_FACTOR,
        speedFactor * SMALL_ROBOT_REEF_FRONT_TO_DROP_RIGHT_FRONT_SPEED_FACTOR);
}

void initSmallRobotTargets2020(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();

    // TODO : SCORE TO MANAGE
    gameStrategyContext->endMatch->scoreToShow += SCORE_POINT_2020_LIGHTHOUSE_OK;
    addGameTarget(&flag1Target, "FLAG1_TARGET", SCORE_POINT_2020_FLAG_1, flag1Location, flag1Location);
    addGameTarget(&flag2Target, "FLAG2_TARGET", SCORE_POINT_2020_FLAG_2, flag2Location, flag2Location);
    addGameTarget(&rightCupTarget, "RIGHT_CUP_TARGET", SCORE_POINT_2020_ALL_RIGHT_CUPS, reefFrontLocation, cupDropRightLocation);
}

void initSmallRobotTargetActions2020(GameStrategyContext* gameStrategyContext) {
    // FLAG 1 TARGET
    addTargetPrepareAction(&(flag1Target.actionList), &flag1PrepareTargetAction, smallRobotStartAreaLocation, FLAG1_ARM_ON_ACTION_TIME_TO_ACHIEVE, &flag1PrepareTargetActionItemList);
    addTargetDropAction(&(flag1Target.actionList), &flag1DropTargetAction, flag1Location, FLAG1_ARM_OFF_ACTION_TIME_TO_ACHIEVE, &flag1DropTargetActionItemList);

    // FLAG 2 TARGET
    addTargetPrepareAction(&(flag2Target.actionList), &flag2PrepareTargetAction, smallRobotStartAreaLocation, FLAG2_ARM_ON_ACTION_TIME_TO_ACHIEVE, &flag2PrepareTargetActionItemList);
    addTargetDropAction(&(flag2Target.actionList), &flag2DropTargetAction, flag2Location, FLAG2_ARM_OFF_ACTION_TIME_TO_ACHIEVE, &flag2DropTargetActionItemList);

    // RIGHT CUP TARGET
    addTargetPrepareAction(&(rightCupTarget.actionList), &rightCupPrepareTargetAction, flag2Location, RIGHT_CUP_PREPARE_ACTION_TIME_TO_ACHIEVE, &rightCupPrepareTargetActionItemList);
    addTargetTakeAction(&(rightCupTarget.actionList), &rightCupTakeTargetAction, reefFrontLocation, RIGHT_CUP_TAKE_ACTION_TIME_TO_ACHIEVE, &rightCupTakeTargetActionItemList);
    addTargetDropAction(&(rightCupTarget.actionList), &rightCupRightDropTargetAction, cupDropRightLocation, RIGHT_CUP_RIGHT_DROP_ACTION_TIME_TO_ACHIEVE, &rightCupRightDropTargetActionItemList);
    // addTargetDropAction(&(rightCupTarget.actionList), &rightCupLeftDropTargetAction, cupDropLeftLocation, RIGHT_CUP_LEFT_DROP_ACTION_TIME_TO_ACHIEVE, &rightCupLeftDropTargetActionItemList);
}

void initSmallRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext) {
    // Flag 1
    addTargetActionItem(&flag1PrepareTargetActionItemList, &flag1PrepareTargetActionItem1, &lateralArmOn, "LAT ARM ON");
    addTargetActionItem(&flag1DropTargetActionItemList, &flag1DropTargetActionItem1, &lateralArmOff, "LAT ARM OFF");

    // Flag 1 & 2
    addTargetActionItem(&flag2PrepareTargetActionItemList, &flag2PrepareTargetActionItem1, &lateralArmOn, "LAT ARM ON");
    addTargetActionItem(&flag2DropTargetActionItemList, &flag2DropTargetActionItem1, &lateralArmOff, "LAT ARM OFF");

    // RightCup
    addTargetActionItem(&rightCupPrepareTargetActionItemList, &rightCupPrepareTargetActionItem, &prepareHook, "PREP HOOK");
    addTargetActionItem(&rightCupTakeTargetActionItemList, &rightCupTakeTargetActionItem, &takeCups, "TAKE CUPS");
    addTargetActionItem(&rightCupRightDropTargetActionItemList, &rightCupRightDropTargetActionItem, &dropCups, "DROP CUPS RIGHT");
    // addTargetActionItem(&rightCupLeftDropTargetActionItemList, &rightCupLeftDropTargetActionItem, &dropCups, "DROP CUPS LEFT");
}

GameStrategy* initSmallRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2020_1_FLAG_1) {
        addGameStrategyItem(&smallRobotStrategyFlag1, &flag1StrategyItem, &flag1Target);
        return &smallRobotStrategyFlag1;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2020_2_FLAG_2) {
        addGameStrategyItem(&smallRobotStrategyFlag2, &flag2StrategyItem, &flag2Target);
        return &smallRobotStrategyFlag2;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2020_3_FLAG_2_REEF) {
        addGameStrategyItem(&smallRobotStrategyFlag2Reef, &flag2StrategyItem, &flag2Target);
        addGameStrategyItem(&smallRobotStrategyFlag2Reef, &rightCupStrategyItem, &rightCupTarget);
        return &smallRobotStrategyFlag2Reef;
    }

    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initSmallRobotStrategies2020(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();

    addGameStrategy(&smallRobotStrategyFlag1, SMALL_ROBOT_STRATEGY_2020_1_FLAG_1, "FLAG 1");
    addGameStrategy(&smallRobotStrategyFlag2, SMALL_ROBOT_STRATEGY_2020_2_FLAG_2, "FLAG 2");
    addGameStrategy(&smallRobotStrategyFlag2Reef, SMALL_ROBOT_STRATEGY_2020_3_FLAG_2_REEF, "FLAG 2 / REEF");
}