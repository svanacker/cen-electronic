#include "bigRobotStrategy2019.h"

#include "../strategy/strategy2019.h"
#include "../fork/fork2019.h"

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

#include "../../../robot/2019/bigRobot/bigRobotActions2019.h"
#include "../../../robot/2019/bigRobot/bigRobotLocation2019.h"
#include "../../../robot/2019/bigRobot/bigRobotPath2019.h"
#include "../../../robot/2019/bigRobot/bigRobotStrategy2019.h"

#include "../../../robot/2019/fork/forkDevice2019.h"

#include "../../../robot/2019/navigation/location2019.h"
#include "../../../robot/2019/navigation/path2019.h"
#include "../../../robot/2019/navigation/angle2019.h"

#include "../../../robot/2019/strategy/teamColor2019.h"
#include "../../../robot/2019/strategy/strategy2019.h"
#include "../../../robot/2019/strategy/strategy2019Utils.h"
#include "../../../robot/2019/strategy/strategyConfig2019.h"

// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points

// Big Robot
static Location* bigRobotStartAreaLocation;
static Location* chaosFrontLocation;
static Location* rediumDropZoneLocation;
static Location* keyPoint1Location;
static Location* keyPoint2Location;
static Location* acceleratorDropLocation;
static Location* bigDistributorLine1FrontLocation;
static Location* bigDistributorLine2FrontLocation;
static Location* bigDistributorLine3FrontLocation;


// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Big Robot
PathData* bigRobotStartArea_to_bigDistributorLine1Front;
PathData* bigRobotStartArea_to_chaosZoneFront;
PathData* chaosZoneFront_to_rediumDropZone;
PathData* rediumDropZone_to_keyPoint1;
PathData* rediumDropZone_to_keyPoint2;
PathData* keyPoint2_to_bigDistributorLine1Front;

// Big Distributor & Keypoint1
PathData* bigDistributorLine1Front_to_keyPoint1;
PathData* keyPoint1_to_acceleratorDrop;
PathData* acceleratorDrop_to_keyPoint1;
PathData* keyPoint1_to_bigDistributorLine2Front;
PathData* bigDistributorLine2Front_to_keyPoint1;
PathData* keyPoint1_to_bigDistributorLine3Front;
PathData* bigDistributorLine3Front_to_keyPoint1;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List

static GameTarget chaosTarget;
static GameTarget bigDistributorLine1Target;
static GameTarget bigDistributorLine2Target;
static GameTarget bigDistributorLine3Target;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

static GameTargetAction chaosTakeTargetAction;
static GameTargetAction chaosDropTargetAction;

static GameTargetAction bigDistributorLine1PrepareTakeTargetAction;
static GameTargetAction bigDistributorLine1TakeTargetAction;
static GameTargetAction bigDistributorLine1DropTargetAction;

static GameTargetAction bigDistributorLine2PrepareTakeTargetAction;
static GameTargetAction bigDistributorLine2TakeTargetAction;
static GameTargetAction bigDistributorLine2DropTargetAction;

static GameTargetAction bigDistributorLine3PrepareTakeTargetAction;
static GameTargetAction bigDistributorLine3TakeTargetAction;
static GameTargetAction bigDistributorLine3DropTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Big Robot
static GameTargetActionItemList chaosTakeTargetActionItemList;
static GameTargetActionItemList chaosDropTargetActionItemList;

static GameTargetActionItemList bigDistributorLine1PrepareTakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine1TakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine1DropTargetActionItemList;

static GameTargetActionItemList bigDistributorLine2PrepareTakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine2TakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine2DropTargetActionItemList;

static GameTargetActionItemList bigDistributorLine3PrepareTakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine3TakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine3DropTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

// Big Robot
static GameTargetActionItem bigDistributorLine1PrepareTargetActionItem;
static GameTargetActionItem bigDistributorLine1TakeTargetActionItem;
static GameTargetActionItem bigDistributorLine1DropTargetActionItem;

