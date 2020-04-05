#include "bigRobotStrategy2020.h"

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

#include "../../../robot/2020/commonRobot/commonRobotLocations2020.h"

#include "../../../robot/2020/bigRobot/bigRobotActions2020.h"
#include "../../../robot/2020/bigRobot/bigRobotLocation2020.h"
#include "../../../robot/2020/bigRobot/bigRobotPath2020.h"
#include "../../../robot/2020/bigRobot/bigRobotStrategy2020.h"

#include "../../../robot/2020/navigation/location2020.h"
#include "../../../robot/2020/navigation/path2020.h"
#include "../../../robot/2020/navigation/angle2020.h"

#include "../../../robot/2020/arm/arm2020.h"

#include "../../../robot/2020/strategy/teamColor2020.h"
#include "../../../robot/2020/strategy/strategy2020.h"
#include "../../../robot/2020/strategy/strategy2020Utils.h"
#include "../../../robot/2020/strategy/strategyConfig2020.h"

// TODO : TO REMOVE
#include "../../../robot/2020/smallRobot/smallRobotActions2020.h"

// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points

// Big Robot
static Location* bigRobotStartAreaLocation;
static Location* bigRobotPoint1Location;
static Location* smallHarborFrontMiddleLocation;
static Location* centerPointLocation;
static Location* leftReefFrontLocation;
static Location* dropLeftFrontLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Big Robot
PathData* bigRobotStartArea_to_point1_Path;
PathData* point1_to_smallHarborFrontMiddle_Path;
PathData* smallHarborFrontMiddle_to_centerPoint_Path;
PathData* centerPoint_to_leftReefFront_Path;
PathData* leftReefFront_to_dropLeftFront_Path;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List

static GameTarget smallHarbor1Target;
static GameTarget leftReefTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// Small Harbor 1
static GameTargetAction smallHarbor1PrepareTargetAction;
static GameTargetAction smallHarbor1TakeTargetAction;
static GameTargetAction smallHarbor1DropTargetAction;

// To take Cup from Left Reef
static GameTargetAction leftCupPrepareTargetAction;
static GameTargetAction leftCupTakeTargetAction;
static GameTargetAction leftCupDropTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Big Robot -> Small Harbor 1
static GameTargetActionItemList smallHarbor1PrepareTargetActionItemList;
static GameTargetActionItemList smallHarbor1TakeTargetActionItemList;
static GameTargetActionItemList smallHarbor1DropTargetActionItemList;

// Big Robot -> Left Reef
static GameTargetActionItemList leftCupPrepareTargetActionItemList;
static GameTargetActionItemList leftCupTakeTargetActionItemList;
static GameTargetActionItemList leftCupDropTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

// Big Robot

// -> Small Harbor 1
static GameTargetActionItem smallHarbor1PrepareTargetActionItem;
static GameTargetActionItem smallHarbor1TakeTargetActionItem;
static GameTargetActionItem smallHarbor1DropTargetActionItem;

// -> Cup
static GameTargetActionItem leftCupPrepareTargetActionItem;
static GameTargetActionItem leftCupTakeTargetActionItem;
static GameTargetActionItem leftCupDropTargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

// 
static GameStrategy bigRobotStrategy1;
static GameStrategy bigRobotStrategy2;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

static GameStrategyItem bigRobotSmallHarborStrategyItem;
static GameStrategyItem leftReefStrategyItem;

void initBigRobotLocations2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    bigRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, BIG_ROBOT_START_AREA, BIG_ROBOT_START_AREA_LABEL, BIG_ROBOT_START_AREA_X, BIG_ROBOT_START_AREA_Y);
    bigRobotPoint1Location = addLocationWithColors(teamColor, navigation, BIG_ROBOT_POINT_1, BIG_ROBOT_POINT_1_LABEL, BIG_ROBOT_POINT_1_X, BIG_ROBOT_POINT_1_Y);
    smallHarborFrontMiddleLocation = addLocationWithColors(teamColor, navigation, SMALL_HARBOR_FRONT_MIDDLE, SMALL_HARBOR_FRONT_MIDDLE_LABEL, SMALL_HARBOR_FRONT_MIDDLE_X, SMALL_HARBOR_FRONT_MIDDLE_Y);
    centerPointLocation = addLocationWithColors(teamColor, navigation, CENTER_POINT, CENTER_POINT_LABEL, CENTER_POINT_X, CENTER_POINT_Y);
    leftReefFrontLocation = addLocationWithColors(teamColor, navigation, LEFT_REEF_FRONT, LEFT_REEF_FRONT_LABEL, LEFT_REEF_FRONT_X, LEFT_REEF_FRONT_Y);
    dropLeftFrontLocation = addLocationWithColors(teamColor, navigation, DROP_LEFT_FRONT, DROP_LEFT_FRONT_LABEL, DROP_LEFT_FRONT_X, DROP_LEFT_FRONT_Y);
}

