#include "smallRobotStrategy2019.h"

#include <stdlib.h>

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

#include "../../../robot/2019/fork/forkDevice2019.h"

#include "../../../robot/2019/navigation/angle2019.h"
#include "../../../robot/2019/navigation/location2019.h"
#include "../../../robot/2019/navigation/path2019.h"

#include "../../../robot/2019/smallRobot/smallRobotActions2019.h"
#include "../../../robot/2019/smallRobot/smallRobotLocation2019.h"
#include "../../../robot/2019/smallRobot/smallRobotPath2019.h"
#include "../../../robot/2019/smallRobot/smallRobotStrategy2019.h"

#include "../../../robot/2019/strategy/strategy2019Utils.h"
#include "../../../robot/2019/strategy/strategyConfig2019.h"
#include "../../../robot/2019/strategy/teamColor2019.h"

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------

static Location* blueiumRightLocation;
static Location* smallDistributorLine1Location;
static Location* smallRobotStartAreaLocation;
static Location* acceleratorFrontLocation;
static Location* acceleratorCenteredLocation;
static Location* goldeniumFrontLocation;
static Location* weighingMachineFrontLocation;
static Location* weighingMachineDropLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

// Small Robot
PathData* smallRobotStartArea_to_accelerator_Path;
PathData* smallRobotStartArea_to_acceleratorCentered_Path;
PathData* acceleratorCentered_to_accelerator_Path;

PathData* acceleratorFront_to_goldeniumFront_Path;
PathData* goldeniumFront_to_weighingMachineFront_Path;
PathData* weighingMachineFront_to_weighingMachineDrop_Path;

PathData* weighingMachineDrop_to_bluiumRight_Path;
PathData* bluiumRight_to_smallDistributor_Path;

PathData* smallDistributor_to_bluiumRight_Path;
PathData* bluiumRight_to_weighingMachineDrop_Path;


// Go back Home
PathData* weighingMachineDrop_to_smallRobotStartArea_Path;


// ------------------------------------------------------- TARGET -------------------------------------------------------------------------

static GameTarget acceleratorTarget;
static GameTarget goldeniumTakeTarget;
static GameTarget goldeniumDropTarget;
static GameTarget smallDistributorLine1Target;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

static GameTargetAction acceleratorPrepareTargetAction;
static GameTargetAction acceleratorDropTargetAction;

static GameTargetAction goldeniumPrepareTakeTargetAction;
static GameTargetAction goldeniumTakeTargetAction;

static GameTargetAction goldeniumPrepareDropTargetAction;
static GameTargetAction goldeniumDropTargetAction;

static GameTargetAction smallDistributorLine1PrepareTargetAction;
static GameTargetAction smallDistributorLine1TakeTargetAction;
static GameTargetAction smallDistributorLine1DropTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Accelerator
static GameTargetActionItemList acceleratorPrepareTargetActionItemList;
static GameTargetActionItemList acceleratorDropTargetActionItemList;

// Take Goldenium
static GameTargetActionItemList goldeniumPrepareTakeTargetActionItemList;
static GameTargetActionItemList goldeniumTakeTargetActionItemList;

// Drop Goldenium
static GameTargetActionItemList goldeniumPrepareDropTargetActionItemList;
static GameTargetActionItemList goldeniumDropTargetActionItemList;

// Small Distributor Line 1
static GameTargetActionItemList smallDistributorLine1PrepareTargetActionItemList;
static GameTargetActionItemList smallDistributorLine1TakeTargetActionItemList;
static GameTargetActionItemList smallDistributorLine1DropTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

static GameTargetActionItem acceleratorPrepareTargetActionItem;
static GameTargetActionItem acceleratorRotationTargetActionItem;
static GameTargetActionItem acceleratorDropTargetActionItem;

static GameTargetActionItem goldeniumPrepareTakeTargetActionItem;
static GameTargetActionItem goldeniumTakeTargetActionItem;

static GameTargetActionItem goldeniumPrepareDropTargetActionItem;
static GameTargetActionItem goldeniumDropTargetActionItem;

static GameTargetActionItem smallDistributorLine1PrepareTargetActionItem;
static GameTargetActionItem smallDistributorLine1TakeTargetActionItem;
static GameTargetActionItem smallDistributorLine1DropTargetActionItem;


// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy

// SMALL ROBOT
static GameStrategy smallRobotStrategy1Accelerator;
static GameStrategy smallRobotStrategy2AcceleratorTakeGoldenium;
static GameStrategy smallRobotStrategy3AcceleratorTakeDropGoldenium;
static GameStrategy smallRobotStrategy4AcceleratorTakeDropGoldeniumSmallDist;
static GameStrategy smallRobotStrategy5AcceleratorCenteredTakeDropGoldeniumSmallDist;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items
static GameStrategyItem acceleratorStrategyItem;
static GameStrategyItem takeGoldeniumStrategyItem;
static GameStrategyItem dropGoldeniumStrategyItem;
static GameStrategyItem smallDistributorLine1StrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void initSmallRobotLocations2019(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;

    smallRobotStartAreaLocation = addLocationWithColors(teamColor, navigation, SMALL_ROBOT_START_AREA, SMALL_ROBOT_START_AREA_LABEL, SMALL_ROBOT_START_AREA_X, SMALL_ROBOT_START_AREA_Y);
    acceleratorFrontLocation = addLocationWithColors(teamColor, navigation, ACCELERATOR_FRONT, ACCELERATOR_FRONT_LABEL, ACCELERATOR_FRONT_X, ACCELERATOR_FRONT_Y);
    acceleratorCenteredLocation = addLocationWithColors(teamColor, navigation, ACCELERATOR_CENTER, ACCELERATOR_CENTER_LABEL, ACCELERATOR_CENTER_X, ACCELERATOR_CENTER_Y);
    goldeniumFrontLocation = addLocationWithColors(teamColor, navigation, GOLDENIUM_FRONT, GOLDENIUM_FRONT_LABEL, GOLDENIUM_FRONT_X, GOLDENIUM_FRONT_Y);
    weighingMachineFrontLocation = addLocationWithColors(teamColor, navigation, WEIGHING_MACHINE_FRONT, WEIGHING_MACHINE_FRONT_LABEL, WEIGHING_MACHINE_FRONT_X, WEIGHING_MACHINE_FRONT_Y);
    weighingMachineDropLocation = addLocationWithColors(teamColor, navigation, WEIGHING_MACHINE_DROP, WEIGHING_MACHINE_DROP_LABEL, WEIGHING_MACHINE_DROP_X, WEIGHING_MACHINE_DROP_Y);
    blueiumRightLocation = addLocationWithColors(teamColor, navigation, BLUEIUM_RIGHT, BLUEIUM_RIGHT_LABEL, BLUEIUM_RIGHT_X, BLUEIUM_RIGHT_Y);
    smallDistributorLine1Location = addLocationWithColors(teamColor, navigation, SMALL_DISTRIBUTOR_LINE_1, SMALL_DISTRIBUTOR_LINE_1_LABEL, SMALL_DISTRIBUTOR_LINE_1_X, SMALL_DISTRIBUTOR_LINE_1_Y);
}

