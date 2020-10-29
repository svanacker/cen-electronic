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
#include "../../../robot/2020/commonRobot/commonRobotActions2020.h"
#include "../../../robot/2020/commonRobot/commonRobotPath2020.h"

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

static Location* centerStartAreaLocation;
static Location* leftReef2FrontLocation;
static Location* leftReef2TakeLocation;
static Location* centerPointLocation;
static Location* dropCenterFrontLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Small Robot
PathData* smallRobotStartArea_to_flag1_Path;
PathData* smallRobotStartArea_to_flag2_Path;
PathData* flag2_to_reefFront_Path;
PathData* reefFront_to_rightCupDropRight_Path;
PathData* rightCupDropRight_to_centerStartArea_Path;
PathData* centerStartArea_to_leftReef2_Path;
PathData* leftReef2Front_to_leftReef2TakePath;
PathData* leftReef2Take_to_centerPoint_Path;
PathData* centerPoint_to_dropCenter_Path;

// ------------------------------------------------------- TARGET -------------------------------------------------------------------------

static GameTarget flag1Target;
static GameTarget flag2Target;
static GameTarget rightCupTarget;
static GameTarget leftReef2Target;

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
static GameTargetAction rightCupRightDropTargetAction;

// To take Cup from Left Reef 2
static GameTargetAction left2CupPrepareTargetAction;
static GameTargetAction left2CupTakeTargetAction;
static GameTargetAction left2CupDropTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Flag
static GameTargetActionItemList flag1PrepareTargetActionItemList;
static GameTargetActionItemList flag1DropTargetActionItemList;
static GameTargetActionItemList flag2PrepareTargetActionItemList;
static GameTargetActionItemList flag2DropTargetActionItemList;

// Cup
static GameTargetActionItemList rightCupPrepareTargetActionItemList;
static GameTargetActionItemList rightCupTakeTargetActionItemList;
static GameTargetActionItemList rightCupRightDropTargetActionItemList;

// Left Reef 2
static GameTargetActionItemList left2CupPrepareTargetActionItemList;
static GameTargetActionItemList left2CupTakeTargetActionItemList;
static GameTargetActionItemList left2CupDropTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEMS  -------------------------------------------------------

// Flag
static GameTargetActionItem flag1PrepareTargetActionItem1;
static GameTargetActionItem flag1PrepareTargetActionItem2;
static GameTargetActionItem flag1DropTargetActionItem1;
static GameTargetActionItem flag2PrepareTargetActionItem1;
static GameTargetActionItem flag2PrepareTargetActionItem2;
static GameTargetActionItem flag2DropTargetActionItem1;

// Cup
static GameTargetActionItem rightCupPrepareTargetActionItem;
static GameTargetActionItem rightCupTakeTargetActionItem;
static GameTargetActionItem rightCupRightDropTargetActionItem;

// -> Cup 2
static GameTargetActionItem left2CupPrepareTargetActionItem;
static GameTargetActionItem left2CupTakeTargetActionItem;
static GameTargetActionItem left2CupDropTargetActionItem1;
static GameTargetActionItem left2CupDropTargetActionItem2;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

// SMALL ROBOT
static GameStrategy smallRobotStrategy1Flag1;
static GameStrategy smallRobotStrategy2Flag2;
static GameStrategy smallRobotStrategy3Flag2Reef;
static GameStrategy smallRobotStrategy4Flag2ReefBoth;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items

// -> Flag
static GameStrategyItem flag1StrategyItem;
static GameStrategyItem flag2StrategyItem;

// -> Cup
static GameStrategyItem rightCupStrategyItem;

