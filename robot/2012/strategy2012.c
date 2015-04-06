#include <stdlib.h>

#include "strategy2012.h"
#include "strategy2012Utils.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../motion/motion.h"
#include "../../motion/simple/simpleMotion.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameBoard.h"


#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameTargetActionItem.h"
#include "../../robot/strategy/gameTargetActionList.h"

#include "armDeviceInterface2012.h"
#include "armDriver2012.h"

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points
static Location* startAreaLocation; 
static Location* startAreaFrontLocation;

static Location* bullion1Location;
static Location* bottle1Location;
static Location* bottle2FrontLocation;
static Location* bottle2Location;
static Location* dropZone1Location;
static Location* frontOfMapLocation;

// -> Bullion1
static Location* bullionRight1Location;
static Location* bullionLeft1Location;

// -> OpponentCD
static Location* bullionMiddle2Location;

static Location* obstacleL1Location;
static Location* obstacleL2Location;
static Location* obstacleL3Location;
static Location* obstacleL4Location;
static Location* obstacleR1Location;
static Location* obstacleR2Location;
static Location* obstacleR3Location;
static Location* obstacleR4Location;
static Location* obstacleM1Location;
static Location* obstacleM2Location;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

PathData* startAreaToBullion1Path;
PathData* bottle2ToCDPath;
PathData* cdToDropZone1Path;
PathData* dropZone1ToBullionLeft1Path;
PathData* dropZone1ToBullionRight1Path;
PathData* obstacleR3ToBullionRight1Path;
PathData* obstacleL3ToBullionLeft1Path;

PathData* bullion1ToBottle1Path;
PathData* bottle1ToBottle2FrontPath;

// OL1->OL2
PathData* obstacleL1ToObstacleL2Path;

// OL1->OL4
PathData* obstacleL1ToObstacleL4Path;
PathData* obstacleL2ToObstacleL3Path;
PathData* obstacleL3ToObstacleL4Path;

// OL4->OM2
PathData* obstacleL4ToObstacleM2Path;

// OL4->OR4
PathData* obstacleL4ToObstacleR4Path;
PathData* obstacleM2ToObstacleR4Path;

// OR4->OR3
PathData* obstacleR4ToObstacleR3Path;

// OR4->OR1
PathData* obstacleR4ToObstacleR1Path;
PathData* obstacleR3ToObstacleR2Path;
PathData* obstacleR2ToObstacleR1Path;

// OR1->OM1
PathData* obstacleR1ToObstacleM1Path;

// OR1->OL1
PathData* obstacleR1ToObstacleL1Path;

// OM1->OL1
PathData* obstacleM1ToObstacleL1Path;

// bottle1->OR1
PathData* bottle1ToObstacleR1Path;

// bottle2->OR3 : TODO : Asymetric
PathData* bottle2ToObstacleR3Path;

// dropZone1->OL1
PathData* dropZone1ToObstacleL1Path;

// dropZone1->OM1
PathData* dropZone1ToObstacleM1Path;

// dropZone1->OR1
PathData* dropZone1ToObstacleR1Path;

// bullion1->OL1
PathData* bullion1ToObstacleL1Path;

// bullion1->OM1
PathData* bullion1ToObstacleM1Path;

// bullion1->OR1
PathData* bullion1ToObstacleR1Path;

// bottle2Front->OR4
PathData* bottle2FrontToObstacleR4Path;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List
static GameTarget bullion1Target;
static GameTarget bottle1Target;
static GameTarget bottle2Target;
static GameTarget cd4Target;
static GameTarget bullionRight1Target;
static GameTarget bullionLeft1Target;
//static GameTarget opponentCDTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// -> Base target
static GameTargetAction bullion1TargetAction;
static GameTargetAction bottle1TargetAction;
static GameTargetAction bottle2TargetAction;
static GameTargetAction cdTakeTargetAction;

// -> Bullion1
static GameTargetAction bullionRight1FromDropZone1TargetAction;
static GameTargetAction bullionRight1FromR3TargetAction;

static GameTargetAction bullionLeft1FromDropZone1TargetAction;
static GameTargetAction bullionLeft1FromL3TargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEMS --------------------------------------------------------

