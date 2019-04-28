#include <stdlib.h>

#include "strategy2019.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../common/pwm/servo/servoList.h"

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

#include "../../robot/2019/forkDevice2019.h"

// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points

// -> Small Robot
static Location* smallRobotStartAreaLocation;
static Location* acceleratorFrontLocation;
static Location* goldeniumFrontLocation;
static Location* weighingMachineFrontLocation;
static Location* weighingMachineDropLocation;

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

// Small Robot
PathData* smallRobotStartArea_to_accelerator_Path;
PathData* acceleratorFront_to_goldeniumFront_Path;
PathData* goldeniumFront_to_weighingMachineFront_Path;
PathData* weighingMachineFront_to_weighingMachineDrop_Path;



// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List
static GameTarget acceleratorTarget;
static GameTarget goldeniumTakeTarget;
static GameTarget goldeniumDropTarget;
static GameTarget chaosTarget;
static GameTarget bigDistributorLine1Target;
static GameTarget bigDistributorLine2Target;
static GameTarget bigDistributorLine3Target;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

static GameTargetAction acceleratorTargetAction;

static GameTargetAction goldeniumTakeTargetAction;
static GameTargetAction goldeniumDropTargetAction;

static GameTargetAction chaosTakeTargetAction;
static GameTargetAction chaosDropTargetAction;

static GameTargetAction bigDistributorLine1TakeTargetAction;
static GameTargetAction bigDistributorLine1MoveTargetAction1;
static GameTargetAction bigDistributorLine1MoveTargetAction2;
static GameTargetAction bigDistributorLine1DropTargetAction;

static GameTargetAction bigDistributorLine2TakeTargetAction;
static GameTargetAction bigDistributorLine2MoveTargetAction1;
static GameTargetAction bigDistributorLine2MoveTargetAction2;
static GameTargetAction bigDistributorLine2DropTargetAction;

static GameTargetAction bigDistributorLine3TakeTargetAction;
static GameTargetAction bigDistributorLine3MoveTargetAction1;
static GameTargetAction bigDistributorLine3MoveTargetAction2;
static GameTargetAction bigDistributorLine3DropTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

// Small Robot
static GameTargetActionItemList acceleratorTargetActionItemList;

static GameTargetActionItemList goldeniumTakeTargetActionItemList;
static GameTargetActionItemList goldeniumDropTargetActionItemList;

// Big Robot
static GameTargetActionItemList chaosTakeTargetActionItemList;

static GameTargetActionItemList bigDistributorLine1PrepareTargetActionItemList;
static GameTargetActionItemList bigDistributorLine1TakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine1DropTargetActionItemList;

static GameTargetActionItemList bigDistributorLine2PrepareTargetActionItemList;
static GameTargetActionItemList bigDistributorLine2TakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine2DropTargetActionItemList;

static GameTargetActionItemList bigDistributorLine3PrepareTargetActionItemList;
static GameTargetActionItemList bigDistributorLine3TakeTargetActionItemList;
static GameTargetActionItemList bigDistributorLine3DropTargetActionItemList;

// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

// Small Robot
static GameTargetActionItem acceleratorTargetActionItem;

static GameTargetActionItem goldeniumPrepareTakeTargetActionItem;
static GameTargetActionItem goldeniumTakeTargetActionItem;

// Big Robot
static GameTargetActionItem goldeniumPrepareDropTargetActionItem;
static GameTargetActionItem goldeniumDropTargetActionItem;

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

// SMALL ROBOT
static GameStrategy smallRobotStrategy1Accelerator;
static GameStrategy smallRobotStrategy2AcceleratorTakeGoldenium;
static GameStrategy smallRobotStrategy3AcceleratorTakeDropGoldenium;

// BIG ROBOT
static GameStrategy bigRobotStrategy1Chaos;
static GameStrategy bigRobotStrategy2BigDistributorLine1;
static GameStrategy bigRobotStrategy3BigDistributorLine123;
static GameStrategy bigRobotStrategy4ChaosBigDistributorLine123;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items
static GameStrategyItem acceleratorStrategyItem;
static GameStrategyItem takeGoldeniumStrategyItem;
static GameStrategyItem dropGoldeniumStrategyItem;