void initSmallRobotPaths2019(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;
    float aFactor = gameStrategyContext->defaultAccelerationFactor;
    float speedFactor = gameStrategyContext->defaultSpeedFactor;

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

    smallRobotStartArea_to_acceleratorCentered_Path = addNavigationPathWithColor(teamColor,
        navigation,
        smallRobotStartAreaLocation,
        acceleratorCenteredLocation,
        SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CENTERED_COST,
        SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CENTERED_CP1,
        SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CENTERED_CP2,
        deciDegreeToRad(SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG),
        deciDegreeToRad(ACCELERATOR_CENTER_START_DECI_DEG),
        aFactor * SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CENTERED_ACCELERATION_FACTOR,
        speedFactor * SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CENTERED_SPEED_FACTOR);

    acceleratorCentered_to_accelerator_Path = addNavigationPathWithColor(teamColor,
        navigation,
        acceleratorCenteredLocation,
        acceleratorFrontLocation,
        ACCELERATOR_CENTERED_TO_ACCELERATOR_COST,
        ACCELERATOR_CENTERED_TO_ACCELERATOR_CP1,
        ACCELERATOR_CENTERED_TO_ACCELERATOR_CP2,
        deciDegreeToRad(ACCELERATOR_CENTER_END_DECI_DEG),
        deciDegreeToRad(ACCELERATOR_CENTER_END_DECI_DEG),
        aFactor * ACCELERATOR_CENTERED_TO_ACCELERATOR_ACCELERATION_FACTOR,
        speedFactor * SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CENTERED_SPEED_FACTOR);

    acceleratorFront_to_goldeniumFront_Path = addNavigationPathWithColor(teamColor,
        navigation,
        acceleratorFrontLocation,
        goldeniumFrontLocation,
        ACCELERATOR_TO_GOLDENIUM_COST,
        ACCELERATOR_TO_GOLDENIUM_CP1,
        ACCELERATOR_TO_GOLDENIUM_CP2,
        deciDegreeToRad(ACCELERATOR_FRONT_DECI_DEG),
        deciDegreeToRad(GOLDENIUM_FRONT_ANGLE_DECI_DEG),
        aFactor * ACCELERATOR_TO_GOLDENIUM_ACCELERATION_FACTOR,
        speedFactor * ACCELERATOR_TO_GOLDENIUM_SPEED_FACTOR);

    goldeniumFront_to_weighingMachineFront_Path = addNavigationPathWithColor(teamColor,
        navigation,
        goldeniumFrontLocation,
        weighingMachineFrontLocation,
        GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_COST,
        GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_CP1,
        GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_CP2,
        deciDegreeToRad(GOLDENIUM_FRONT_ANGLE_DECI_DEG),
        deciDegreeToRad(WEIGHING_MACHINE_FRONT_FROM_GOLDENIUM_ANGLE_DECI_DEG),
        aFactor * GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_ACCELERATION_FACTOR,
        speedFactor * GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_SPEED_FACTOR);

    weighingMachineFront_to_weighingMachineDrop_Path = addNavigationPathWithColor(teamColor,
        navigation,
        weighingMachineFrontLocation,
        weighingMachineDropLocation,
        WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_COST,
        WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_CP1,
        WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_CP2,
        deciDegreeToRad(WEIGHING_MACHINE_FRONT_TO_DROP_ANGLE_DECI_DEG),
        deciDegreeToRad(WEIGHING_MACHINE_DROP_ANGLE_DECI_DEG),
        aFactor * WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_ACCELERATION_FACTOR,
        speedFactor * WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_SPEED_FACTOR);

    // Weighing Machine -> Small Distributor 1

    weighingMachineDrop_to_bluiumRight_Path = addNavigationPathWithColor(teamColor,
        navigation,
        weighingMachineDropLocation,
        blueiumRightLocation,
        WEIGHING_MACHINE_TO_BLUEIUM_RIGHT_COST,
        WEIGHING_MACHINE_TO_BLUEIUM_RIGHT_CP1,
        WEIGHING_MACHINE_TO_BLUEIUM_RIGHT_CP2,
        deciDegreeToRad(WEIGHING_MACHINE_DROP_ANGLE_DECI_DEG),
        deciDegreeToRad(BLUEIUM_RIGHT_ANGLE_FROM_DECI_DEG),
        aFactor * WEIGHING_MACHINE_TO_BLUEIUM_RIGHT_ACCELERATION_FACTOR,
        speedFactor * WEIGHING_MACHINE_TO_BLUEIUM_RIGHT_SPEED_FACTOR);


    bluiumRight_to_smallDistributor_Path = addNavigationPathWithColor(teamColor,
        navigation,
        blueiumRightLocation,
        smallDistributorLine1Location,
        BLUEIUM_RIGHT_TO_SMALL_DISTRIBUTOR_LINE_1_COST,
        BLUEIUM_RIGHT_TO_SMALL_DISTRIBUTOR_LINE_1_CP1,
        BLUEIUM_RIGHT_TO_SMALL_DISTRIBUTOR_LINE_1_CP2,
        deciDegreeToRad(BLUEIUM_RIGHT_ANGLE_TO_DECI_DEG),
        deciDegreeToRad(SMALL_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG),
        aFactor * BLUEIUM_RIGHT_TO_SMALL_DISTRIBUTOR_LINE_1_ACCELERATION_FACTOR,
        speedFactor * BLUEIUM_RIGHT_TO_SMALL_DISTRIBUTOR_LINE_1_SPEED_FACTOR);

    // Small Distributor 1 -> Weighing Machine
    smallDistributor_to_bluiumRight_Path = addNavigationPathWithColor(teamColor,
        navigation,
        smallDistributorLine1Location,
        blueiumRightLocation,
        SMALL_DISTRIBUTOR_LINE_1_TO_BLUEIUM_RIGHT_COST,
        SMALL_DISTRIBUTOR_LINE_1_TO_BLUEIUM_RIGHT_CP1,
        SMALL_DISTRIBUTOR_LINE_1_TO_BLUEIUM_RIGHT_CP2,
        deciDegreeToRad(BLUEIUM_RIGHT_ANGLE_TO_DECI_DEG),
        deciDegreeToRad(SMALL_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG),
        aFactor * SMALL_DISTRIBUTOR_LINE_1_TO_BLUEIUM_RIGHT_ACCELERATION_FACTOR,
        speedFactor * SMALL_DISTRIBUTOR_LINE_1_TO_BLUEIUM_RIGHT_SPEED_FACTOR);

    bluiumRight_to_weighingMachineDrop_Path = addNavigationPathWithColor(teamColor,
        navigation,
        blueiumRightLocation,
        weighingMachineDropLocation,
        BLUEIUM_RIGHT_TO_WEIGHING_MACHINE_COST,
        BLUEIUM_RIGHT_TO_WEIGHING_MACHINE_CP1,
        BLUEIUM_RIGHT_TO_WEIGHING_MACHINE_CP2,
        deciDegreeToRad(BLUEIUM_RIGHT_ANGLE_FROM_DECI_DEG),
        deciDegreeToRad(WEIGHING_MACHINE_DROP_ANGLE_DECI_DEG),
        aFactor * BLUEIUM_RIGHT_TO_WEIGHING_MACHINE_ACCELERATION_FACTOR,
        speedFactor * BLUEIUM_RIGHT_TO_WEIGHING_MACHINE_SPEED_FACTOR);

}

