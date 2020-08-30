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

#include "../../../robot/2020/commonRobot/commonRobotActions2020.h"
#include "../../../robot/2020/commonRobot/commonRobotLocations2020.h"
#include "../../../robot/2020/commonRobot/commonRobotPath2020.h"

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

#include "../../../robot/2020/commonRobot/commonRobotActions2020.h"

// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points

// Big Robot
static Location* bigRobotStartAreaLocation;
static Location* bigRobotPoint1Location;
static Location* smallHarborFrontMiddleLocation;
static Location* dropLightHouseFrontLocation;

// static Location* centerPointLocation;
static Location* leftReefTakeLocation;
static Location* leftReefFrontLocation;
static Location* frontLeftLocation;
static Location* dropLeftLocation;
// static Location* centerStartAreaLocation;
// static Location* leftReef2FrontLocation;
// static Location* dropCenterFrontLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Big Robot
PathData* bigRobotStartArea_to_point1_Path;
// PathData* point1_to_smallHarborFrontMiddle_Path;
PathData* point1_to_lightHouseDropFrontMiddle_Path;
PathData* lightHouseDrop_to_smallHarborFrontMiddle_Path;

PathData* smallHarborFrontMiddle_to_leftReefFront_Path;
PathData* leftReefFront_to_leftReefTake_Path;
PathData* leftReefTake_to_frontLeft_Path;
PathData* frontLeft_to_dropLeftFront_Path;
PathData* dropLeftFront_to_centerStartArea_Path;
PathData* centerStartArea_to_leftReef2_Path;
PathData* leftReef2_to_centerPoint_Path;
PathData* centerPoint_to_dropCenter_Path;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List

static GameTarget lightHouseTarget;
static GameTarget smallHarbor1Target;
static GameTarget leftReefTarget;
// static GameTarget leftReef2Target;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// Lighthouse
static GameTargetAction lightHousePrepareTargetAction;
static GameTargetAction lightHouseTakeTargetAction;
static GameTargetAction lightHouseDropTargetAction;

// Small Harbor 1
static GameTargetAction smallHarbor1PrepareTargetAction;
// static GameTargetAction smallHarbor1TakeTargetAction;
static GameTargetAction smallHarbor1DropTargetAction;

// To take Cup from Left Reef
static GameTargetAction leftCupPrepareTargetAction;
static GameTargetAction leftCupTakeTargetAction;
static GameTargetAction leftCupDropTargetAction;

// To take Cup from Left Reef 2
/*
static GameTargetAction left2CupPrepareTargetAction;
static GameTargetAction left2CupTakeTargetAction;
static GameTargetAction left2CupDropTargetAction;
*/
// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Big Robot -> Light House
static GameTargetActionItemList lightHousePrepareTargetActionItemList;
static GameTargetActionItemList lightHouseTakeTargetActionItemList;
static GameTargetActionItemList lightHouseDropTargetActionItemList;

// Big Robot -> Small Harbor 1
static GameTargetActionItemList smallHarbor1PrepareTargetActionItemList;
// static GameTargetActionItemList smallHarbor1TakeTargetActionItemList;
static GameTargetActionItemList smallHarbor1DropTargetActionItemList;

// Big Robot -> Left Reef
static GameTargetActionItemList leftCupPrepareTargetActionItemList;
static GameTargetActionItemList leftCupTakeTargetActionItemList;
static GameTargetActionItemList leftCupDropTargetActionItemList;

// Big Robot -> Left Reef 2
/*
static GameTargetActionItemList left2CupPrepareTargetActionItemList;
static GameTargetActionItemList left2CupTakeTargetActionItemList;
static GameTargetActionItemList left2CupDropTargetActionItemList;
*/
// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

// Big Robot

// -> LightHouse
static GameTargetActionItem lightHousePrepareCupTargetActionItem;
static GameTargetActionItem lightHousePrepareArmTargetActionItem;
static GameTargetActionItem lightHouseTakeTargetActionItem;
//static GameTargetActionItem lightHouseDropTargetActionItem;

// -> Small Harbor 1
static GameTargetActionItem smallHarbor1PrepareTargetActionItem;
// static GameTargetActionItem smallHarbor1TakeTargetActionItem;
static GameTargetActionItem smallHarbor1DropTargetActionItem;

// -> Cup
static GameTargetActionItem leftCupPrepareTargetActionItem;
static GameTargetActionItem leftCupTakeTargetActionItem;
static GameTargetActionItem leftCupDropTargetActionItem;