// -> CD 4
static GameTargetActionItemList cdTakeTargetActionItemList;  
static GameTargetActionItem cdTakeStep1TargetActionItem;
static GameTargetActionItem cdTakeStep2TargetActionItem;

// -> BULLION RIGHT 1
static GameTargetActionItemList bullionRight1FromDropZone1ActionItemList; 
static GameTargetActionItemList bullionRight1FromR3ActionItemList; 
static GameTargetActionItem bullionRight1RotateTargetActionItem;
static GameTargetActionItem bullionRight1Step1FromDropZone1TargetActionItem;
static GameTargetActionItem bullionRight1Step1FromR3TargetActionItem;
static GameTargetActionItem bullionRight1Step2OpenPlierTargetActionItem;
static GameTargetActionItem bullionRight1Step3GoTargetActionItem;
static GameTargetActionItem bullionRight1Step4ClosePlierTargetActionItem;

// -> BULLION LEFT 1
static GameTargetActionItemList bullionLeft1FromDropZone1ActionItemList; 
static GameTargetActionItemList bullionLeft1FromL3ActionItemList; 
static GameTargetActionItem bullionLeft1RotateTargetActionItem;
static GameTargetActionItem bullionLeft1Step1FromDropZone1TargetActionItem;
static GameTargetActionItem bullionLeft1Step1FromL3TargetActionItem;
static GameTargetActionItem bullionLeft1Step2OpenPlierTargetActionItem;
static GameTargetActionItem bullionLeft1Step3GoTargetActionItem;
static GameTargetActionItem bullionLeft1Step4ClosePlierTargetActionItem;

// -> CD OPPONENT
// static GameTargetActionItemList opponentCDActionItemList; 

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
static GameStrategy strategy1;

// strategies Items
static GameStrategyItem takeBullionFirstStrategyItem;
static GameStrategyItem bottle1StrategyItem;
static GameStrategyItem bottle2StrategyItem;
static GameStrategyItem cdTakeStrategyItem;
static GameStrategyItem bullionRight1StrategyItem;
static GameStrategyItem bullionLeft1StrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void setColor(TEAM_COLOR color) {
    GameStrategyContext* context = getStrategyContext();

    appendStringAndDec(getInfoOutputStreamLogger(), "setColor:", color);
    println(getInfoOutputStreamLogger());

    context->color = color;
    changeLocationsForColor();
    int angle = 675;
    if (!isViolet()) {
        angle = -angle;
        context->robotPosition.y = 2840;
    }
    else {
        context->robotPosition.y = 160;
    }
    context->robotPosition.x = 160;

    context->robotAngle = angle;

    printStrategyAllDatas(getInfoOutputStreamLogger());
}