void initSmallRobotTargets2019(GameStrategyContext* gameStrategyContext) {
    clearGameTargets();
    gameStrategyContext->endMatch->scoreToShow += SCORE_POINT_2019_EXPERIENCE_READY;
    addGameTarget(&acceleratorTarget, "ACC_TARGET", SCORE_POINT_2019_EXPERIENCE_ACTIVATED_AND_OK + SCORE_POINT_2019_LAUNCH_BLUIUM_IN_ACCELERATOR, acceleratorFrontLocation, acceleratorFrontLocation);
    addGameTarget(&goldeniumTakeTarget, "GOLD_TAKE_TARGET", SCORE_POINT_2019_EXTRACT_GOLDENIUM, goldeniumFrontLocation, goldeniumFrontLocation);
    addGameTarget(&goldeniumDropTarget, "GOLD_DROP_TARGET", SCORE_POINT_2019_WEIGHING_MACHINE_GOLDENIUM, weighingMachineDropLocation, weighingMachineDropLocation);
    // TODO : SCORE_POINT_2019_ADD_ATOM_ACCELERATOR is false
    addGameTarget(&smallDistributorLine1Target, "SMALL_DIST_1_TARGET", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR, smallDistributorLine1Location, weighingMachineDropLocation);
}

void initSmallRobotTargetActions2019(GameStrategyContext* gameStrategyContext) {
    // ACCELERATOR TARGET
    addTargetPrepareAction(&(acceleratorTarget.actionList), &acceleratorPrepareTargetAction, smallRobotStartAreaLocation, ACCELERATOR_ARM_ON_ACTION_TIME_TO_ACHIEVE, &acceleratorPrepareTargetActionItemList);
    addTargetDropAction(&(acceleratorTarget.actionList), &acceleratorDropTargetAction, acceleratorFrontLocation, ACCELERATOR_ARM_OFF_ACTION_TIME_TO_ACHIEVE, &acceleratorDropTargetActionItemList);

    // GOLDENIUM TAKE TARGET
    addTargetPrepareAction(&(goldeniumTakeTarget.actionList), &goldeniumPrepareTakeTargetAction, acceleratorFrontLocation, GOLDENIUM_PREPARE_TAKE_TIME_TO_ACHIEVE, &goldeniumPrepareTakeTargetActionItemList);
    addTargetDropAction(&(goldeniumTakeTarget.actionList), &goldeniumTakeTargetAction, goldeniumFrontLocation, GOLDENIUM_TAKE_TIME_TO_ACHIEVE, &goldeniumTakeTargetActionItemList);

    // GOLDENIUM DROP TARGET
    addTargetPrepareAction(&(goldeniumDropTarget.actionList), &goldeniumPrepareDropTargetAction, weighingMachineFrontLocation, GOLDENIUM_PREPARE_DROP_TIME_TO_ACHIEVE, &goldeniumPrepareDropTargetActionItemList);
    addTargetDropAction(&(goldeniumDropTarget.actionList), &goldeniumDropTargetAction, weighingMachineDropLocation, GOLDENIUM_DROP_TIME_TO_ACHIEVE, &goldeniumDropTargetActionItemList);

    // SMALL DISTRIBUTOR LINE 1 TARGET
    addTargetPrepareAction(&(smallDistributorLine1Target.actionList), &smallDistributorLine1PrepareTargetAction, blueiumRightLocation, SMALL_DISTRIBUTOR_LINE_1_PREPARE_TIME_TO_ACHIEVE, &smallDistributorLine1PrepareTargetActionItemList);
    addTargetTakeAction(&(smallDistributorLine1Target.actionList), &smallDistributorLine1TakeTargetAction, smallDistributorLine1Location, SMALL_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE, &smallDistributorLine1TakeTargetActionItemList);
    addTargetDropAction(&(smallDistributorLine1Target.actionList), &smallDistributorLine1DropTargetAction, weighingMachineDropLocation, SMALL_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE, &smallDistributorLine1DropTargetActionItemList);
}