static GameStrategyItem chaosStrategyItem;
static GameStrategyItem bigDistributorLine1StrategyItem;
static GameStrategyItem bigDistributorLine2StrategyItem;
static GameStrategyItem bigDistributorLine3StrategyItem;

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
    float angleDeciDegree = 0;
    enum RobotType robotType = robotConfig->robotType;
    if (robotType == ROBOT_TYPE_BIG) {
        gameStrategyContext->robotPosition->x = BIG_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = BIG_ROBOT_START_AREA_Y;
        angleDeciDegree = BIG_ROBOT_START_AREA_ANGLE_DECI_DEG;
    }
    else if (robotType == ROBOT_TYPE_SMALL) {
        gameStrategyContext->robotPosition->x = SMALL_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = SMALL_ROBOT_START_AREA_Y;
        angleDeciDegree = SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG;
    }
    // Symetry
	if (isViolet(gameStrategyContext)) {
        angleDeciDegree += (float) ANGLE_DECI_DEG_180;
        gameStrategyContext->robotPosition->y = GAMEBOARD_HEIGHT - gameStrategyContext->robotPosition->y;
	}
    float angleRadian = mod2PI(deciDegreeToRad(angleDeciDegree));
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
        chaosFrontLocation = addNavigationWithColors(teamColor, navigation, CHAOS_ZONE_FRONT, CHAOS_ZONE_FRONT_X, CHAOS_ZONE_FRONT_Y);
        rediumDropZoneLocation = addNavigationWithColors(teamColor, navigation, REDIUM_DROP_ZONE, REDIUM_DROP_ZONE_X, REDIUM_DROP_ZONE_Y);
        acceleratorDropLocation = addNavigationWithColors(teamColor, navigation, ACCELERATOR_DROP, ACCELERATOR_DROP_X, ACCELERATOR_DROP_Y);
        keyPoint1Location = addNavigationWithColors(teamColor, navigation, KEY_POINT_1, KEY_POINT_1_X, KEY_POINT_1_Y);
        keyPoint2Location = addNavigationWithColors(teamColor, navigation, KEY_POINT_2, KEY_POINT_2_X, KEY_POINT_2_Y);
        bigDistributorLine1FrontLocation = addNavigationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_1, BIG_DISTRIBUTOR_LINE_1_X, BIG_DISTRIBUTOR_LINE_1_Y);
        bigDistributorLine2FrontLocation = addNavigationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_2, BIG_DISTRIBUTOR_LINE_2_X, BIG_DISTRIBUTOR_LINE_2_Y);
        bigDistributorLine3FrontLocation = addNavigationWithColors(teamColor, navigation, BIG_DISTRIBUTOR_LINE_3, BIG_DISTRIBUTOR_LINE_3_X, BIG_DISTRIBUTOR_LINE_3_Y);
    }
    else if (robotType == ROBOT_TYPE_SMALL) {
        smallRobotStartAreaLocation = addNavigationWithColors(teamColor, navigation, SMALL_ROBOT_START_AREA, SMALL_ROBOT_START_AREA_X, SMALL_ROBOT_START_AREA_Y);
        acceleratorFrontLocation = addNavigationWithColors(teamColor, navigation, ACCELERATOR_FRONT, ACCELERATOR_FRONT_X, ACCELERATOR_FRONT_Y);
        goldeniumFrontLocation = addNavigationWithColors(teamColor, navigation, GOLDENIUM_FRONT, GOLDENIUM_FRONT_X, GOLDENIUM_FRONT_Y);
        weighingMachineFrontLocation = addNavigationWithColors(teamColor, navigation, WEIGHING_MACHINE_FRONT, WEIGHING_MACHINE_FRONT_X, WEIGHING_MACHINE_FRONT_Y);
        weighingMachineDropLocation = addNavigationWithColors(teamColor, navigation, WEIGHING_MACHINE_DROP, WEIGHING_MACHINE_DROP_X, WEIGHING_MACHINE_DROP_Y);
    }
    else {
        writeError(ROBOT_TYPE_UNKNOWN_ERROR);
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

void initPaths2019(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum TeamColor teamColor = gameStrategyContext->color;
    float aFactor = gameStrategyContext->defaultAccelerationFactor;
    float speedFactor = gameStrategyContext->defaultSpeedFactor;

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
                                                    deciDegreeToRad(WEIGHING_MACHINE_FRONT_ANGLE_DECI_DEG),
                                                    aFactor * GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_ACCELERATION_FACTOR,
                                                    speedFactor * GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_SPEED_FACTOR);

        weighingMachineFront_to_weighingMachineDrop_Path = addNavigationPathWithColor(teamColor,
                                                    navigation,
                                                    weighingMachineFrontLocation,
                                                    weighingMachineDropLocation,
                                                    WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_COST,
                                                    WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_CP1,
                                                    WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_CP2,
                                                    deciDegreeToRad(WEIGHING_MACHINE_FRONT_ANGLE_DECI_DEG),
                                                    deciDegreeToRad(WEIGHING_MACHINE_DROP_ANGLE_DECI_DEG),
                                                    aFactor * WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_ACCELERATION_FACTOR,
                                                    speedFactor * WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_SPEED_FACTOR);
    }
    else if (robotType == ROBOT_TYPE_BIG) {
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
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
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
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
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
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
                                                aFactor * BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR,
                                                speedFactor * BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_SPEED_FACTOR);

        keyPoint1_to_acceleratorDrop = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                keyPoint1Location,
                                                acceleratorDropLocation,
                                                KEY_POINT_1_TO_ACCELERATOR_DROP_COST,
                                                KEY_POINT_1_TO_ACCELERATOR_DROP_CP1,
                                                KEY_POINT_1_TO_ACCELERATOR_DROP_CP2,
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
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
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
                                                aFactor * ACCELERATOR_DROP_TO_KEY_POINT_1_ACCELERATION_FACTOR,
                                                speedFactor * ACCELERATOR_DROP_TO_KEY_POINT_1_SPEED_FACTOR);
    

        keyPoint1_to_bigDistributorLine2Front = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                keyPoint1Location,
                                                bigDistributorLine2FrontLocation,
                                                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_COST,
                                                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_CP1,
                                                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_CP2,
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
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
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
                                                aFactor * BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR,
                                                speedFactor * BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_SPEED_FACTOR);
    
        keyPoint1_to_bigDistributorLine3Front = addNavigationPathWithColor(teamColor,
                                                navigation,
                                                keyPoint1Location,
                                                bigDistributorLine3FrontLocation,
                                                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_COST,
                                                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_CP1,
                                                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_CP2,
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
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
                                                deciDegreeToRad(KEY_POINT_1_ANGLE_DECI_DEG),
                                                aFactor * BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR,
                                                speedFactor * BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_SPEED_FACTOR);
    }
}