void initLocations2012() {
    clearLocationList(getNavigationLocationList());
    // -> General locations
    startAreaLocation = addNavigationLocation(START_AREA, START_AREA_X, START_AREA_Y);
    startAreaFrontLocation = addNavigationLocation(START_AREA_FRONT, START_AREA_FRONT_X, START_AREA_FRONT_Y);
    bullion1Location = addNavigationLocation(BULLION_1, BULLION_1_X, BULLION_1_Y);
    bottle1Location = addNavigationLocation(BOTTLE_1, BOTTLE_1_X, BOTTLE_1_Y);
    bottle2FrontLocation = addNavigationLocation(BOTTLE_2_FRONT, BOTTLE_2_FRONT_X, BOTTLE_2_FRONT_Y);
    bottle2Location = addNavigationLocation(BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);
//     cdTakeLocation = addNavigationLocation(CD_TAKE, CD_TAKE_X, CD_TAKE_Y);
    dropZone1Location = addNavigationLocation(DROP_ZONE_1, (int)DROP_ZONE_1_X, (int) DROP_ZONE_1_Y);
    frontOfMapLocation = addNavigationLocation(FRONT_OF_MAP_LOCATION, (int) FRONT_OF_MAP_LOCATION_X, (int)FRONT_OF_MAP_LOCATION_Y);
    // -> Bullion 1
    bullionRight1Location = addNavigationLocation(BULLION_RIGHT_1, BULLION_RIGHT_1_X, BULLION_RIGHT_1_Y); 
    bullionLeft1Location = addNavigationLocation(BULLION_LEFT_1, BULLION_LEFT_1_X, BULLION_LEFT_1_Y); 
    // -> Bullion 2 / Opponent CD
    bullionMiddle2Location = addNavigationLocation(BULLION_MIDDLE_2, (int)BULLION_MIDDLE_2_X, (int) BULLION_MIDDLE_2_Y);

    obstacleL1Location = addNavigationLocation(OBSTACLE_L1, OBSTACLE_L_X, OBSTACLE_1_Y);
    obstacleL2Location = addNavigationLocation(OBSTACLE_L2, OBSTACLE_L_X, OBSTACLE_2_Y);
    obstacleL3Location = addNavigationLocation(OBSTACLE_L3, OBSTACLE_L_X, (int) OBSTACLE_3_Y);
    obstacleL4Location = addNavigationLocation(OBSTACLE_L4, (int) OBSTACLE_L_X, (int)OBSTACLE_4_Y);
    obstacleM1Location = addNavigationLocation(OBSTACLE_M1, (int) OBSTACLE_M_X, (int)OBSTACLE_1_Y);
    obstacleM2Location = addNavigationLocation(OBSTACLE_M2, (int) OBSTACLE_M_X, (int)OBSTACLE_4_Y);
    obstacleR1Location = addNavigationLocation(OBSTACLE_R1, (int) OBSTACLE_R_X, (int) OBSTACLE_1_Y);
    obstacleR2Location = addNavigationLocation(OBSTACLE_R2, (int) OBSTACLE_R_X, (int) OBSTACLE_2_Y);
    obstacleR3Location = addNavigationLocation(OBSTACLE_R3, (int) OBSTACLE_R_X, (int) OBSTACLE_3_Y);
    obstacleR4Location = addNavigationLocation(OBSTACLE_R4, (int) OBSTACLE_R_X, (int) OBSTACLE_4_Y);
}