void initSmallRobotTargetActionsItems2019(GameStrategyContext* gameStrategyContext) {
    // Accelerator => We remove the arm when reaching the drop (drop is done by the move of the robot)
    addTargetActionItem(&acceleratorPrepareTargetActionItemList, &acceleratorPrepareTargetActionItem, &acceleratorArmOn, "ACC ARM ON");
    addTargetActionItem(&acceleratorDropTargetActionItemList, &acceleratorRotationTargetActionItem, &acceleratorRotationIfNeeded, "ROTATION");
    // We don't activate it for most Strategies
    acceleratorRotationTargetActionItem.enabled = false;

    addTargetActionItem(&acceleratorDropTargetActionItemList, &acceleratorDropTargetActionItem, &acceleratorArmOff, "ACC ARM Off");

    // Goldenium Take
    addTargetActionItem(&goldeniumPrepareTakeTargetActionItemList, &goldeniumPrepareTakeTargetActionItem, &goldeniumPrepareTake, "PREP GOLD TAKE");
    addTargetActionItem(&goldeniumTakeTargetActionItemList, &goldeniumTakeTargetActionItem, &goldeniumTake, "GOLD TAKE");

    // Goldenium Drop
    addTargetActionItem(&goldeniumPrepareDropTargetActionItemList, &goldeniumPrepareDropTargetActionItem, &goldeniumPrepareDrop, "GOLD PREP DROP");
    addTargetActionItem(&goldeniumDropTargetActionItemList, &goldeniumDropTargetActionItem, &goldeniumDrop, "GOLD DROP");

    // Small Distributor Line 1 Target
    addTargetActionItem(&smallDistributorLine1PrepareTargetActionItemList, &smallDistributorLine1PrepareTargetActionItem, &smallDistributorLinePrepare, "SMALL DIST PREP");
    addTargetActionItem(&smallDistributorLine1TakeTargetActionItemList, &smallDistributorLine1TakeTargetActionItem, &smallDistributorLineTake, "SMALL DIST TAKE");
    addTargetActionItem(&smallDistributorLine1DropTargetActionItemList, &smallDistributorLine1DropTargetActionItem, &smallDistributorAcceleratorDrop, "SMALL DIST DROP");
}