void initTargets2019(GameStrategyContext* gameStrategyContext) {
	clearGameTargets();

    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum RobotType robotType = robotConfig->robotType;
    if (robotType == ROBOT_TYPE_BIG) {
        addGameTarget(&chaosTarget, "CHAOS_TARGET", SCORE_POINT_2019_CHAOS_5_PUNK, chaosFrontLocation, rediumDropZoneLocation);
        addGameTarget(&bigDistributorLine1Target, "BIG DIST 1", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR * 2, bigDistributorLine1FrontLocation, acceleratorDropLocation);
        addGameTarget(&bigDistributorLine2Target, "BIG DIST 2", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR * 2, bigDistributorLine2FrontLocation, acceleratorDropLocation);
        addGameTarget(&bigDistributorLine3Target, "BIG DIST 3", SCORE_POINT_2019_ADD_ATOM_ACCELERATOR * 2, bigDistributorLine3FrontLocation, acceleratorDropLocation);
    }
    else if (robotType == ROBOT_TYPE_SMALL) {
        addGameTarget(&acceleratorTarget, "ACC_TARGET", SCORE_POINT_2019_LAUNCH_BLUIUM_IN_ACCELERATOR, acceleratorFrontLocation, acceleratorFrontLocation);
        addGameTarget(&goldeniumTakeTarget, "GOLD_TAKE_TARGET", SCORE_POINT_2019_EXTRACT_GOLDENIUM, goldeniumFrontLocation, goldeniumFrontLocation);
        addGameTarget(&goldeniumDropTarget, "GOLD_DROP_TARGET", SCORE_POINT_2019_WEIGHING_MACHINE_GOLDENIUM, weighingMachineFrontLocation, weighingMachineFrontLocation);
    }
}

