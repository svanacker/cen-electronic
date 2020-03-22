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

// static Location* blueiumRightLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Small Robot
// PathData* smallRobotStartArea_to_accelerator_Path;


// ------------------------------------------------------- TARGET -------------------------------------------------------------------------

// static GameTarget acceleratorTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// static GameTargetAction acceleratorPrepareTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Accelerator
// static GameTargetActionItemList acceleratorPrepareTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

// static GameTargetActionItem acceleratorPrepareTargetActionItem1;
// static GameTargetActionItem acceleratorRotationTargetActionItem;
// static GameTargetActionItem acceleratorDropTargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

// SMALL ROBOT
// static GameStrategy smallRobotStrategy1Accelerator;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items
// static GameStrategyItem acceleratorStrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void initSmallRobotLocations2020(GameStrategyContext* gameStrategyContext) {
    // Navigation* navigation = gameStrategyContext->navigation;
    // enum TeamColor teamColor = gameStrategyContext->color;

    // smallRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, SMALL_ROBOT_START_AREA, SMALL_ROBOT_START_AREA_LABEL, SMALL_ROBOT_START_AREA_X, SMALL_ROBOT_START_AREA_Y);
}

void initSmallRobotPaths2020(GameStrategyContext* gameStrategyContext) {
    /*
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;
    float aFactor = gameStrategyContext->defaultAccelerationFactor;
    float speedFactor = gameStrategyContext->defaultSpeedFactor;
*/
    // -> Small Robot
    /*
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
     */
}

void initSmallRobotTargets2020(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();
    /*
    gameStrategyContext->endMatch->scoreToShow += SCORE_POINT_2019_EXPERIENCE_READY;
    addGameTarget(&acceleratorTarget, "ACC_TARGET", SCORE_POINT_2019_EXPERIENCE_ACTIVATED_AND_OK + SCORE_POINT_2019_LAUNCH_BLUIUM_IN_ACCELERATOR, acceleratorFrontLocation, acceleratorFrontLocation);
    addGameTarget(&goldeniumTakeTarget, "GOLD_TAKE_TARGET", SCORE_POINT_2019_EXTRACT_GOLDENIUM, goldeniumFrontLocation, goldeniumFrontLocation);
    addGameTarget(&goldeniumDropTarget, "GOLD_DROP_TARGET", SCORE_POINT_2019_WEIGHING_MACHINE_GOLDENIUM, weighingMachineDropLocation, weighingMachineDropLocation);

    // TODO : SCORE_POINT_2019_ADD_ATOM_ACCELERATOR is false
    addGameTarget(&smallDistributorLine1Target, "SMALL_DIST_1_TARGET", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR, smallDistributorLine1Location, weighingMachineDropLocation);
    addGameTarget(&bigDistributorLine3RediumGreeniumTarget, "BIG_DIST_RED_TARGET_3", 10.0f, bigDistributorLine3Location, rediumGreeniumDropLocation);
    addGameTarget(&bigDistributorLine2BlueiumGreeniumTarget, "BIG_DIST_RED_TARGET_2", 5.0f, bigDistributorLine2Location, blueiumGreeniumDropLocation);
     */
}

void initSmallRobotTargetActions2020(GameStrategyContext* gameStrategyContext) {
    // ACCELERATOR TARGET
    /*
    addTargetPrepareAction(&(acceleratorTarget.actionList), &acceleratorPrepareTargetAction, smallRobotStartAreaLocation, ACCELERATOR_ARM_ON_ACTION_TIME_TO_ACHIEVE, &acceleratorPrepareTargetActionItemList);
    addTargetDropAction(&(acceleratorTarget.actionList), &acceleratorDropTargetAction, acceleratorFrontLocation, ACCELERATOR_ARM_OFF_ACTION_TIME_TO_ACHIEVE, &acceleratorDropTargetActionItemList);
     */
}

void initSmallRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext) {
    // Accelerator => We remove the arm when reaching the drop (drop is done by the move of the robot)
    // addTargetActionItem(&acceleratorPrepareTargetActionItemList, &acceleratorPrepareTargetActionItem1, &acceleratorArmOn, "ACC ARM ON");

}

GameStrategy* initSmallRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    if (strategyId == SMALL_ROBOT_STRATEGY_1_ACCELERATOR) {
        // addGameStrategyItem(&smallRobotStrategy1Accelerator, &acceleratorStrategyItem, &acceleratorTarget);
        // return &smallRobotStrategy1Accelerator;
    }

    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initSmallRobotStrategies2020(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();

    /*
    addGameStrategy(&smallRobotStrategy1Accelerator, SMALL_ROBOT_STRATEGY_1_ACCELERATOR, "ACCELERATOR");
    addGameStrategy(&smallRobotStrategy2AcceleratorTakeGoldenium, SMALL_ROBOT_STRATEGY_2_ACCELERATOR_TAKE_GOLDENIUM, "ACC / TAKE GOLD");
    addGameStrategy(&smallRobotStrategy3AcceleratorTakeDropGoldenium, SMALL_ROBOT_STRATEGY_3_ACCELERATOR_TAKE_DROP_GOLDENIUM, "ACC / TAKE DROP GOLD");
     */
}