// -> Cup Left
static GameStrategyItem leftCup2StrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void initSmallRobotLocations2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    smallRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, SMALL_ROBOT_START_AREA, SMALL_ROBOT_START_AREA_LABEL, SMALL_ROBOT_START_AREA_X, SMALL_ROBOT_START_AREA_Y);
    // FLAG
    flag1Location = addLocationWithColors(teamColor, navigation, FLAG_1_FRONT, FLAG_1_FRONT_LABEL, FLAG_1_FRONT_X, FLAG_1_FRONT_Y);
    flag2Location = addLocationWithColors(teamColor, navigation, FLAG_2_FRONT, FLAG_2_FRONT_LABEL, FLAG_2_FRONT_X, FLAG_2_FRONT_Y);
    // FRONT
    reefFrontLocation = addLocationWithColors(teamColor, navigation, REEF_RIGHT_FRONT, REEF_RIGHT_FRONT_LABEL, REEF_RIGHT_FRONT_X, REEF_RIGHT_FRONT_Y);
    reefFrontLocation->adjustType = LOCATION_ADJUST_Y;
    reefFrontLocation->adjustValue = REEF_RIGHT_FRONT_ADJUST_Y;
    cupDropRightLocation = addLocationWithColors(teamColor, navigation, DROP_RIGHT_FRONT, DROP_RIGHT_FRONT_LABEL, DROP_RIGHT_FRONT_X, DROP_RIGHT_FRONT_Y);
    
    // To Get Reef 2
    centerStartAreaLocation = addLocationWithColors(teamColor, navigation, CENTER_START_AREA, CENTER_START_AREA_LABEL, CENTER_START_AREA_X, CENTER_START_AREA_Y);
    leftReef2FrontLocation = addLocationWithColors(teamColor, navigation, LEFT_REEF_2_FRONT, LEFT_REEF_2_FRONT_LABEL, LEFT_REEF_2_FRONT_X, LEFT_REEF_2_FRONT_Y);
    leftReef2TakeLocation = addLocationWithColors(teamColor, navigation, LEFT_REEF_2_TAKE, LEFT_REEF_2_TAKE_LABEL, LEFT_REEF_2_TAKE_X, LEFT_REEF_2_TAKE_Y);
    leftReef2TakeLocation->adjustType = LOCATION_ADJUST_X;
    leftReef2TakeLocation->adjustValue = LEFT_REEF_2_TAKE_ADJUST_X;
    centerPointLocation = addLocationWithColors(teamColor, navigation, CENTER_POINT, CENTER_POINT_LABEL, CENTER_POINT_X, CENTER_POINT_Y);
    dropCenterFrontLocation = addLocationWithColors(teamColor, navigation, DROP_CENTER_FRONT, DROP_CENTER_FRONT_LABEL, DROP_CENTER_FRONT_X, DROP_CENTER_FRONT_Y);
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
    
    rightCupDropRight_to_centerStartArea_Path  = addNavigationPathWithColor(teamColor,
        navigation,
        cupDropRightLocation,
        centerStartAreaLocation,
        SMALL_ROBOT_DROP_RIGHT_TO_CENTRAL_START_AREA_COST,
        SMALL_ROBOT_DROP_RIGHT_TO_CENTRAL_START_AREA_CP1,
        SMALL_ROBOT_DROP_RIGHT_TO_CENTRAL_START_AREA_CP2,
        deciDegreeToRad(DROP_RIGHT_FRONT_DECI_DEG),
        deciDegreeToRad(CENTER_START_AREA_ANGLE_DECI_DEG),
        aFactor * SMALL_ROBOT_DROP_RIGHT_TO_CENTRAL_START_AREA_SPEED_FACTOR,
        speedFactor * SMALL_ROBOT_DROP_RIGHT_TO_CENTRAL_START_AREA_FRONT_ACC_FACTOR);

    centerStartArea_to_leftReef2_Path  = addNavigationPathWithColor(teamColor,
        navigation,
        centerStartAreaLocation,
        leftReef2FrontLocation,
        SMALL_CENTRAL_START_AREA_TO_LEFT_REEF_2_FRONT_COST,
        SMALL_CENTRAL_START_AREA_TO_LEFT_REEF_2_FRONT_CP1,
        SMALL_CENTRAL_START_AREA_TO_LEFT_REEF_2_FRONT_CP2,
        deciDegreeToRad(LEFT_REEF_2_FRONT_ANGLE_DECI_DEG),
        deciDegreeToRad(LEFT_REEF_2_FRONT_ANGLE_DECI_DEG),
        aFactor * SMALL_CENTRAL_START_AREA_TO_LEFT_REEF_2_FRONT_SPEED_FACTOR,
        speedFactor * SMALL_CENTRAL_START_AREA_TO_LEFT_REEF_2_FRONT_ACC_FACTOR);

    leftReef2Front_to_leftReef2TakePath = addNavigationPathWithColor(teamColor,
        navigation,
        leftReef2FrontLocation,
        leftReef2TakeLocation,
        SMALL_ROBOT_LEFT_REEF_2_FRONT_TO_LEFT_REEF_2_TAKE_COST,
        SMALL_ROBOT_LEFT_REEF_2_FRONT_TO_LEFT_REEF_2_TAKE_CP1,
        SMALL_ROBOT_LEFT_REEF_2_FRONT_TO_LEFT_REEF_2_TAKE_CP2,
        deciDegreeToRad(LEFT_REEF_2_FRONT_ANGLE_DECI_DEG),
        deciDegreeToRad(LEFT_REEF_2_TAKE_ANGLE_DECI_DEG),
        aFactor * SMALL_ROBOT_LEFT_REEF_2_FRONT_TO_LEFT_REEF_2_TAKE_ACC_FACTOR,
        speedFactor * SMALL_ROBOT_LEFT_REEF_2_FRONT_TO_LEFT_REEF_2_TAKE_SPEED_FACTOR);
    /*
    centerStartArea_to_leftReef2_Path = addNavigationPathWithColor(teamColor,
        navigation,
        centerStartAreaLocation,
        leftReef2FrontLocation,
        CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_COST,
        CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_CP1,
        CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_CP2,
        deciDegreeToRad(CENTER_START_AREA_ANGLE_DECI_DEG),
        deciDegreeToRad(LEFT_REEF_2_FRONT_ANGLE_DECI_DEG),
        speedFactor * CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_SPEED_FACTOR,
        aFactor * CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_ACC_FACTOR
    );
    */

    leftReef2Take_to_centerPoint_Path = addNavigationPathWithColor(teamColor,
        navigation,
        leftReef2TakeLocation,
        centerPointLocation,
        LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_COST,
        LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_CP1,
        LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_CP2,
        deciDegreeToRad(LEFT_REEF_2_TAKE_ANGLE_DECI_DEG),
        deciDegreeToRad(CENTER_POINT_END2_ANGLE_DECI_DEG),
        speedFactor * LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_SPEED_FACTOR,
        aFactor * LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_ACC_FACTOR
    );

    centerPoint_to_dropCenter_Path = addNavigationPathWithColor(teamColor,
        navigation,
        centerPointLocation,
        dropCenterFrontLocation,
        CENTRAL_POINT__TO__DROP_CENTER_FRONT_COST,
        CENTRAL_POINT__TO__DROP_CENTER_FRONT_CP1,
        CENTRAL_POINT__TO__DROP_CENTER_FRONT_CP2,
        deciDegreeToRad(CENTER_POINT_END2_ANGLE_DECI_DEG),
        deciDegreeToRad(DROP_CENTER_FRONT_DECI_DEG),
        speedFactor * CENTRAL_POINT__TO__DROP_CENTER_FRONT_SPEED_FACTOR,
        aFactor * CENTRAL_POINT__TO__DROP_CENTER_FRONT_ACC_FACTOR
    );
}