static GameTargetActionItem bigDistributorLine2PrepareTargetActionItem;
static GameTargetActionItem bigDistributorLine2TakeTargetActionItem;
static GameTargetActionItem bigDistributorLine2DropTargetActionItem;

static GameTargetActionItem bigDistributorLine3PrepareTargetActionItem;
static GameTargetActionItem bigDistributorLine3TakeTargetActionItem;
static GameTargetActionItem bigDistributorLine3DropTargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

static GameStrategy bigRobotStrategy1Chaos;
static GameStrategy bigRobotStrategy2BigDistributorLine1;
static GameStrategy bigRobotStrategy3BigDistributorLine123;
static GameStrategy bigRobotStrategy4ChaosBigDistributorLine123;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

static GameStrategyItem chaosStrategyItem;
static GameStrategyItem bigDistributorLine1StrategyItem;
static GameStrategyItem bigDistributorLine2StrategyItem;
static GameStrategyItem bigDistributorLine3StrategyItem;

void initBigRobotLocations2019(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    bigRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, BIG_ROBOT_START_AREA, BIG_ROBOT_START_AREA_LABEL, BIG_ROBOT_START_AREA_X, BIG_ROBOT_START_AREA_Y);
    chaosFrontLocation = addLocationWithColors(teamColor, navigation, CHAOS_ZONE_FRONT, CHAOS_ZONE_FRONT_LABEL, CHAOS_ZONE_FRONT_X, CHAOS_ZONE_FRONT_Y);
    rediumDropZoneLocation = addLocationWithColors(teamColor, navigation, REDIUM_DROP_ZONE, REDIUM_DROP_ZONE_LABEL, REDIUM_DROP_ZONE_X, REDIUM_DROP_ZONE_Y);
    acceleratorDropLocation = addLocationWithColors(teamColor, navigation, ACCELERATOR_DROP, ACCELERATOR_DROP_LABEL, ACCELERATOR_DROP_X, ACCELERATOR_DROP_Y);

    keyPoint1Location = addLocationWithColors(teamColor, navigation, KEY_POINT_1, KEY_POINT_1_LABEL, KEY_POINT_1_X, KEY_POINT_1_Y);
    keyPoint2Location = addLocationWithColors(teamColor, navigation, KEY_POINT_2, KEY_POINT_2_LABEL, KEY_POINT_2_X, KEY_POINT_2_Y);
    bigDistributorLine1FrontLocation = addLocationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_1, BIG_DISTRIBUTOR_LINE_1_LABEL,  BIG_DISTRIBUTOR_LINE_1_X, BIG_DISTRIBUTOR_LINE_1_Y);
    bigDistributorLine2FrontLocation = addLocationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_2, BIG_DISTRIBUTOR_LINE_2_LABEL, BIG_DISTRIBUTOR_LINE_2_X, BIG_DISTRIBUTOR_LINE_2_Y);
    bigDistributorLine3FrontLocation = addLocationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_3, BIG_DISTRIBUTOR_LINE_3_LABEL, BIG_DISTRIBUTOR_LINE_3_X, BIG_DISTRIBUTOR_LINE_3_Y);

}