void initTargetActions2019(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    if (robotConfig->robotType == ROBOT_TYPE_SMALL) {
        // ACCELERATOR TARGET
        addTargetDropAction(&(acceleratorTarget.actionList), &acceleratorTargetAction, acceleratorFrontLocation, ACCELERATOR_ACTION_TIME_TO_ACHIEVE, &acceleratorTargetActionItemList);
        // GOLDENIUM TAKE TARGET
        addTargetHandlingAction(&(goldeniumTakeTarget.actionList), &goldeniumTakeTargetAction, goldeniumFrontLocation, GOLDENIUM_TAKE_TIME_TO_ACHIEVE, &goldeniumTakeTargetActionItemList);
        // GOLDENIUM DROP TARGET
        addTargetDropAction(&(goldeniumDropTarget.actionList), &goldeniumDropTargetAction, weighingMachineFrontLocation, GOLDENIUM_DROP_TIME_TO_ACHIEVE, &goldeniumDropTargetActionItemList);
    }
    else if (robotConfig->robotType == ROBOT_TYPE_BIG) {
        // CHAOS
        addTargetPrepareAction(&(chaosTarget.actionList), &chaosTakeTargetAction, chaosFrontLocation, CHAOS_TAKE_TIME_TO_ACHIEVE, &chaosTakeTargetActionItemList);
        addTargetMoveAction(&(chaosTarget.actionList), &chaosDropTargetAction, chaosFrontLocation, rediumDropZoneLocation, CHAOS_DROP_TIME_TO_ACHIEVE);
        
        // BIG DISTRIBUTOR LINE 1
        addTargetHandlingAction(&(bigDistributorLine1Target.actionList), &bigDistributorLine1TakeTargetAction, bigDistributorLine1FrontLocation, BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine1TakeTargetActionItemList);
        addTargetMoveAction(&(bigDistributorLine1Target.actionList), &bigDistributorLine1MoveTargetAction1, bigDistributorLine1FrontLocation, keyPoint1Location, BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE);
        addTargetMoveAction(&(bigDistributorLine1Target.actionList), &bigDistributorLine1MoveTargetAction2, keyPoint1Location, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE);
        addTargetDropAction(&(bigDistributorLine1Target.actionList), &bigDistributorLine1DropTargetAction, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE, &bigDistributorLine1DropTargetActionItemList);

        // BIG DISTRIBUTOR LINE 2
        addTargetHandlingAction(&(bigDistributorLine2Target.actionList), &bigDistributorLine2TakeTargetAction, bigDistributorLine2FrontLocation, BIG_DISTRIBUTOR_LINE_2_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine2TakeTargetActionItemList);
        addTargetMoveAction(&(bigDistributorLine2Target.actionList), &bigDistributorLine2MoveTargetAction1, bigDistributorLine2FrontLocation, keyPoint1Location, BIG_DISTRIBUTOR_LINE_2_MOVE_TIME_TO_ACHIEVE);
        addTargetMoveAction(&(bigDistributorLine2Target.actionList), &bigDistributorLine2MoveTargetAction2, keyPoint1Location, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_2_MOVE_TIME_TO_ACHIEVE);
        addTargetDropAction(&(bigDistributorLine2Target.actionList), &bigDistributorLine2DropTargetAction, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_2_DROP_TIME_TO_ACHIEVE, &bigDistributorLine2DropTargetActionItemList);

        // BIG DISTRIBUTOR LINE 3
        addTargetHandlingAction(&(bigDistributorLine3Target.actionList), &bigDistributorLine3TakeTargetAction, bigDistributorLine3FrontLocation, BIG_DISTRIBUTOR_LINE_3_TAKE_TIME_TO_ACHIEVE, &bigDistributorLine3TakeTargetActionItemList);
        addTargetMoveAction(&(bigDistributorLine3Target.actionList), &bigDistributorLine3MoveTargetAction1, bigDistributorLine2FrontLocation, keyPoint1Location, BIG_DISTRIBUTOR_LINE_3_MOVE_TIME_TO_ACHIEVE);
        addTargetMoveAction(&(bigDistributorLine3Target.actionList), &bigDistributorLine3MoveTargetAction2, keyPoint1Location, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_2_MOVE_TIME_TO_ACHIEVE);
        addTargetDropAction(&(bigDistributorLine3Target.actionList), &bigDistributorLine3DropTargetAction, acceleratorDropLocation, BIG_DISTRIBUTOR_LINE_3_DROP_TIME_TO_ACHIEVE, &bigDistributorLine3DropTargetActionItemList);
    }
}