void initPaths2012(int index) {
    clearPathList(getNavigationPathList());

    bottle2ToCDPath = addNavigationPath(bottle2Location, obstacleR1Location, BOTTLE_2_TO_CD_COST, 0x1B, 0x30, 0xF8F8, 0xFAF6, BOTTLE_2_TO_CD_SPEED_FACTOR, BOTTLE_2_TO_CD_ACCELERATION_FACTOR);
    cdToDropZone1Path = addNavigationPath(obstacleR1Location, dropZone1Location, CD_TO_DROP_ZONE_1_COST, 0x11, 0x26, 0xFAF6, ANGLE_NEG_90, CD_TO_DROP_ZONE_1_SPEED_FACTOR, CD_TO_DROP_ZONE_1_ACCELERATION_FACTOR);
    // TODO : Replate by initAsymmetricPathData
    dropZone1ToBullionLeft1Path = addNavigationPath(dropZone1Location, bullionLeft1Location, DROP_ZONE_1_TO_BULLION_LEFT_1_COST, 0xB0, 0x80, ANGLE_NEG_90, ANGLE_NEG_90, DROP_ZONE_1_TO_BULLION_LEFT_1_SPEED_FACTOR, DROP_ZONE_1_TO_BULLION_LEFT_1_ACCELERATION_FACTOR);
    dropZone1ToBullionRight1Path = addNavigationPath(dropZone1Location, bullionRight1Location, DROP_ZONE_1_TO_BULLION_RIGHT_1_COST, 0xB0, 0x80, ANGLE_NEG_90, ANGLE_NEG_90, DROP_ZONE_1_TO_BULLION_RIGHT_1_SPEED_FACTOR, DROP_ZONE_1_TO_BULLION_RIGHT_1_ACCELERATION_FACTOR);
    obstacleR3ToBullionRight1Path = addNavigationPath(obstacleR3Location, bullionRight1Location, OR3_TO_BULLIONRIGHT1_COST, 0x0A, 0x0A, ANGLE_NEG_135, ANGLE_NEG_90, OR3_TO_BULLIONRIGHT1_SPEED_FACTOR, OR3_TO_BULLIONRIGHT1_ACCELERATION_FACTOR);
    obstacleL3ToBullionLeft1Path = addNavigationPath(obstacleL3Location, bullionLeft1Location, OL3_TO_BULLIONRIGHT1_COST, 0x0A, 0x0A, ANGLE_NEG_45, ANGLE_NEG_90, OL3_TO_BULLIONRIGHT1_SPEED_FACTOR, OL3_TO_BULLIONRIGHT1_ACCELERATION_FACTOR);


    // DIRECT PATH TO TARGETS
    if (index == STRATEGY_HOMOLOGATION) {
        #ifdef INCLUDE_HOMOLOGATION
            startAreaToStartAreaFrontPath = addNavigationPath(startAreaLocation, startAreaFrontLocation, STARTAREA_TO_STARTAREA_FRONT_COST,  0x0A, 0x0A, START_ANGLE, ANGLE_90, STARTAREA_TO_STARTAREA_FRONT_SPEED_FACTOR, STARTAREA_TO_STARTAREA_FRONT_ACCELERATION_FACTOR);
            startAreaFrontToOM1Path = addNavigationPath(startAreaFrontLocation, obstacleM1Location, STARTAREA_FRONT_TO_OM1_COST,  0x0A, 0x0A, ANGLE_0, ANGLE_0, STARTAREA_FRONT_TO_OM1_SPEED_FACTOR, STARTAREA_FRONT_TO_OM1_ACCELERATION_FACTOR); 
        #endif
    }
    else {
        startAreaToBullion1Path = addNavigationPath(startAreaLocation, bullion1Location, START_AREA_TO_BULLION_1_COST, 0x40, 0x40, START_ANGLE, ANGLE_NEG_90, START_AREA_TO_BULLION_1_SPEED_FACTOR, START_AREA_TO_BULLION_1_ACCELERATION_FACTOR);
    }

    // TODO : Asymetric
    bullion1ToBottle1Path = addNavigationPath(bullion1Location, bottle1Location, BULLION_1_TO_BOTTLE_1_COST, 0xEC, 0xC0, ANGLE_NEG_90, ANGLE_180, BULLION_1_TO_BOTTLE_1_SPEED_FACTOR, BULLION_1_TO_BOTTLE_1_ACCELERATION_FACTOR);

    bottle1ToBottle2FrontPath = addNavigationPath(bottle1Location, bottle2FrontLocation, BOTTLE_1_TO_BOTTLE_2_FRONT_COST, 0x40, 0x0A, ANGLE_180, 0x0450, BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR, BOTTLE_1_TO_BOTTLE_2_ACCELERATION_FACTOR);


    // OL1->OL2
    obstacleL1ToObstacleL2Path = addNavigationPath(obstacleL1Location, obstacleL2Location, OBSTACLE_L1_TO_L2_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L1_TO_L2_SPEED_FACTOR, OBSTACLE_L1_TO_L2_ACCELERATION_FACTOR);

    // OL1->OL4
    obstacleL1ToObstacleL4Path = addNavigationPath(obstacleL1Location, obstacleL4Location, OBSTACLE_L1_TO_L4_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L1_TO_L4_SPEED_FACTOR, OBSTACLE_L1_TO_L4_ACCELERATION_FACTOR);
    obstacleL2ToObstacleL3Path = addNavigationPath(obstacleL2Location, obstacleL3Location, OBSTACLE_L2_TO_L3_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L2_TO_L3_SPEED_FACTOR, OBSTACLE_L2_TO_L3_ACCELERATION_FACTOR);
    obstacleL3ToObstacleL4Path = addNavigationPath(obstacleL3Location, obstacleL4Location, OBSTACLE_L3_TO_L4_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L3_TO_L4_SPEED_FACTOR, OBSTACLE_L3_TO_L4_ACCELERATION_FACTOR);

    // OL4->OM2
    obstacleL4ToObstacleM2Path = addNavigationPath(obstacleL4Location, obstacleM2Location, OBSTACLE_L4_TO_M2_COST, 0x0A, 0x0A, 0, 0, OBSTACLE_L4_TO_M2_SPEED_FACTOR, OBSTACLE_L4_TO_M2_ACCELERATION_FACTOR);

    // OL4->OR4
    obstacleL4ToObstacleR4Path = addNavigationPath(obstacleL4Location, obstacleR4Location, OBSTACLE_L4_TO_R4_COST, 0x0A, 0x0A, 0, 0, OBSTACLE_L4_TO_R4_SPEED_FACTOR, OBSTACLE_L4_TO_R4_ACCELERATION_FACTOR); 
    obstacleM2ToObstacleR4Path = addNavigationPath(obstacleM2Location, obstacleR4Location, OBSTACLE_M2_TO_R4_COST, 0x0A, 0x0A, 0, 0, OBSTACLE_M2_TO_R4_SPEED_FACTOR, OBSTACLE_M2_TO_R4_ACCELERATION_FACTOR);

    // OR4->OR3
    obstacleR4ToObstacleR3Path = addNavigationPath(obstacleR4Location, obstacleR3Location, OBSTACLE_R4_TO_R3_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R4_TO_R3_SPEED_FACTOR, OBSTACLE_R4_TO_R3_ACCELERATION_FACTOR);

    // OR4->OR1
    obstacleR4ToObstacleR1Path = addNavigationPath(obstacleR4Location, obstacleR1Location, OBSTACLE_R4_TO_R1_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R4_TO_R1_SPEED_FACTOR, OBSTACLE_R4_TO_R1_ACCELERATION_FACTOR);

    obstacleR3ToObstacleR2Path = addNavigationPath(obstacleR3Location, obstacleR2Location, OBSTACLE_R3_TO_R2_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R3_TO_R2_SPEED_FACTOR, OBSTACLE_R3_TO_R2_ACCELERATION_FACTOR);

    obstacleR2ToObstacleR1Path = addNavigationPath(obstacleR2Location, obstacleR1Location, OBSTACLE_R2_TO_R1_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R2_TO_R1_SPEED_FACTOR, OBSTACLE_R2_TO_R1_ACCELERATION_FACTOR);

    // OR1->OM1
    obstacleR1ToObstacleM1Path = addNavigationPath(obstacleR1Location, obstacleM1Location, OBSTACLE_R1_TO_M1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, OBSTACLE_R1_TO_M1_SPEED_FACTOR, OBSTACLE_R1_TO_M1_ACCELERATION_FACTOR);

    // OR1->OL1
    obstacleR1ToObstacleL1Path = addNavigationPath(obstacleR1Location, obstacleL1Location, OBSTACLE_R1_TO_L1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, OBSTACLE_R1_TO_L1_SPEED_FACTOR, OBSTACLE_R1_TO_L1_ACCELERATION_FACTOR);

    // OM1->OL1
    obstacleM1ToObstacleL1Path = addNavigationPath(obstacleM1Location, obstacleL1Location, OBSTACLE_M1_TO_L1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, OBSTACLE_M1_TO_L1_SPEED_FACTOR, OBSTACLE_M1_TO_L1_ACCELERATION_FACTOR);

    // bottle1->OR1
    bottle1ToObstacleR1Path = addNavigationPath(bottle1Location, obstacleR1Location, BOTTLE1_TO_OR1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, BOTTLE1_TO_OR1_SPEED_FACTOR, BOTTLE1_TO_OR1_ACCELERATION_FACTOR);

    // bottle2->OR3 : TODO : Asymetric
    bottle2ToObstacleR3Path = addNavigationPath(bottle2Location, obstacleR3Location, BOTTLE2_TO_OR3_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, BOTTLE2_TO_OR3_SPEED_FACTOR, BOTTLE2_TO_OR3_ACCELERATION_FACTOR);

    // dropZone1->OL1
    dropZone1ToObstacleL1Path = addNavigationPath(dropZone1Location, obstacleL1Location, DROPZONE1_TO_OL1_COST, 0x19, 0x19, ANGLE_90, ANGLE_180, DROPZONE1_TO_OL1_SPEED_FACTOR, DROPZONE1_TO_OL1_ACCELERATION_FACTOR);

    // dropZone1->OM1
    dropZone1ToObstacleM1Path = addNavigationPath(dropZone1Location, obstacleM1Location, DROPZONE1_TO_OM1_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, DROPZONE1_TO_OM1_SPEED_FACTOR, DROPZONE1_TO_OM1_ACCELERATION_FACTOR);

    // dropZone1->OR1
    dropZone1ToObstacleR1Path = addNavigationPath(dropZone1Location, obstacleR1Location, DROPZONE1_TO_OR1_COST, 0x19, 0x19, ANGLE_90, 0, DROPZONE1_TO_OR1_SPEED_FACTOR, DROPZONE1_TO_OR1_ACCELERATION_FACTOR);

    // bullion1->OL1
    if (index != STRATEGY_HOMOLOGATION) {
        bullion1ToObstacleL1Path = addNavigationPath(bullion1Location, obstacleL1Location, BULLION1_TO_OL1_COST, 0x19, 0x19, ANGLE_90, ANGLE_180, BULLION1_TO_OL1_SPEED_FACTOR, BULLION1_TO_OL1_ACCELERATION_FACTOR);
    }

    // bullion1->OM1
    bullion1ToObstacleM1Path = addNavigationPath(bullion1Location, obstacleM1Location, BULLION1_TO_OM1_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, BULLION1_TO_OM1_SPEED_FACTOR, BULLION1_TO_OM1_ACCELERATION_FACTOR);

    // bullion1->OR1
    bullion1ToObstacleR1Path = addNavigationPath(bullion1Location, obstacleR1Location, BULLION1_TO_OR1_COST, 0x19, 0x19, ANGLE_90, 0, BULLION1_TO_OR1_SPEED_FACTOR, BULLION1_TO_OR1_ACCELERATION_FACTOR);

    // bottle2Front->OR4
    bottle2FrontToObstacleR4Path = addNavigationPath(bottle2FrontLocation, obstacleR4Location, BOTTLE2FRONT_TO_CD_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, BOTTLE2FRONT_TO_CD_SPEED_FACTOR, BOTTLE2FRONT_TO_CD_ACCELERATION_FACTOR);
}