void initBigRobotPaths2019(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    float aFactor = gameStrategyContext->defaultAccelerationFactor;
    float speedFactor = gameStrategyContext->defaultSpeedFactor;

    // Big Robot
    bigRobotStartArea_to_bigDistributorLine1Front = addNavigationPathWithColor(teamColor,
        navigation,
        bigRobotStartAreaLocation,
        bigDistributorLine1FrontLocation,
        BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_COST,
        BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP1,
        BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP2,
        deciDegreeToRad(BIG_ROBOT_START_AREA_ANGLE_DECI_DEG),
        deciDegreeToRad(BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG),
        aFactor * BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_ACCELERATION_FACTOR,
        speedFactor * BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_SPEED_FACTOR);

    bigRobotStartArea_to_chaosZoneFront = addNavigationPathWithColor(teamColor,
        navigation,
        bigRobotStartAreaLocation,
        chaosFrontLocation,
        BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_COST,
        BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_CP1,
        BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_CP2,
        deciDegreeToRad(BIG_ROBOT_START_AREA_ANGLE_DECI_DEG),
        deciDegreeToRad(CHAOS_ZONE_FRONT_ANGLE_DECI_DEG),
        aFactor * BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_ACCELERATION_FACTOR,
        speedFactor * BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_SPEED_FACTOR);

    chaosZoneFront_to_rediumDropZone = addNavigationPathWithColor(teamColor,
        navigation,
        chaosFrontLocation,
        rediumDropZoneLocation,
        CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_COST,
        CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_CP1,
        CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_CP2,
        deciDegreeToRad(CHAOS_ZONE_FRONT_ANGLE_DECI_DEG),
        deciDegreeToRad(REDIUM_DROP_ZONE_ANGLE_DECI_DEG),
        aFactor * CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_ACCELERATION_FACTOR,
        speedFactor * CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_SPEED_FACTOR);

    rediumDropZone_to_keyPoint1 = addNavigationPathWithColor(teamColor,
        navigation,
        rediumDropZoneLocation,
        keyPoint1Location,
        REDIUM_DROP_ZONE_TO_KEY_POINT_1_COST,
        REDIUM_DROP_ZONE_TO_KEY_POINT_1_CP1,
        REDIUM_DROP_ZONE_TO_KEY_POINT_1_CP2,
        deciDegreeToRad(REDIUM_DROP_ZONE_ANGLE_DECI_DEG),
        deciDegreeToRad(KEY_POINT_1_FROM_REDIUM_DROP_ZONE_ANGLE_DECI_DEG),
        aFactor * REDIUM_DROP_ZONE_TO_KEY_POINT_1_ACCELERATION_FACTOR,
        speedFactor * REDIUM_DROP_ZONE_TO_KEY_POINT_1_SPEED_FACTOR);

    rediumDropZone_to_keyPoint2 = addNavigationPathWithColor(teamColor,
        navigation,
        rediumDropZoneLocation,
        keyPoint2Location,
        REDIUM_DROP_ZONE_TO_KEY_POINT_2_COST,
        REDIUM_DROP_ZONE_TO_KEY_POINT_2_CP1,
        REDIUM_DROP_ZONE_TO_KEY_POINT_2_CP2,
        deciDegreeToRad(REDIUM_DROP_ZONE_ANGLE_DECI_DEG),
        deciDegreeToRad(KEY_POINT_2_ANGLE_DECI_DEG),
        aFactor * REDIUM_DROP_ZONE_TO_KEY_POINT_2_ACCELERATION_FACTOR,
        speedFactor * REDIUM_DROP_ZONE_TO_KEY_POINT_2_SPEED_FACTOR);

    keyPoint2_to_bigDistributorLine1Front = addNavigationPathWithColor(teamColor,
        navigation,
        keyPoint2Location,
        bigDistributorLine2FrontLocation,
        KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_COST,
        KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP1,
        KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP2,
        deciDegreeToRad(KEY_POINT_2_TO_DISTRIBUTOR_ANGLE_DECI_DEG),
        deciDegreeToRad(BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG),
        aFactor * KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_ACCELERATION_FACTOR,
        speedFactor * KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_SPEED_FACTOR);


    bigDistributorLine1Front_to_keyPoint1 = addNavigationPathWithColor(teamColor,
        navigation,
        bigDistributorLine1FrontLocation,
        keyPoint1Location,
        BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_COST,
        BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_CP1,
        BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_CP2,
        deciDegreeToRad(BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG),
        deciDegreeToRad(KEY_POINT_1_FROM_DISTRIBUTOR_ANGLE_DECI_DEG),
        aFactor * BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR,
        speedFactor * BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_SPEED_FACTOR);

    keyPoint1_to_acceleratorDrop = addNavigationPathWithColor(teamColor,
        navigation,
        keyPoint1Location,
        acceleratorDropLocation,
        KEY_POINT_1_TO_ACCELERATOR_DROP_COST,
        KEY_POINT_1_TO_ACCELERATOR_DROP_CP1,
        KEY_POINT_1_TO_ACCELERATOR_DROP_CP2,
        deciDegreeToRad(KEY_POINT_1_TO_ACCERATOR_ANGLE_DECI_DEG),
        deciDegreeToRad(ACCELERATOR_DROP_DECI_DEG),
        aFactor * KEY_POINT_1_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR,
        speedFactor * KEY_POINT_1_TO_ACCELERATOR_DROP_SPEED_FACTOR);

    acceleratorDrop_to_keyPoint1 = addNavigationPathWithColor(teamColor,
        navigation,
        acceleratorDropLocation,
        keyPoint1Location,
        ACCELERATOR_DROP_TO_KEY_POINT_1_COST,
        ACCELERATOR_DROP_TO_KEY_POINT_1_CP1,
        ACCELERATOR_DROP_TO_KEY_POINT_1_CP2,
        deciDegreeToRad(ACCELERATOR_DROP_DECI_DEG),
        deciDegreeToRad(KEY_POINT_1_FROM_ACCERATOR_ANGLE_DECI_DEG),
        aFactor * ACCELERATOR_DROP_TO_KEY_POINT_1_ACCELERATION_FACTOR,
        speedFactor * ACCELERATOR_DROP_TO_KEY_POINT_1_SPEED_FACTOR);

    keyPoint1_to_bigDistributorLine2Front = addNavigationPathWithColor(teamColor,
        navigation,
        keyPoint1Location,
        bigDistributorLine2FrontLocation,
        KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_COST,
        KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_CP1,
        KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_CP2,
        deciDegreeToRad(KEY_POINT_1_FROM_ACCERATOR_ANGLE_DECI_DEG),
        deciDegreeToRad(BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG),
        aFactor * KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_ACCELERATION_FACTOR,
        speedFactor * KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_SPEED_FACTOR);

    bigDistributorLine2Front_to_keyPoint1 = addNavigationPathWithColor(teamColor,
        navigation,
        bigDistributorLine2FrontLocation,
        keyPoint1Location,
        BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_COST,
        BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_CP1,
        BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_CP2,
        deciDegreeToRad(BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG),
        deciDegreeToRad(KEY_POINT_1_FROM_DISTRIBUTOR_ANGLE_DECI_DEG),
        aFactor * BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR,
        speedFactor * BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_SPEED_FACTOR);

    keyPoint1_to_bigDistributorLine3Front = addNavigationPathWithColor(teamColor,
        navigation,
        keyPoint1Location,
        bigDistributorLine3FrontLocation,
        KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_COST,
        KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_CP1,
        KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_CP2,
        deciDegreeToRad(KEY_POINT_1_FROM_ACCERATOR_ANGLE_DECI_DEG),
        deciDegreeToRad(BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG),
        aFactor * KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_ACCELERATION_FACTOR,
        speedFactor * KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_SPEED_FACTOR);

    bigDistributorLine3Front_to_keyPoint1 = addNavigationPathWithColor(teamColor,
        navigation,
        bigDistributorLine3FrontLocation,
        keyPoint1Location,
        BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_COST,
        BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_CP1,
        BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_CP2,
        deciDegreeToRad(BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG),
        deciDegreeToRad(KEY_POINT_1_FROM_DISTRIBUTOR_ANGLE_DECI_DEG),
        aFactor * BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR,
        speedFactor * BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_SPEED_FACTOR);
}