bool acceleratorArmOn(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "Accelerator Arm On");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;

    if (isViolet(gameStrategyContext)) {
        // Right Arm
        arm2019On(2);
        
    }
    else {
        // Left Arm
        arm2019On(1);
    }
    // TODO
    return true;
}

bool acceleratorArmOff(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "Accelerator Arm Off");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;

    if (isViolet(gameStrategyContext)) {
        // Right Arm
        arm2019Off(2);
        
    }
    else {
        // Left Arm
        arm2019Off(1);
    }
    // TODO
    return true;
}

bool goldeniumPrepareTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "goldeniumPrepareTake");
    moveElevatorDoublePuck();
    return true;
}

bool goldeniumTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "goldeniumTake");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;

    if (isViolet(gameStrategyContext)) {
        forkScanFromLeftToRight();
        moveForkDoublePuck(2);
    }
    else {
        forkScanFromRightToLeft();
        moveForkDoublePuck(1);
    }
    
    moveElevatorUp();
    
    return true;
}

bool goldeniumDrop(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "goldeniumDrop");
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    if (isViolet(gameStrategyContext)) {
        moveForkPushOff(2);
    }
    else {
        moveForkPushOff(1);
    }
    return true;
}

bool bigDistributorLinePrepare(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "bigDistributorLinePrepare");
    // TODO
    return true;
}

bool bigDistributorLineTake(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "bigDistributorLineTake");
    // TODO
    return true;
}

bool acceleratorDrop(int* context) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "acceleratorDrop");
    // TODO
    return true;
}


void initTargetActionsItems2019(GameStrategyContext* gameStrategyContext) {
    // Accelerator
    addTargetActionItem(&acceleratorTargetActionItemList, &acceleratorTargetActionItem, &acceleratorArmOn, "ACC ARM ON");
    
    // Goldenium Take
    addTargetActionItem(&goldeniumTakeTargetActionItemList, &goldeniumPrepareTakeTargetActionItem, &goldeniumPrepareTake, "PREP GOLD TAKE");
    addTargetActionItem(&goldeniumTakeTargetActionItemList, &goldeniumTakeTargetActionItem, &goldeniumTake, "GOLD TAKE");
   
    // Goldenium Drop
    addTargetActionItem(&goldeniumDropTargetActionItemList, &goldeniumPrepareDropTargetActionItem, &goldeniumDrop, "PREP GOLD DROP");
    addTargetActionItem(&goldeniumDropTargetActionItemList, &goldeniumDropTargetActionItem, &goldeniumDrop, "GOLD DROP");
    
    // Chaos : No specific action to do
    
    // Big Distributor 1 Line 1
    addTargetActionItem(&bigDistributorLine1PrepareTargetActionItemList, &bigDistributorLine1PrepareTargetActionItem, &bigDistributorLinePrepare, "PREP DIST 1");
    addTargetActionItem(&bigDistributorLine1TakeTargetActionItemList, &bigDistributorLine1TakeTargetActionItem, &bigDistributorLineTake, "TAKE DIST 1");
    addTargetActionItem(&bigDistributorLine1DropTargetActionItemList, &bigDistributorLine1DropTargetActionItem, &acceleratorDrop, "ACC DROP");

    // Big Distributor 1 Line 2
    addTargetActionItem(&bigDistributorLine2PrepareTargetActionItemList, &bigDistributorLine2PrepareTargetActionItem, &bigDistributorLinePrepare, "PREP DIST 3");
    addTargetActionItem(&bigDistributorLine2TakeTargetActionItemList, &bigDistributorLine2TakeTargetActionItem, &bigDistributorLineTake, "TAKE DIST 3");
    addTargetActionItem(&bigDistributorLine2DropTargetActionItemList, &bigDistributorLine2DropTargetActionItem, &acceleratorDrop, "ACC DROP");

    // Big Distributor 1 Line 3
    addTargetActionItem(&bigDistributorLine3PrepareTargetActionItemList, &bigDistributorLine3PrepareTargetActionItem, &bigDistributorLinePrepare, "PREP DIST 3");
    addTargetActionItem(&bigDistributorLine3TakeTargetActionItemList, &bigDistributorLine3TakeTargetActionItem, &bigDistributorLineTake, "TAKE DIST 3");
    addTargetActionItem(&bigDistributorLine3DropTargetActionItemList, &bigDistributorLine3DropTargetActionItem, &acceleratorDrop, "ACC DROP");
}