GameStrategy* initSmallRobotStrategiesItems2019(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    if (strategyId == SMALL_ROBOT_STRATEGY_1_ACCELERATOR) {
        addGameStrategyItem(&smallRobotStrategy1Accelerator, &acceleratorStrategyItem, &acceleratorTarget);
        return &smallRobotStrategy1Accelerator;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_2_ACCELERATOR_TAKE_GOLDENIUM) {
        addGameStrategyItem(&smallRobotStrategy2AcceleratorTakeGoldenium, &acceleratorStrategyItem, &acceleratorTarget);
        addGameStrategyItem(&smallRobotStrategy2AcceleratorTakeGoldenium, &takeGoldeniumStrategyItem, &goldeniumTakeTarget);
        return &smallRobotStrategy2AcceleratorTakeGoldenium;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_3_ACCELERATOR_TAKE_DROP_GOLDENIUM) {
        addGameStrategyItem(&smallRobotStrategy3AcceleratorTakeDropGoldenium, &acceleratorStrategyItem, &acceleratorTarget);
        addGameStrategyItem(&smallRobotStrategy3AcceleratorTakeDropGoldenium, &takeGoldeniumStrategyItem, &goldeniumTakeTarget);
        addGameStrategyItem(&smallRobotStrategy3AcceleratorTakeDropGoldenium, &dropGoldeniumStrategyItem, &goldeniumDropTarget);
        return &smallRobotStrategy3AcceleratorTakeDropGoldenium;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_4_ACCELERATOR_TAKE_DROP_GOLDENIUM_SMALL_DIST) {
        addGameStrategyItem(&smallRobotStrategy4AcceleratorTakeDropGoldeniumSmallDist, &acceleratorStrategyItem, &acceleratorTarget);
        addGameStrategyItem(&smallRobotStrategy4AcceleratorTakeDropGoldeniumSmallDist, &takeGoldeniumStrategyItem, &goldeniumTakeTarget);
        addGameStrategyItem(&smallRobotStrategy4AcceleratorTakeDropGoldeniumSmallDist, &dropGoldeniumStrategyItem, &goldeniumDropTarget);
        addGameStrategyItem(&smallRobotStrategy4AcceleratorTakeDropGoldeniumSmallDist, &smallDistributorLine1StrategyItem, &smallDistributorLine1Target);
        return &smallRobotStrategy4AcceleratorTakeDropGoldeniumSmallDist;
    }
    else if (strategyId == SMALL_ROBOT_STRATEGY_5_ACCELERATOR_CENTER_GOLDENIUM_SMALL_DIST) {
        Navigation* navigation = gameStrategyContext->navigation;
        PathData* path = getPathOfLocations(navigation->paths, smallRobotStartAreaLocation, acceleratorFrontLocation);
        path->cost = 3000.0f;
        acceleratorRotationTargetActionItem.enabled = true;
        addGameStrategyItem(&smallRobotStrategy5AcceleratorCenteredTakeDropGoldeniumSmallDist, &acceleratorStrategyItem, &acceleratorTarget);
        addGameStrategyItem(&smallRobotStrategy5AcceleratorCenteredTakeDropGoldeniumSmallDist, &takeGoldeniumStrategyItem, &goldeniumTakeTarget);
        addGameStrategyItem(&smallRobotStrategy5AcceleratorCenteredTakeDropGoldeniumSmallDist, &dropGoldeniumStrategyItem, &goldeniumDropTarget);
        addGameStrategyItem(&smallRobotStrategy5AcceleratorCenteredTakeDropGoldeniumSmallDist, &smallDistributorLine1StrategyItem, &smallDistributorLine1Target);
        return &smallRobotStrategy5AcceleratorCenteredTakeDropGoldeniumSmallDist;
    }
    writeError(STRATEGY_NOT_DEFINED);
    return NULL;
}

void initSmallRobotStrategies2019(GameStrategyContext* gameStrategyContext) {
    clearGameStrategies();

    addGameStrategy(&smallRobotStrategy1Accelerator, SMALL_ROBOT_STRATEGY_1_ACCELERATOR, "ACCELERATOR");
    addGameStrategy(&smallRobotStrategy2AcceleratorTakeGoldenium, SMALL_ROBOT_STRATEGY_2_ACCELERATOR_TAKE_GOLDENIUM, "ACC / TAKE GOLD");
    addGameStrategy(&smallRobotStrategy3AcceleratorTakeDropGoldenium, SMALL_ROBOT_STRATEGY_3_ACCELERATOR_TAKE_DROP_GOLDENIUM, "ACC / TAKE DROP GOLD");
}