void initTargets2012() {
    clearGameTargets();

    addGameTarget(&bullion1Target, BULLION_1, BULLION_GAIN, bullion1Location);
    addGameTarget(&bullionRight1Target, BULLION_RIGHT_1, BULLION_GAIN, bullionRight1Location);

    addGameTarget(&bullion1Target, BULLION_1, BULLION_GAIN, bullion1Location);
    addGameTarget(&bottle1Target, BOTTLE_1, BOTTLE_GAIN, bottle1Location);
    addGameTarget(&bottle2Target, BOTTLE_2, BOTTLE_GAIN, bottle2Location);
    addGameTarget(&cd4Target, CD_TAKE, CD_4_GAIN, obstacleR1Location);

    // Bullion Left / Right
    addGameTarget(&bullionRight1Target, BULLION_RIGHT_1, BULLION_GAIN, bullionRight1Location);
    addGameTarget(&bullionLeft1Target, BULLION_LEFT_1, BULLION_GAIN, bullionLeft1Location);
}

// CD ActionItem

void cdTakeStep1() {
    motionFollowPath(bottle2ToCDPath, false);
}

void cdTakeStep2() {
    motionFollowPath(cdToDropZone1Path, false);
}

// Bullion Right 1 ActionItem

void bullionRight1Rotate() {
    rotateAbsolute(ANGLE_NEG_90);
}