// -> Cup 2
/*
static GameTargetActionItem left2CupPrepareTargetActionItem;
static GameTargetActionItem left2CupTakeTargetActionItem;
static GameTargetActionItem left2CupDropTargetActionItem;
*/
// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

// 
static GameStrategy bigRobotStrategy1;
static GameStrategy bigRobotStrategy2;
static GameStrategy bigRobotStrategy3;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

static GameStrategyItem lightHouseStrategyItem;
static GameStrategyItem bigRobotSmallHarborStrategyItem;
static GameStrategyItem leftReefStrategyItem;
// static GameStrategyItem leftReef2StrategyItem;

void initBigRobotLocations2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    bigRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, BIG_ROBOT_START_AREA, BIG_ROBOT_START_AREA_LABEL, BIG_ROBOT_START_AREA_X, BIG_ROBOT_START_AREA_Y);
    bigRobotPoint1Location = addLocationWithColors(teamColor, navigation, BIG_ROBOT_POINT_1, BIG_ROBOT_POINT_1_LABEL, BIG_ROBOT_POINT_1_X, BIG_ROBOT_POINT_1_Y);

    dropLightHouseFrontLocation = addLocationWithColors(teamColor, navigation, LIGHT_HOUSE_DROP_POINT, LIGHT_HOUSE_DROP_POINT_LABEL, LIGHT_HOUSE_DROP_POINT_X, LIGHT_HOUSE_DROP_POINT_Y);
    smallHarborFrontMiddleLocation = addLocationWithColors(teamColor, navigation, SMALL_HARBOR_FRONT_MIDDLE, SMALL_HARBOR_FRONT_MIDDLE_LABEL, SMALL_HARBOR_FRONT_MIDDLE_X, SMALL_HARBOR_FRONT_MIDDLE_Y);
    // centerPointLocation = addLocationWithColors(teamColor, navigation, CENTER_POINT, CENTER_POINT_LABEL, CENTER_POINT_X, CENTER_POINT_Y);
    leftReefFrontLocation = addLocationWithColors(teamColor, navigation, LEFT_REEF_FRONT, LEFT_REEF_FRONT_LABEL, LEFT_REEF_FRONT_X, LEFT_REEF_FRONT_Y);
    leftReefTakeLocation = addLocationWithColors(teamColor, navigation, LEFT_REEF_TAKE, LEFT_REEF_TAKE_LABEL, LEFT_REEF_TAKE_X, LEFT_REEF_TAKE_Y);
    leftReefTakeLocation->adjustType = LOCATION_ADJUST_X;
    leftReefTakeLocation->adjustValue = LEFT_REEF_TAKE_ADJUST_X;
    frontLeftLocation = addLocationWithColors(teamColor, navigation, FRONT_LEFT, FRONT_LEFT_LABEL, FRONT_LEFT_X, FRONT_LEFT_Y);
    dropLeftLocation = addLocationWithColors(teamColor, navigation, DROP_LEFT, DROP_LEFT_LABEL, DROP_LEFT_X, DROP_LEFT_Y);
    /*
    centerStartAreaLocation = addLocationWithColors(teamColor, navigation, CENTER_START_AREA, CENTER_START_AREA_LABEL, CENTER_START_AREA_X, CENTER_START_AREA_Y);
    leftReef2FrontLocation = addLocationWithColors(teamColor, navigation, LEFT_REEF_2_FRONT, LEFT_REEF_2_FRONT_LABEL, LEFT_REEF_2_FRONT_X, LEFT_REEF_2_FRONT_Y);
    dropCenterFrontLocation = addLocationWithColors(teamColor, navigation, DROP_CENTER_FRONT, DROP_CENTER_FRONT_LABEL, DROP_CENTER_FRONT_X, DROP_CENTER_FRONT_Y);
*/
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

    /*
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
        */

    point1_to_lightHouseDropFrontMiddle_Path = addNavigationPathWithColor(teamColor,
        navigation,
        bigRobotPoint1Location,
        dropLightHouseFrontLocation,
        BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_COST,
        BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_CP1,
        BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_CP2,
        deciDegreeToRad(BIG_ROBOT_POINT_1_START_ANGLE_DECI_DEG),
        deciDegreeToRad(LIGHT_HOUSE_DROP_POINT_ANGLE_DECI_DEG),
        speedFactor * BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_SPEED_FACTOR,
        aFactor * BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT__ACC_FACTOR
    );

    lightHouseDrop_to_smallHarborFrontMiddle_Path = addNavigationPathWithColor(teamColor,
        navigation,
        dropLightHouseFrontLocation,
        smallHarborFrontMiddleLocation,
        LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_COST,
        LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_CP1,
        LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_CP2,
        deciDegreeToRad(LIGHT_HOUSE_DROP_POINT_ANGLE_DECI_DEG),
        deciDegreeToRad(SMALL_HARBOR_FRONT_MIDDLE_ANGLE_DECI_DEG),
        speedFactor * LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_SPEED_FACTOR,
        aFactor * LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_ACC_FACTOR
    );

    smallHarborFrontMiddle_to_leftReefFront_Path = addNavigationPathWithColor(teamColor,
        navigation,
        smallHarborFrontMiddleLocation,
        leftReefFrontLocation,
        SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_COST,
        SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_CP1,
        SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_CP2,
        deciDegreeToRad(SMALL_HARBOR_FRONT_MIDDLE_ANGLE_DECI_DEG),
        deciDegreeToRad(LEFT_REEF_FRONT_START_ANGLE_DECI_DEG),
        speedFactor * SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_SPEED_FACTOR,
        aFactor * SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_ACC_FACTOR
        );

    leftReefFront_to_leftReefTake_Path = addNavigationPathWithColor(teamColor,
        navigation,
        leftReefFrontLocation,
        leftReefTakeLocation,
        LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_COST,
        LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_CP1,
        LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_CP2,
        deciDegreeToRad(LEFT_REEF_FRONT_END_ANGLE_DECI_DEG),
        deciDegreeToRad(LEFT_REEF_TAKE_ANGLE_DECI_DEG),
        speedFactor * LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_SPEED_FACTOR,
        aFactor * LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_ACC_FACTOR
    );

    leftReefTake_to_frontLeft_Path = addNavigationPathWithColor(teamColor,
        navigation,
        leftReefTakeLocation,
        frontLeftLocation,
        LEFT_REEF_TAKE__TO__FRONT_LEFT_COST,
        LEFT_REEF_TAKE__TO__FRONT_LEFT_CP1,
        LEFT_REEF_TAKE__TO__FRONT_LEFT_CP2,
        deciDegreeToRad(LEFT_REEF_TAKE_ANGLE_DECI_DEG),
        deciDegreeToRad(FRONT_LEFT_ANGLE_DECI_DEG),
        speedFactor * LEFT_REEF_TAKE__TO__FRONT_LEFT_SPEED_FACTOR,
        aFactor * LEFT_REEF_TAKE__TO__FRONT_LEFT_ACC_FACTOR
    );

    frontLeft_to_dropLeftFront_Path = addNavigationPathWithColor(teamColor,
        navigation,
        frontLeftLocation,
        dropLeftLocation,
        FRONT_LEFT__TO__DROP_LEFT_COST,
        FRONT_LEFT__TO__DROP_LEFT_CP1,
        FRONT_LEFT__TO__DROP_LEFT_CP2,
        deciDegreeToRad(FRONT_LEFT_ANGLE_DECI_DEG),
        deciDegreeToRad(DROP_LEFT_ANGLE_DECI_DEG),
        speedFactor * FRONT_LEFT__TO__DROP_LEFT_SPEED_FACTOR,
        aFactor * FRONT_LEFT__TO__DROP_LEFT_ACC_FACTOR
    );
    /*
    dropLeftFront_to_centerStartArea_Path = addNavigationPathWithColor(teamColor,
        navigation,
        dropLeftFrontLocation,
        centerStartAreaLocation,
        DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_COST,
        DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_CP1,
        DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_CP2,
        deciDegreeToRad(DROP_LEFT_FRONT_DECI_DEG),
        deciDegreeToRad(CENTER_START_AREA_ANGLE_DECI_DEG),
        speedFactor * DROP_LEFT_FRONT__TO__CENTRAL_START_SPEED_FACTOR,
        aFactor * DROP_LEFT_FRONT__TO__CENTRAL_START_ACC_FACTOR
    );
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

    leftReef2_to_centerPoint_Path = addNavigationPathWithColor(teamColor,
        navigation,
        leftReef2FrontLocation,
        centerPointLocation,
        LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_COST,
        LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_CP1,
        LEFT_REEF_FRONT_2__TO__CENTRAL_POINT_CP2,
        deciDegreeToRad(LEFT_REEF_2_FRONT_ANGLE_DECI_DEG),
        deciDegreeToRad(CENTER_POINT_END_ANGLE_DECI_DEG),
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
        deciDegreeToRad(CENTER_POINT_END_ANGLE_DECI_DEG),
        deciDegreeToRad(DROP_CENTER_FRONT_DECI_DEG),
        speedFactor * CENTRAL_POINT__TO__DROP_CENTER_FRONT_SPEED_FACTOR,
        aFactor * CENTRAL_POINT__TO__DROP_CENTER_FRONT_ACC_FACTOR
    );
    */
}