/**
* @private.
*/
void initStrategies2019(GameStrategyContext* gameStrategyContext) {
	clearGameStrategies();
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum RobotType robotType = robotConfig->robotType;

    if (robotType == ROBOT_TYPE_SMALL) {
        addGameStrategy(&smallRobotStrategy1Accelerator, SMALL_ROBOT_STRATEGY_1_ACCELERATOR,  "ACCELERATOR");
        addGameStrategy(&smallRobotStrategy2AcceleratorTakeGoldenium, SMALL_ROBOT_STRATEGY_2_ACCELERATOR_TAKE_GOLDENIUM, "ACC / TAKE GOLD");
        addGameStrategy(&smallRobotStrategy3AcceleratorTakeDropGoldenium, SMALL_ROBOT_STRATEGY_3_ACCELERATOR_TAKE_DROP_GOLDENIUM, "ACC / TAKE DROP GOLD");
    }
    else if (robotType == ROBOT_TYPE_BIG) {
        addGameStrategy(&bigRobotStrategy1Chaos, BIG_ROBOT_STRATEGY_1_CHAOS, "CHAOS");
        addGameStrategy(&bigRobotStrategy2BigDistributorLine1, BIG_ROBOT_STRATEGY_2_BIG_DISTRIBUTOR_LINE_1, "DIST 1");
        addGameStrategy(&bigRobotStrategy3BigDistributorLine123, BIG_ROBOT_STRATEGY_3_BIG_DISTRIBUTOR_LINE_1_2_3, "DIST 123");
        addGameStrategy(&bigRobotStrategy4ChaosBigDistributorLine123, BIG_ROBOT_STRATEGY_4_CHAOS_BIG_DISTRIBUTOR_LINE_1_2_3, "CHAOS / DIST 123");
        
    }
}

GameStrategy* initStrategiesItems2019(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (strategyId == NO_STRATEGY_INDEX) {
        return NULL;
    }
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum RobotType robotType = robotConfig->robotType;
    
    if (robotType == ROBOT_TYPE_SMALL) {
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
    }
    else if (robotType == ROBOT_TYPE_BIG) {
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
        
    }
    return NULL;
}

void initStrategy2019(GameStrategyContext* gameStrategyContext) {
    initColorAndStartPosition2019(gameStrategyContext);
    float tofDistanceFactor = getSonarDistanceCheckFactor(gameStrategyContext->robotConfig);
    setTofListNameAndOrientationAngle(gameStrategyContext->tofSensorList, tofDistanceFactor);
    showGameStrategyContextTeamColorAndStrategy(gameStrategyContext);

    gameStrategyContext->defaultAccelerationFactor = getAccelerationFactor(gameStrategyContext->robotConfig);
    gameStrategyContext->defaultSpeedFactor = getSpeedFactor(gameStrategyContext->robotConfig);

	initLocations2019(gameStrategyContext);
	initPaths2019(gameStrategyContext);

	initTargets2019(gameStrategyContext);
	initTargetActions2019(gameStrategyContext);
	initTargetActionsItems2019(gameStrategyContext);

	initStrategies2019(gameStrategyContext);
	

	GameStrategy* strategy = initStrategiesItems2019(gameStrategyContext);
    gameStrategyContext->gameStrategy = strategy;

	// opponent
	Point* p = gameStrategyContext->opponentRobotPosition;
	p->x = 0;
	p->y = 0;

	// obstacle
	p = gameStrategyContext->lastObstaclePosition;
	p->x = 0;
	p->y = 0;

	// reinitialize the game board to change elements / targets ...
}