void initBigRobotPaths2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    float aFactor = gameStrategyContext->defaultAccelerationFactor;
    float speedFactor = gameStrategyContext->defaultSpeedFactor;

    // Big Robot
    bigRobotStartArea_to_point1_Path = addNavigationPathWithColor(teamColor,
        navigation,
        bigRobotStartAreaLocation,
        bigRobotPoint1Location,
        BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_COST,
        BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_CP1,
        BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_CP2,
        deciDegreeToRad(BIG_ROBOT_START_AREA_ANGLE_DECI_DEG),
        deciDegreeToRad(BIG_ROBOT_POINT_1_START_ANGLE_DECI_DEG),
        aFactor * BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_SPEED_FACTOR,
        speedFactor * BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_ACC_FACTOR);

    point1_to_smallHarborFrontMiddle_Path = addNavigationPathWithColor(teamColor,
        navigation,
        bigRobotPoint1Location,
        smallHarborFrontMiddleLocation,
        BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_COST,
        BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_CP1,
        BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_CP2,
        deciDegreeToRad(BIG_ROBOT_POINT_1_END_ANGLE_DECI_DEG),
        deciDegreeToRad(SMALL_HARBOR_FRONT_MIDDLE_ANGLE_DECI_DEG),
        speedFactor * BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_SPEED_FACTOR,
        aFactor * BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_ACC_FACTOR
        );

    smallHarborFrontMiddle_to_centerPoint_Path = addNavigationPathWithColor(teamColor,
        navigation,
        smallHarborFrontMiddleLocation,
        centerPointLocation,
        SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_COST,
        SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_CP1,
        SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_CP2,
        deciDegreeToRad(SMALL_HARBOR_FRONT_MIDDLE_ANGLE_DECI_DEG),
        deciDegreeToRad(CENTER_POINT_START_ANGLE_DECI_DEG),
        speedFactor * SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_SPEED_FACTOR,
        aFactor * SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_ACC_FACTOR
        );

    centerPoint_to_leftReefFront_Path = addNavigationPathWithColor(teamColor,
        navigation,
        centerPointLocation,
        leftReefFrontLocation,
        CENTER_POINT__TO__LEFT_REEF_FRONT_COST,
        CENTER_POINT__TO__LEFT_REEF_FRONT_CP1,
        CENTER_POINT__TO__LEFT_REEF_FRONT_CP2,
        deciDegreeToRad(CENTER_POINT_END_ANGLE_DECI_DEG),
        deciDegreeToRad(LEFT_REEF_FRONT_ANGLE_DECI_DEG),
        speedFactor * CENTER_POINT__TO__LEFT_REEF_FRONT_SPEED_FACTOR,
        aFactor * CENTER_POINT__TO__LEFT_REEF_FRONT_ACC_FACTOR
    );

    leftReefFront_to_dropLeftFront_Path = addNavigationPathWithColor(teamColor,
        navigation,
        leftReefFrontLocation,
        dropLeftFrontLocation,
        LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_COST,
        LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_CP1,
        LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_CP2,
        deciDegreeToRad(LEFT_REEF_FRONT_ANGLE_DECI_DEG),
        deciDegreeToRad(DROP_LEFT_FRONT_DECI_DEG),
        speedFactor * LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_SPEED_FACTOR,
        aFactor * LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_ACC_FACTOR
    );
}