void bullionRight1Step3GoToDropZone() {
    motionGoLocation(dropZone1Location,
                     ANGLE_NEG_90, 
                    0x78, 0x40,
                    MOTION_ACCELERATION_FACTOR_LOW, MOTION_SPEED_FACTOR_LOW);
}

void R3ToBullionRight1() {
    motionFollowPath(obstacleR3ToBullionRight1Path, false);
}

void dropZone1ToBullionRight1() {
    motionFollowPath(dropZone1ToBullionRight1Path, false);
}

// Bullion Left 1 ActionItem

void bullionLeft1Rotate() {
    rotateAbsolute(ANGLE_NEG_90);
}

void bullionLeft1Step3GoToDropZone() {
    motionGoLocation(dropZone1Location,
                     ANGLE_NEG_90, 
                    0x78, 0x40,
                    MOTION_ACCELERATION_FACTOR_LOW, MOTION_SPEED_FACTOR_LOW);
}

void dropZone1ToBullionLeft1() {
    motionFollowPath(dropZone1ToBullionLeft1Path, false);
}

void L3ToBullionLeft1() {
    motionFollowPath(obstacleL3ToBullionLeft1Path, false);
}

void initTargetActions2012() {
    clearTargetActionList(&(bullion1Target.actionList));
    clearTargetActionList(&(bottle1Target.actionList));
    clearTargetActionList(&(bottle2Target.actionList));
    clearTargetActionList(&(cd4Target.actionList));
    clearTargetActionList(&(bullionRight1Target.actionList));
    clearTargetActionList(&(bullionLeft1Target.actionList));
    //clearTargetActionList(&(opponentCDTarget.actionList));

    addTargetAction(&(bullion1Target.actionList), &bullion1TargetAction, bullion1Location, bullion1Location, 2, NULL, NULL);
    addTargetAction(&(bottle1Target.actionList), &bottle1TargetAction, bottle1Location, bottle1Location, 2, NULL, NULL);
    addTargetAction(&(bottle2Target.actionList), &bottle2TargetAction, bottle2Location, bottle2Location, 3, NULL, NULL);
    addTargetAction(&(cd4Target.actionList), &cdTakeTargetAction, bottle2Location, dropZone1Location, 4, NULL /** TODO*/,&cdTakeTargetActionItemList);

    // BULLION RIGHT 1
    addTargetAction(&(bullionRight1Target.actionList), &bullionRight1FromDropZone1TargetAction, dropZone1Location, dropZone1Location, 5, NULL /** TODO*/, &bullionRight1FromDropZone1ActionItemList);
    addTargetAction(&(bullionRight1Target.actionList), &bullionRight1FromR3TargetAction, obstacleR3Location, dropZone1Location, 7, NULL /** TODO*/, &bullionRight1FromR3ActionItemList);

    // BULLION LEFT 1
    addTargetAction(&(bullionLeft1Target.actionList), &bullionLeft1FromDropZone1TargetAction, dropZone1Location, dropZone1Location, 5, NULL /** TODO*/, &bullionLeft1FromDropZone1ActionItemList);
    addTargetAction(&(bullionLeft1Target.actionList), &bullionLeft1FromL3TargetAction, obstacleL3Location, dropZone1Location, 7, NULL /** TODO*/, &bullionLeft1FromL3ActionItemList);

    // OPPONENT CD
    //addTargetAction(&(opponentCDTarget.actionList), &opponentCDTargetAction, &dropZone1Location, &dropZone1Location, 5, NULL);
}