void initBigRobotTargets2020(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();
    // TODO : Change Value of gain
    addGameTarget(&lightHouseTarget, "LIGHT HOUSE", 30, bigRobotStartAreaLocation, dropLightHouseFrontLocation);
    addGameTarget(&smallHarbor1Target, "SMALL_HARB_1", 30, dropLightHouseFrontLocation, smallHarborFrontMiddleLocation);
    addGameTarget(&leftReefTarget, "LEFT_REEF", 10, leftReefTakeLocation, dropLeftLocation);
    // addGameTarget(&leftReefTarget, "LEFT_REEF2", 10, leftReef2FrontLocation, dropCenterFrontLocation);
}

void initBigRobotTargetActions2020(GameStrategyContext* gameStrategyContext) {

    // LightHouse
    addTargetPrepareAction(&(lightHouseTarget.actionList), &lightHousePrepareTargetAction, bigRobotStartAreaLocation, 0.0f, &lightHousePrepareTargetActionItemList);
    addTargetTakeAction(&(lightHouseTarget.actionList), &lightHouseTakeTargetAction, bigRobotPoint1Location, 1.0f, &lightHouseTakeTargetActionItemList);
    addTargetDropAction(&(lightHouseTarget.actionList), &lightHouseDropTargetAction, dropLightHouseFrontLocation, 0.0f, &lightHouseDropTargetActionItemList);

    // SmallHarbor1
    // TODO : Change Time
    addTargetPrepareAction(&(smallHarbor1Target.actionList), &smallHarbor1PrepareTargetAction, dropLightHouseFrontLocation, 10, &smallHarbor1PrepareTargetActionItemList);
    // addTargetTakeAction(&(smallHarbor1Target.actionList), &smallHarbor1TakeTargetAction, bigRobotPoint1Location, 10, &smallHarbor1TakeTargetActionItemList);
    addTargetDropAction(&(smallHarbor1Target.actionList), &smallHarbor1DropTargetAction, smallHarborFrontMiddleLocation, 10, &smallHarbor1DropTargetActionItemList);

    // LeftReef
    // TODO : Change Time
    addTargetPrepareAction(&(leftReefTarget.actionList), &leftCupPrepareTargetAction, leftReefFrontLocation, 10, &leftCupPrepareTargetActionItemList);
    addTargetTakeAction(&(leftReefTarget.actionList), &leftCupTakeTargetAction, leftReefTakeLocation, 10, &leftCupTakeTargetActionItemList);
    addTargetDropAction(&(leftReefTarget.actionList), &leftCupDropTargetAction, dropLeftLocation, 10, &leftCupDropTargetActionItemList);

    // LeftReef 2
    // TODO : Change Time
    /*
    addTargetPrepareAction(&(leftReef2Target.actionList), &left2CupPrepareTargetAction, centerStartAreaLocation, 10, &left2CupPrepareTargetActionItemList);
    addTargetTakeAction(&(leftReef2Target.actionList), &left2CupTakeTargetAction, leftReef2FrontLocation, 10, &left2CupTakeTargetActionItemList);
    addTargetDropAction(&(leftReef2Target.actionList), &left2CupDropTargetAction, dropCenterFrontLocation, 10, &left2CupDropTargetActionItemList);
    */
}

void initBigRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext) {
    // Light House
    addTargetActionItem(&lightHousePrepareTargetActionItemList, &lightHousePrepareCupTargetActionItem, &bigRobotPrepareFloorCups, NULL, "PREP FLOOR CUPS");
    addTargetActionItem(&lightHousePrepareTargetActionItemList, &lightHousePrepareArmTargetActionItem, &lightHouseLateralArmOn, NULL, "ARM ON");
    addTargetActionItem(&lightHouseTakeTargetActionItemList, &lightHouseTakeTargetActionItem, &bigRobotLockFloorCups, &commonAreActionsFinished, "LOCK FLOOR CUPS");

    // Small Harbor 1
    // TODO : Replace takeCups by more precise semantic
    addTargetActionItem(&smallHarbor1PrepareTargetActionItemList, &smallHarbor1PrepareTargetActionItem, &lightHouseLateralArmOff, NULL, "ARM OFF");
    // addTargetActionItem(&smallHarbor1TakeTargetActionItemList, &smallHarbor1TakeTargetActionItem, &bigRobotLockFloorCups, &commonAreActionsFinished, "SMALL HARBOR 1 -> LOOK FLOOR CUPS");
    addTargetActionItem(&smallHarbor1DropTargetActionItemList, &smallHarbor1DropTargetActionItem, &bigRobotReleaseCups, &commonAreActionsFinished, "SMALL HARBOR 1 -> DROP CUPS");

    // Left Reef
    addTargetActionItem(&leftCupPrepareTargetActionItemList, &leftCupPrepareTargetActionItem, &bigRobotPrepareHook, NULL, "LEFT REEF -> PREP CUP UP");
    addTargetActionItem(&leftCupTakeTargetActionItemList, &leftCupTakeTargetActionItem, &bigRobotTakeCups, &commonAreActionsFinished, "LEFT REEF -> TAKE CUPS");
    addTargetActionItem(&leftCupDropTargetActionItemList, &leftCupDropTargetActionItem, &bigRobotDropCups, &commonAreActionsFinished, "LEFT REEF -> DROP CUPS");

    // Left Reef 2
    /*
    addTargetActionItem(&left2CupPrepareTargetActionItemList, &left2CupPrepareTargetActionItem, &bigRobotPrepareHook, NULL, "LEFT REEF 2 -> PREP CUP UP");
    addTargetActionItem(&left2CupTakeTargetActionItemList, &left2CupTakeTargetActionItem, &bigRobotTakeCups, &commonAreActionsFinished, "LEFT REEF 2 -> TAKE CUPS");
    addTargetActionItem(&left2CupDropTargetActionItemList, &left2CupDropTargetActionItem, &bigRobotDropCups, &commonAreActionsFinished, "LEFT REEF 2 -> DROP CUPS");
    */
}