void initBigRobotTargets2019(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();
    addGameTarget(&chaosTarget, "CHAOS_TARGET", SCORE_POINT_2019_CHAOS_5_PUNK, chaosFrontLocation, rediumDropZoneLocation);
    addGameTarget(&bigDistributorLine1Target, "BIG DIST 1", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR * 2, bigDistributorLine1FrontLocation, acceleratorDropLocation);
    addGameTarget(&bigDistributorLine2Target, "BIG DIST 2", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR * 2, bigDistributorLine2FrontLocation, acceleratorDropLocation);
    addGameTarget(&bigDistributorLine3Target, "BIG DIST 3", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR * 2, bigDistributorLine3FrontLocation, acceleratorDropLocation);
}

void initBigRobotTargetActions2019(GameStrategyContext* gameStrategyContext) {
    // CHAOS
    addTargetPrepareAction(&(chaosTarget.actionList), &chaosTakeTargetAction, chaosFrontLocation, CHAOS_TAKE_TIME_TO_ACHIEVE, &chaosTakeTargetActionItemList);
    addTargetTakeAction(&(chaosTarget.actionList), &chaosDropTargetAction, rediumDropZoneLocation, CHAOS_DROP_TIME_TO_ACHIEVE, &chaosDropTargetActionItemList);

    // BIG DISTRIBUTOR LINE 1
    addTargetPrepareAction(&(bigDistributorLine1Target.actionList), &bigDistributorLine1PrepareTakeTargetAction, NULL, BIG_DISTRIBUTOR_LINE_1_PREPARE_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine1PrepareTakeTargetActionItemList);
    addTargetTakeAction(&(bigDistributorLine1Target.actionList), &bigDistributorLine1TakeTargetAction, bigDistributorLine1FrontLocation, BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine1TakeTargetActionItemList);
    addTargetDropAction(&(bigDistributorLine1Target.actionList), &bigDistributorLine1DropTargetAction, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE, &bigDistributorLine1DropTargetActionItemList);

    // BIG DISTRIBUTOR LINE 2
    addTargetPrepareAction(&(bigDistributorLine2Target.actionList), &bigDistributorLine2PrepareTakeTargetAction, NULL, BIG_DISTRIBUTOR_LINE_2_PREPARE_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine2PrepareTakeTargetActionItemList);
    addTargetTakeAction(&(bigDistributorLine2Target.actionList), &bigDistributorLine2TakeTargetAction, bigDistributorLine2FrontLocation, BIG_DISTRIBUTOR_LINE_2_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine2TakeTargetActionItemList);
    addTargetDropAction(&(bigDistributorLine2Target.actionList), &bigDistributorLine2DropTargetAction, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_2_DROP_TIME_TO_ACHIEVE, &bigDistributorLine2DropTargetActionItemList);

    // BIG DISTRIBUTOR LINE 3
    addTargetPrepareAction(&(bigDistributorLine3Target.actionList), &bigDistributorLine3PrepareTakeTargetAction, NULL, BIG_DISTRIBUTOR_LINE_3_PREPARE_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine3PrepareTakeTargetActionItemList);
    addTargetTakeAction(&(bigDistributorLine3Target.actionList), &bigDistributorLine3TakeTargetAction, bigDistributorLine3FrontLocation, BIG_DISTRIBUTOR_LINE_3_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine3TakeTargetActionItemList);
    addTargetDropAction(&(bigDistributorLine3Target.actionList), &bigDistributorLine3DropTargetAction, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_3_DROP_TIME_TO_ACHIEVE, &bigDistributorLine3DropTargetActionItemList);
}