void initBigRobotTargets2020(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();
    // TODO : Change Value of gain
    addGameTarget(&smallHarbor1Target, "SMALL_HARB_1", 30, bigRobotStartAreaLocation, smallHarborFrontMiddleLocation);
    addGameTarget(&leftReefTarget, "LEFT_REEF", 10, leftReefFrontLocation, dropLeftFrontLocation);
}

void initBigRobotTargetActions2020(GameStrategyContext* gameStrategyContext) {

    // SmallHarbor1
    // TODO : Change Time
    addTargetPrepareAction(&(smallHarbor1Target.actionList), &smallHarbor1PrepareTargetAction, bigRobotStartAreaLocation, 10, &smallHarbor1PrepareTargetActionItemList);
    addTargetTakeAction(&(smallHarbor1Target.actionList), &smallHarbor1TakeTargetAction, bigRobotPoint1Location, 10, &smallHarbor1TakeTargetActionItemList);
    addTargetDropAction(&(smallHarbor1Target.actionList), &smallHarbor1DropTargetAction, smallHarborFrontMiddleLocation, 10, &smallHarbor1DropTargetActionItemList);

    // LeftReef
    // TODO : Change Time
    addTargetPrepareAction(&(leftReefTarget.actionList), &leftCupPrepareTargetAction, centerPointLocation, 10, &leftCupPrepareTargetActionItemList);
    addTargetTakeAction(&(leftReefTarget.actionList), &leftCupTakeTargetAction, leftReefFrontLocation, 10, &leftCupTakeTargetActionItemList);
    addTargetDropAction(&(leftReefTarget.actionList), &leftCupDropTargetAction, dropLeftFrontLocation, 10, &leftCupDropTargetActionItemList);
}

void initBigRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext) {
    // Small Harbor 1
    // TODO : Replace takeCups by more precise semantic
    addTargetActionItem(&smallHarbor1PrepareTargetActionItemList, &smallHarbor1PrepareTargetActionItem, &bigRobotPrepareFloorCups, "SMALL HARBOR 1 -> PREPARE CUP UP");
    addTargetActionItem(&smallHarbor1TakeTargetActionItemList, &smallHarbor1TakeTargetActionItem, &bigRobotLockFloorCups, "SMALL HARBOR 1 -> LOOK FLOOR CUPS");
    addTargetActionItem(&smallHarbor1DropTargetActionItemList, &smallHarbor1DropTargetActionItem, &bigRobotReleaseCups, "SMALL HARBOR 1 -> DROP CUPS");

    // Left Reef
    addTargetActionItem(&leftCupPrepareTargetActionItemList, &leftCupPrepareTargetActionItem, &smallRobotPrepareHook, "LEFT REEF -> PREPARE CUP UP");
    addTargetActionItem(&leftCupTakeTargetActionItemList, &leftCupTakeTargetActionItem, &smallRobotTakeCups, "LEFT REEF -> TAKE CUPS");
    addTargetActionItem(&leftCupDropTargetActionItemList, &leftCupDropTargetActionItem, &smallRobotDropCups, "LEFT REEF -> DROP CUPS");
}

GameStrategy* initBigRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    else if (strategyId == BIG_ROBOT_STRATEGY_2020_1_SMALL_HARBOR) {
        addGameStrategyItem(&bigRobotStrategy1, &bigRobotSmallHarborStrategyItem, &smallHarbor1Target);
        return &bigRobotStrategy1;
    }
    else if (strategyId == BIG_ROBOT_STRATEGY_2020_2_SMALL_HARBOR_LEFT_REEF) {
        addGameStrategyItem(&bigRobotStrategy2, &bigRobotSmallHarborStrategyItem, &smallHarbor1Target);
        addGameStrategyItem(&bigRobotStrategy2, &leftReefStrategyItem, &leftReefTarget);
        return &bigRobotStrategy2;
    }
    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initBigRobotStrategies2020(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();
    addGameStrategy(&bigRobotStrategy1, BIG_ROBOT_STRATEGY_2020_1_SMALL_HARBOR, "SMALL HARBOR");
    addGameStrategy(&bigRobotStrategy2, BIG_ROBOT_STRATEGY_2020_2_SMALL_HARBOR_LEFT_REEF, "SMALL HARBOR & LEFT REEF");
}