void initTargetActionsItems2012() {
    // CD
    addTargetActionItem(&cdTakeTargetActionItemList, &cdTakeStep1TargetActionItem, &cdTakeStep1, "cdTakeStep1");
    addTargetActionItem(&cdTakeTargetActionItemList, &cdTakeStep2TargetActionItem, &cdTakeStep2, "cdTakeStep2");

    // RIGHT BULLION 1
    addTargetActionItem(&bullionRight1FromDropZone1ActionItemList, &bullionRight1Step1FromDropZone1TargetActionItem, &dropZone1ToBullionRight1, "dropZone1->bullionRight1");
    addTargetActionItem(&bullionRight1FromDropZone1ActionItemList, &bullionRight1Step2OpenPlierTargetActionItem, &armRightDown, "armRightDown");
    addTargetActionItem(&bullionRight1FromDropZone1ActionItemList, &bullionRight1Step3GoTargetActionItem, &bullionRight1Step3GoToDropZone, "bullionRight1GoToDropZone1");
    addTargetActionItem(&bullionRight1FromDropZone1ActionItemList, &bullionRight1Step4ClosePlierTargetActionItem, &armRightUp, "armRightUp");

    addTargetActionItem(&bullionRight1FromR3ActionItemList, &bullionRight1RotateTargetActionItem, &bullionRight1Rotate, "rotate");
    addTargetActionItem(&bullionRight1FromR3ActionItemList, &bullionRight1Step1FromR3TargetActionItem, &R3ToBullionRight1, "R3->bullionRight1");
    addTargetActionItem(&bullionRight1FromR3ActionItemList, &bullionRight1Step2OpenPlierTargetActionItem, &armRightDown, "armRightDown");
    addTargetActionItem(&bullionRight1FromR3ActionItemList, &bullionRight1Step3GoTargetActionItem, &bullionRight1Step3GoToDropZone, "bullionRight1GoToDropZone1");
    addTargetActionItem(&bullionRight1FromR3ActionItemList, &bullionRight1Step4ClosePlierTargetActionItem, &armRightUp, "armRightUp");

    // LEFT BULLION 1
    addTargetActionItem(&bullionLeft1FromDropZone1ActionItemList, &bullionLeft1Step1FromDropZone1TargetActionItem, &dropZone1ToBullionLeft1, "dropZone1->bullionLeft1");
    addTargetActionItem(&bullionLeft1FromDropZone1ActionItemList, &bullionLeft1Step2OpenPlierTargetActionItem, &armLeftDown, "armLeftDown");
    addTargetActionItem(&bullionLeft1FromDropZone1ActionItemList, &bullionLeft1Step3GoTargetActionItem, &bullionLeft1Step3GoToDropZone, "bullionLeft1GoToDropZone1");
    addTargetActionItem(&bullionLeft1FromDropZone1ActionItemList, &bullionLeft1Step4ClosePlierTargetActionItem, &armLeftUp, "armLeftUp");

    addTargetActionItem(&bullionLeft1FromL3ActionItemList, &bullionLeft1RotateTargetActionItem, &bullionLeft1Rotate, "rotate");
    addTargetActionItem(&bullionLeft1FromL3ActionItemList, &bullionLeft1Step1FromL3TargetActionItem, &L3ToBullionLeft1, "L3->bullionLeft1");
    addTargetActionItem(&bullionLeft1FromL3ActionItemList, &bullionLeft1Step2OpenPlierTargetActionItem, &armLeftDown, "armLeftDown");
    addTargetActionItem(&bullionLeft1FromL3ActionItemList, &bullionLeft1Step3GoTargetActionItem, &bullionLeft1Step3GoToDropZone, "bullionLeft1GoToDropZone1");
    addTargetActionItem(&bullionLeft1FromL3ActionItemList, &bullionLeft1Step4ClosePlierTargetActionItem, &armLeftUp, "armLeftUp");
}

