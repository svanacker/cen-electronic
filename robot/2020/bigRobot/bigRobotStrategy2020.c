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

#include "../../../robot/2020/strategy/teamColor2020.h"
#include "../../../robot/2020/strategy/strategy2020.h"
#include "../../../robot/2020/strategy/strategy2020Utils.h"
#include "../../../robot/2020/strategy/strategyConfig2020.h"

// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points

// Big Robot
static Location* bigRobotStartAreaLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Big Robot
PathData* bigRobotStartArea_to_bigDistributorLine1Front;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List

static GameTarget harborTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// static GameTargetAction chaosTakeTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Big Robot
// static GameTargetActionItemList chaosTakeTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

// Big Robot
// static GameTargetActionItem bigDistributorLine1PrepareTargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

// static GameStrategy bigRobotStrategy1Chaos;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// static GameStrategyItem chaosStrategyItem;

void initBigRobotLocations2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    bigRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, BIG_ROBOT_START_AREA, BIG_ROBOT_START_AREA_LABEL, BIG_ROBOT_START_AREA_X, BIG_ROBOT_START_AREA_Y);
}

void initBigRobotPaths2020(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    float aFactor = gameStrategyContext->defaultAccelerationFactor;
    float speedFactor = gameStrategyContext->defaultSpeedFactor;

    // Big Robot
    /*
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
    */
}


void initBigRobotTargets2020(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();
    // addGameTarget(&chaosTarget, "CHAOS_TARGET", SCORE_POINT_2019_CHAOS_5_PUNK, chaosFrontLocation, rediumDropZoneLocation);
}

void initBigRobotTargetActions2020(GameStrategyContext* gameStrategyContext) {
    // CHAOS
//    addTargetPrepareAction(&(chaosTarget.actionList), &chaosTakeTargetAction, chaosFrontLocation, CHAOS_TAKE_TIME_TO_ACHIEVE, &chaosTakeTargetActionItemList);
//    addTargetTakeAction(&(chaosTarget.actionList), &chaosDropTargetAction, rediumDropZoneLocation, CHAOS_DROP_TIME_TO_ACHIEVE, &chaosDropTargetActionItemList);
}

void initBigRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext) {
    // Chaos : No specific action to do

    // Big Distributor 1 Line 1
    // addTargetActionItem(&bigDistributorLine1PrepareTakeTargetActionItemList, &bigDistributorLine1PrepareTargetActionItem, &bigDistributorLinePrepare, "PREP DIST 1");
    // addTargetActionItem(&bigDistributorLine1TakeTargetActionItemList, &bigDistributorLine1TakeTargetActionItem, &bigDistributorLineTake, "TAKE DIST 1");
    // addTargetActionItem(&bigDistributorLine1DropTargetActionItemList, &bigDistributorLine1DropTargetActionItem, &bigDistributorAcceleratorDrop, "ACC DROP");
}

GameStrategy* initBigRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    if (strategyId == BIG_ROBOT_STRATEGY_1_CHAOS) {
        // addGameStrategyItem(&bigRobotStrategy1Chaos, &chaosStrategyItem, &chaosTarget);
        // return &bigRobotStrategy1Chaos;
    }
    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initBigRobotStrategies2020(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();
    // addGameStrategy(&bigRobotStrategy1Chaos, BIG_ROBOT_STRATEGY_1_CHAOS, "CHAOS");
}