void initBigRobotTargetActionsItems2019(GameStrategyContext* gameStrategyContext) {
    // Chaos : No specific action to do

    // Big Distributor 1 Line 1
    addTargetActionItem(&bigDistributorLine1PrepareTakeTargetActionItemList, &bigDistributorLine1PrepareTargetActionItem, &bigDistributorLinePrepare, "PREP DIST 1");
    addTargetActionItem(&bigDistributorLine1TakeTargetActionItemList, &bigDistributorLine1TakeTargetActionItem, &bigDistributorLineTake, "TAKE DIST 1");
    addTargetActionItem(&bigDistributorLine1DropTargetActionItemList, &bigDistributorLine1DropTargetActionItem, &bigDistributorAcceleratorDrop, "ACC DROP");

    // Big Distributor 1 Line 2
    addTargetActionItem(&bigDistributorLine2PrepareTakeTargetActionItemList, &bigDistributorLine2PrepareTargetActionItem, &bigDistributorLinePrepare, "PREP DIST 3");
    addTargetActionItem(&bigDistributorLine2TakeTargetActionItemList, &bigDistributorLine2TakeTargetActionItem, &bigDistributorLineTake, "TAKE DIST 3");
    addTargetActionItem(&bigDistributorLine2DropTargetActionItemList, &bigDistributorLine2DropTargetActionItem, &bigDistributorAcceleratorDrop , "ACC DROP");

    // Big Distributor 1 Line 3
    addTargetActionItem(&bigDistributorLine3PrepareTakeTargetActionItemList, &bigDistributorLine3PrepareTargetActionItem, &bigDistributorLinePrepare, "PREP DIST 3");
    addTargetActionItem(&bigDistributorLine3TakeTargetActionItemList, &bigDistributorLine3TakeTargetActionItem, &bigDistributorLineTake, "TAKE DIST 3");
    addTargetActionItem(&bigDistributorLine3DropTargetActionItemList, &bigDistributorLine3DropTargetActionItem, &bigDistributorAcceleratorDrop, "ACC DROP");
}