/**
 * @private.
 */
void initStrategies2012() {
    clearGameStrategies();
    addGameStrategy(&strategy1, "S1");
}

void initStrategiesItems2012(int strategyIndex) {
    if (strategyIndex == STRATEGY_HOMOLOGATION) {
        addGameStrategyItem(&strategy1, &takeBullionFirstStrategyItem, &bullion1Target);
        addGameStrategyItem(&strategy1, &bullionRight1StrategyItem, &bullionRight1Target);
        return;
    }

    addGameStrategyItem(&strategy1, &takeBullionFirstStrategyItem, &bullion1Target);
    addGameStrategyItem(&strategy1, &bottle1StrategyItem, &bottle1Target);
    addGameStrategyItem(&strategy1, &bottle2StrategyItem, &bottle2Target);
    addGameStrategyItem(&strategy1, &cdTakeStrategyItem, &cd4Target);
    addGameStrategyItem(&strategy1, &bullionRight1StrategyItem, &bullionRight1Target);
    addGameStrategyItem(&strategy1, &bullionLeft1StrategyItem, &bullionLeft1Target);
//    addGameStrategyItem(&strategy1, &opponentCDStrategyItem, &opponentCDTarget);
}

void initStrategy2012(int strategyIndex) {
    // initNavigation();
    initLocations2012();
    initPaths2012(strategyIndex);

    initTargets2012();
    initTargetActions2012();
    initTargetActionsItems2012();

    initStrategies2012();
    initStrategiesItems2012(strategyIndex);

    GameStrategy* strategy = getGameStrategy(0);
    GameStrategyContext* strategyContext = getStrategyContext();
    strategyContext->gameStrategy = strategy;
    if (strategyIndex == STRATEGY_HOMOLOGATION) {
        strategyContext->maxTargetToHandle = 1;
    }
    else {
        strategyContext->maxTargetToHandle = getGameTargetList()->size;
    }
    //OutputStream* debugOutputStream = getInfoOutputStreamLogger();
    //printStrategyAllDatas(debugOutputStream);

    // opponent
    Point* p = &(getStrategyContext()->opponentRobotPosition);
    p->x = 0;
    p->y = 0;
    
    // obstacle
    p = &(getStrategyContext()->lastObstaclePosition);
    p->x = 0;
    p->y = 0;
    
    strategyContext->hasMoreNextSteps = true;

    // reinitialize the game board to change elements / targets ...
}

void printStrategyAllDatas(OutputStream* outputStream) {
    printLocationList(outputStream, "navigationLocationList:", getNavigationLocationList());
    printPathList(outputStream, "navigationPathList:", getNavigationPathList());
    printGameTargetList(outputStream);
    printGameStrategyList(outputStream);
    printGameStrategyContext(outputStream, getStrategyContext());
}