void initSmallRobotTargets2020(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();

    // TODO : SCORE TO MANAGE
    gameStrategyContext->endMatch->scoreToShow += SCORE_POINT_2020_LIGHTHOUSE_OK;
    addGameTarget(&flag1Target, "FLAG1_TARGET", SCORE_POINT_2020_FLAG_1, flag1Location, flag1Location);
    addGameTarget(&flag2Target, "FLAG2_TARGET", SCORE_POINT_2020_FLAG_2, flag2Location, flag2Location);
    addGameTarget(&rightCupTarget, "RIGHT_CUP_TARGET", SCORE_POINT_2020_ALL_RIGHT_CUPS, reefFrontLocation, cupDropRightLocation);
    addGameTarget(&leftReef2Target, "LEFT_REEF2", 10, leftReef2TakeLocation, dropCenterFrontLocation);
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

    // LeftReef 2
    // TODO : Change Time
    addTargetPrepareAction(&(leftReef2Target.actionList), &left2CupPrepareTargetAction, cupDropRightLocation, 10, &left2CupPrepareTargetActionItemList);
    addTargetTakeAction(&(leftReef2Target.actionList), &left2CupTakeTargetAction, leftReef2TakeLocation, 10, &left2CupTakeTargetActionItemList);
    addTargetDropAction(&(leftReef2Target.actionList), &left2CupDropTargetAction, dropCenterFrontLocation, 10, &left2CupDropTargetActionItemList);

}

void initSmallRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext) {
    // Flag 1
    addTargetActionItem(&flag1PrepareTargetActionItemList, &flag1PrepareTargetActionItem1, &lateralArmOn, NULL, "LAT ARM ON");
    addTargetActionItem(&flag1PrepareTargetActionItemList, &flag1PrepareTargetActionItem2, &smallRobotHookUpAll, NULL, "HOOK ALL UP");
    addTargetActionItem(&flag1DropTargetActionItemList, &flag1DropTargetActionItem1, &lateralArmOff, NULL, "LAT ARM OFF");

    // Flag 1 & 2
    addTargetActionItem(&flag2PrepareTargetActionItemList, &flag2PrepareTargetActionItem1, &lateralArmOn, NULL, "LAT ARM ON");
    addTargetActionItem(&flag2PrepareTargetActionItemList, &flag2PrepareTargetActionItem2, &smallRobotHookUpAll, NULL, "HOOK ALL UP");
    addTargetActionItem(&flag2DropTargetActionItemList, &flag2DropTargetActionItem1, &lateralArmOff, NULL, "LAT ARM OFF");

    // RightCup
    addTargetActionItem(&rightCupPrepareTargetActionItemList, &rightCupPrepareTargetActionItem, &smallRobotPrepareHook, NULL, "PREP HOOK");
    addTargetActionItem(&rightCupTakeTargetActionItemList, &rightCupTakeTargetActionItem, &smallRobotTakeCups, &commonAreActionsFinished, "TAKE CUPS");
    addTargetActionItem(&rightCupRightDropTargetActionItemList, &rightCupRightDropTargetActionItem, &smallRobotDropCups, &commonAreActionsFinished, "DROP CUPS RIGHT");
    
    // Left Reef 2
    addTargetActionItem(&left2CupPrepareTargetActionItemList, &left2CupPrepareTargetActionItem, &smallRobotPrepareHook, NULL, "LEFT REEF 2 -> PREP CUP UP");
    addTargetActionItem(&left2CupTakeTargetActionItemList, &left2CupTakeTargetActionItem, &smallRobotTakeCups, &commonAreActionsFinished, "LEFT REEF 2 -> TAKE CUPS");
    addTargetActionItem(&left2CupDropTargetActionItemList, &left2CupDropTargetActionItem1, &smallRobotDropCups, &commonAreActionsFinished, "LEFT REEF 2 -> DROP CUPS");
    addTargetActionItem(&left2CupDropTargetActionItemList, &left2CupDropTargetActionItem2, &smallRobotGoBack, &commonAreActionsFinished, "LEFT REEF 2 -> GO BACK");

}

GameStrategy* initSmallRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2020_1_FLAG_1) {
        addGameStrategyItem(&smallRobotStrategy1Flag1, &flag1StrategyItem, &flag1Target);
        return &smallRobotStrategy1Flag1;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2020_2_FLAG_2) {
        addGameStrategyItem(&smallRobotStrategy2Flag2, &flag2StrategyItem, &flag2Target);
        return &smallRobotStrategy2Flag2;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2020_3_FLAG_2_REEF) {
        addGameStrategyItem(&smallRobotStrategy3Flag2Reef, &flag2StrategyItem, &flag2Target);
        addGameStrategyItem(&smallRobotStrategy3Flag2Reef, &rightCupStrategyItem, &rightCupTarget);
        return &smallRobotStrategy3Flag2Reef;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2020_4_FLAG_2_REEF_BOTH) {
        addGameStrategyItem(&smallRobotStrategy4Flag2ReefBoth, &flag2StrategyItem, &flag2Target);
        addGameStrategyItem(&smallRobotStrategy4Flag2ReefBoth, &rightCupStrategyItem, &rightCupTarget);
        addGameStrategyItem(&smallRobotStrategy4Flag2ReefBoth, &leftCup2StrategyItem, &leftReef2Target);
        return &smallRobotStrategy4Flag2ReefBoth;
    }

    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initSmallRobotStrategies2020(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();

    addGameStrategy(&smallRobotStrategy1Flag1, SMALL_ROBOT_STRATEGY_2020_1_FLAG_1, "FLAG 1");
    addGameStrategy(&smallRobotStrategy2Flag2, SMALL_ROBOT_STRATEGY_2020_2_FLAG_2, "FLAG 2");
    addGameStrategy(&smallRobotStrategy3Flag2Reef, SMALL_ROBOT_STRATEGY_2020_3_FLAG_2_REEF, "FLAG 2 / REEF");
    addGameStrategy(&smallRobotStrategy4Flag2ReefBoth, SMALL_ROBOT_STRATEGY_2020_4_FLAG_2_REEF_BOTH, "FLAG 2 / REEF BOTH");
}