GameStrategy* initBigRobotStrategiesItems2019(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    if (strategyId == BIG_ROBOT_STRATEGY_1_CHAOS) {
        addGameStrategyItem(&bigRobotStrategy1Chaos, &chaosStrategyItem, &chaosTarget);
        return &bigRobotStrategy1Chaos;
    }
    else if (strategyId == BIG_ROBOT_STRATEGY_2_BIG_DISTRIBUTOR_LINE_1) {
        addGameStrategyItem(&bigRobotStrategy2BigDistributorLine1, &bigDistributorLine1StrategyItem, &bigDistributorLine1Target);
        return &bigRobotStrategy2BigDistributorLine1;
    }
    else if (strategyId == BIG_ROBOT_STRATEGY_3_BIG_DISTRIBUTOR_LINE_1_2_3) {
        addGameStrategyItem(&bigRobotStrategy3BigDistributorLine123, &bigDistributorLine1StrategyItem, &bigDistributorLine1Target);
        addGameStrategyItem(&bigRobotStrategy3BigDistributorLine123, &bigDistributorLine2StrategyItem, &bigDistributorLine2Target);
        addGameStrategyItem(&bigRobotStrategy3BigDistributorLine123, &bigDistributorLine3StrategyItem, &bigDistributorLine3Target);
        return &bigRobotStrategy3BigDistributorLine123;
    }
    else if (strategyId == BIG_ROBOT_STRATEGY_4_CHAOS_BIG_DISTRIBUTOR_LINE_1_2_3) {
        addGameStrategyItem(&bigRobotStrategy4ChaosBigDistributorLine123, &chaosStrategyItem, &chaosTarget);
        addGameStrategyItem(&bigRobotStrategy4ChaosBigDistributorLine123, &bigDistributorLine1StrategyItem, &bigDistributorLine1Target);
        addGameStrategyItem(&bigRobotStrategy4ChaosBigDistributorLine123, &bigDistributorLine2StrategyItem, &bigDistributorLine2Target);
        addGameStrategyItem(&bigRobotStrategy4ChaosBigDistributorLine123, &bigDistributorLine3StrategyItem, &bigDistributorLine3Target);
        return &bigRobotStrategy4ChaosBigDistributorLine123;
    }
    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initBigRobotStrategies2019(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();
    addGameStrategy(&bigRobotStrategy1Chaos, BIG_ROBOT_STRATEGY_1_CHAOS, "CHAOS");
    addGameStrategy(&bigRobotStrategy2BigDistributorLine1, BIG_ROBOT_STRATEGY_2_BIG_DISTRIBUTOR_LINE_1, "DIST 1");
    addGameStrategy(&bigRobotStrategy3BigDistributorLine123, BIG_ROBOT_STRATEGY_3_BIG_DISTRIBUTOR_LINE_1_2_3, "DIST 123");
    addGameStrategy(&bigRobotStrategy4ChaosBigDistributorLine123, BIG_ROBOT_STRATEGY_4_CHAOS_BIG_DISTRIBUTOR_LINE_1_2_3, "CHAOS / DIST 123");
}