GameStrategy* initBigRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    else if (strategyId == BIG_ROBOT_STRATEGY_2020_1_SMALL_HARBOR) {
        addGameStrategyItem(&bigRobotStrategy1, &lightHouseStrategyItem, &lightHouseTarget);
        addGameStrategyItem(&bigRobotStrategy1, &bigRobotSmallHarborStrategyItem, &smallHarbor1Target);
        return &bigRobotStrategy1;
    }
    else if (strategyId == BIG_ROBOT_STRATEGY_2020_2_SMALL_HARBOR_LEFT_REEF) {
        addGameStrategyItem(&bigRobotStrategy2, &lightHouseStrategyItem, &lightHouseTarget);
        addGameStrategyItem(&bigRobotStrategy2, &bigRobotSmallHarborStrategyItem, &smallHarbor1Target);
        addGameStrategyItem(&bigRobotStrategy2, &leftReefStrategyItem, &leftReefTarget);
        return &bigRobotStrategy2;
    }
    /*
    else if (strategyId == BIG_ROBOT_STRATEGY_2020_3_SMALL_HARBOR_BOTH_REEF) {
        addGameStrategyItem(&bigRobotStrategy3, &lightHouseStrategyItem, &lightHouseTarget);
        addGameStrategyItem(&bigRobotStrategy3, &bigRobotSmallHarborStrategyItem, &smallHarbor1Target);
        addGameStrategyItem(&bigRobotStrategy3, &leftReefStrategyItem, &leftReefTarget);
        addGameStrategyItem(&bigRobotStrategy3, &leftReef2StrategyItem, &leftReef2Target);
        return &bigRobotStrategy3;
    }
    */
    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initBigRobotStrategies2020(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();
    addGameStrategy(&bigRobotStrategy1, BIG_ROBOT_STRATEGY_2020_1_SMALL_HARBOR, "SMALL HARBOR");
    addGameStrategy(&bigRobotStrategy2, BIG_ROBOT_STRATEGY_2020_2_SMALL_HARBOR_LEFT_REEF, "SMALL HARBOR & LEFT REEF");
    addGameStrategy(&bigRobotStrategy3, BIG_ROBOT_STRATEGY_2020_3_SMALL_HARBOR_BOTH_REEF, "SMALL HARBOR & BOTH REEF");
}
