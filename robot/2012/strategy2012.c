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
static Location startAreaLocation; 
#ifdef INCLUDE_HOMOLOGATION
    static Location startAreaFrontLocation; 
#endif

static Location bullion1Location;
static Location bottle1Location;
static Location bottle2FrontLocation;
static Location bottle2Location;
static Location dropZone1Location;
static Location frontOfMapLocation;

// -> Bullion1
static Location bullionRight1Location;
static Location bullionLeft1Location;

// -> OpponentCD
static Location bullionMiddle2Location;

static Location obstacleL1Location;
static Location obstacleL2Location;
static Location obstacleL3Location;
static Location obstacleL4Location;
static Location obstacleR1Location;
static Location obstacleR2Location;
static Location obstacleR3Location;
static Location obstacleR4Location;
static Location obstacleM1Location;
static Location obstacleM2Location;

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
    /*
    clearLocationList(getNavigationLocationList());
    // -> General locations
    addNavigationLocation(&startAreaLocation, START_AREA, START_AREA_X, START_AREA_Y);
    #ifdef INCLUDE_HOMOLOGATION
        addNavigationLocation(&startAreaFrontLocation, START_AREA_FRONT, START_AREA_FRONT_X, START_AREA_FRONT_Y);
    #endif
    addNavigationLocation(&bullion1Location, BULLION_1, BULLION_1_X, BULLION_1_Y);
    addNavigationLocation(&bottle1Location, BOTTLE_1, BOTTLE_1_X, BOTTLE_1_Y);
    addNavigationLocation(&bottle2FrontLocation, BOTTLE_2_FRONT, BOTTLE_2_FRONT_X, BOTTLE_2_FRONT_Y);
    addNavigationLocation(&bottle2Location, BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);
    //addNavigationLocation(&cdTakeLocation, CD_TAKE, CD_TAKE_X, CD_TAKE_Y);
    addNavigationLocation(&dropZone1Location, DROP_ZONE_1, (int)DROP_ZONE_1_X, (int) DROP_ZONE_1_Y);
    addNavigationLocation(&frontOfMapLocation, FRONT_OF_MAP_LOCATION, (int) FRONT_OF_MAP_LOCATION_X, (int)FRONT_OF_MAP_LOCATION_Y);
    // -> Bullion 1
    addNavigationLocation(&bullionRight1Location, BULLION_RIGHT_1, BULLION_RIGHT_1_X, BULLION_RIGHT_1_Y); 
    addNavigationLocation(&bullionLeft1Location, BULLION_LEFT_1, BULLION_LEFT_1_X, BULLION_LEFT_1_Y); 
    // -> Bullion 2 / Opponent CD
    addNavigationLocation(&bullionMiddle2Location, BULLION_MIDDLE_2, (int)BULLION_MIDDLE_2_X, (int) BULLION_MIDDLE_2_Y);

    addNavigationLocation(&obstacleL1Location, OBSTACLE_L1, OBSTACLE_L_X, OBSTACLE_1_Y);
    addNavigationLocation(&obstacleL2Location, OBSTACLE_L2, OBSTACLE_L_X, OBSTACLE_2_Y);
    addNavigationLocation(&obstacleL3Location, OBSTACLE_L3, OBSTACLE_L_X, (int) OBSTACLE_3_Y);
    addNavigationLocation(&obstacleL4Location, OBSTACLE_L4, (int) OBSTACLE_L_X, (int)OBSTACLE_4_Y);
    addNavigationLocation(&obstacleM1Location, OBSTACLE_M1, (int) OBSTACLE_M_X, (int)OBSTACLE_1_Y);
    addNavigationLocation(&obstacleM2Location, OBSTACLE_M2, (int) OBSTACLE_M_X, (int)OBSTACLE_4_Y);
    addNavigationLocation(&obstacleR1Location, OBSTACLE_R1, (int) OBSTACLE_R_X, (int) OBSTACLE_1_Y);
    addNavigationLocation(&obstacleR2Location, OBSTACLE_R2, (int) OBSTACLE_R_X, (int) OBSTACLE_2_Y);
    addNavigationLocation(&obstacleR3Location, OBSTACLE_R3, (int) OBSTACLE_R_X, (int) OBSTACLE_3_Y);
    addNavigationLocation(&obstacleR4Location, OBSTACLE_R4, (int) OBSTACLE_R_X, (int) OBSTACLE_4_Y);
    */
}

/*
void bottle2ToCDPathFunction() { fillPathData(&bottle2Location, &obstacleR1Location, BOTTLE_2_TO_CD_COST, 0x1B, 0x30, 0xF8F8, 0xFAF6, BOTTLE_2_TO_CD_SPEED_FACTOR, BOTTLE_2_TO_CD_ACCELERATION_FACTOR);}
void cdToDropZone1PathFunction() { fillPathData(&obstacleR1Location, &dropZone1Location, CD_TO_DROP_ZONE_1_COST, 0x11, 0x26, 0xFAF6, ANGLE_NEG_90, CD_TO_DROP_ZONE_1_SPEED_FACTOR, CD_TO_DROP_ZONE_1_ACCELERATION_FACTOR);}
void dropZone1ToBullionLeft1PathFunction() { fillAsymmetricPathData(&dropZone1Location, &bullionLeft1Location, DROP_ZONE_1_TO_BULLION_LEFT_1_COST, 0xB0, 0x80, ANGLE_NEG_90, ANGLE_NEG_90, DROP_ZONE_1_TO_BULLION_LEFT_1_SPEED_FACTOR, DROP_ZONE_1_TO_BULLION_LEFT_1_ACCELERATION_FACTOR);} 
void dropZone1ToBullionRight1PathFunction() { fillAsymmetricPathData(&dropZone1Location, &bullionRight1Location, DROP_ZONE_1_TO_BULLION_RIGHT_1_COST, 0xB0, 0x80, ANGLE_NEG_90, ANGLE_NEG_90, DROP_ZONE_1_TO_BULLION_RIGHT_1_SPEED_FACTOR, DROP_ZONE_1_TO_BULLION_RIGHT_1_ACCELERATION_FACTOR);} 
void obstacleR3ToBullionRight1PathFunction() { fillAsymmetricPathData(&obstacleR3Location, &bullionRight1Location, OR3_TO_BULLIONRIGHT1_COST, 0x0A, 0x0A, ANGLE_NEG_135, ANGLE_NEG_90, OR3_TO_BULLIONRIGHT1_SPEED_FACTOR, OR3_TO_BULLIONRIGHT1_ACCELERATION_FACTOR);}
void obstacleL3ToBullionLeft1PathFunction() { fillAsymmetricPathData(&obstacleL3Location, &bullionLeft1Location, OL3_TO_BULLIONRIGHT1_COST, 0x0A, 0x0A, ANGLE_NEG_45, ANGLE_NEG_90, OL3_TO_BULLIONRIGHT1_SPEED_FACTOR, OL3_TO_BULLIONRIGHT1_ACCELERATION_FACTOR);}
*/

void initPaths2012(int index) {
    /*
    clearPathList(getNavigationPathList());

    // DIRECT PATH TO TARGETS
    if (index == STRATEGY_HOMOLOGATION) {
        #ifdef INCLUDE_HOMOLOGATION
            void startAreaToStartAreaFrontPathFunction() { fillPathData(&startAreaLocation, &startAreaFrontLocation, STARTAREA_TO_STARTAREA_FRONT_COST,  0x0A, 0x0A, START_ANGLE, ANGLE_90, STARTAREA_TO_STARTAREA_FRONT_SPEED_FACTOR, STARTAREA_TO_STARTAREA_FRONT_ACCELERATION_FACTOR); }
            addNavigationPath(&startAreaToStartAreaFrontPathFunction);
            void startAreaFrontToOM1PathFunction() { fillPathData(&startAreaFrontLocation, &obstacleM1Location, STARTAREA_FRONT_TO_OM1_COST,  0x0A, 0x0A, ANGLE_0, ANGLE_0, STARTAREA_FRONT_TO_OM1_SPEED_FACTOR, STARTAREA_FRONT_TO_OM1_ACCELERATION_FACTOR); }
            addNavigationPath(&startAreaFrontToOM1PathFunction);
        #endif
    }
    else {
        void startAreaToBullion1PathFunction() { fillPathData(&startAreaLocation, &bullion1Location, START_AREA_TO_BULLION_1_COST,  0x40, 0x40, START_ANGLE, ANGLE_NEG_90, START_AREA_TO_BULLION_1_SPEED_FACTOR, START_AREA_TO_BULLION_1_ACCELERATION_FACTOR); }
        addNavigationPath(&startAreaToBullion1PathFunction);
    }

    void bullion1ToBottle1PathFunction() { fillAsymmetricPathData(&bullion1Location, &bottle1Location, BULLION_1_TO_BOTTLE_1_COST, 0xEC, 0xC0, ANGLE_NEG_90, ANGLE_180, BULLION_1_TO_BOTTLE_1_SPEED_FACTOR, BULLION_1_TO_BOTTLE_1_ACCELERATION_FACTOR); }
    addNavigationPath(&bullion1ToBottle1PathFunction);

    void bottle1ToBottle2FrontPathFunction() { fillPathData(&bottle1Location, &bottle2FrontLocation, BOTTLE_1_TO_BOTTLE_2_FRONT_COST, 0x40, 0x0A, ANGLE_180, 0x0450, BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR, BOTTLE_1_TO_BOTTLE_2_ACCELERATION_FACTOR);}
    addNavigationPath(&bottle1ToBottle2FrontPathFunction);

    void bottle2FrontToBottle2PathFunction() { fillAsymmetricPathData(&bottle2FrontLocation, &bottle2Location, BOTTLE_2_FRONT_TO_BOTTLE_2_COST, 0xE0, 0xF0, 0x0450, 0xF8F8, BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR, BOTTLE_1_TO_BOTTLE_2_ACCELERATION_FACTOR);}
    addNavigationPath(&bottle2FrontToBottle2PathFunction);

    // TO BULLION RIGHT 1
    addNavigationPath(&dropZone1ToBullionRight1PathFunction); 
    
    // TO BULLION LEFT 1
    addNavigationPath(&dropZone1ToBullionLeft1PathFunction);

    // OL1->OL2
    void obstacleL1ToObstacleL2PathFunction() { fillPathData(&obstacleL1Location, &obstacleL2Location, OBSTACLE_L1_TO_L2_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L1_TO_L2_SPEED_FACTOR, OBSTACLE_L1_TO_L2_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleL1ToObstacleL2PathFunction);

    // OL1->OL4
    void obstacleL1ToObstacleL4PathFunction() { fillPathData(&obstacleL1Location, &obstacleL4Location, OBSTACLE_L1_TO_L4_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L1_TO_L4_SPEED_FACTOR, OBSTACLE_L1_TO_L4_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleL1ToObstacleL4PathFunction);

    void obstacleL2ToObstacleL3PathFunction() { fillPathData(&obstacleL2Location, &obstacleL3Location, OBSTACLE_L2_TO_L3_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L2_TO_L3_SPEED_FACTOR, OBSTACLE_L2_TO_L3_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleL2ToObstacleL3PathFunction);

    void obstacleL3ToObstacleL4PathFunction() { fillPathData(&obstacleL3Location, &obstacleL4Location, OBSTACLE_L3_TO_L4_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, OBSTACLE_L3_TO_L4_SPEED_FACTOR, OBSTACLE_L3_TO_L4_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleL3ToObstacleL4PathFunction);

    // OL4->OM2
    void obstacleL4ToObstacleM2PathFunction() { fillPathData(&obstacleL4Location, &obstacleM2Location, OBSTACLE_L4_TO_M2_COST, 0x0A, 0x0A, 0, 0, OBSTACLE_L4_TO_M2_SPEED_FACTOR, OBSTACLE_L4_TO_M2_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleL4ToObstacleM2PathFunction);

    // OL4->OR4
    void obstacleL4ToObstacleR4PathFunction() { fillPathData(&obstacleL4Location, &obstacleR4Location, OBSTACLE_L4_TO_R4_COST, 0x0A, 0x0A, 0, 0, OBSTACLE_L4_TO_R4_SPEED_FACTOR, OBSTACLE_L4_TO_R4_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleL4ToObstacleR4PathFunction);

    void obstacleM2ToObstacleR4PathFunction() { fillPathData(&obstacleM2Location, &obstacleR4Location, OBSTACLE_M2_TO_R4_COST, 0x0A, 0x0A, 0, 0, OBSTACLE_M2_TO_R4_SPEED_FACTOR, OBSTACLE_M2_TO_R4_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleM2ToObstacleR4PathFunction);

    // OR4->OR3
    void obstacleR4ToObstacleR3PathFunction() { fillPathData(&obstacleR4Location, &obstacleR3Location, OBSTACLE_R4_TO_R3_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R4_TO_R3_SPEED_FACTOR, OBSTACLE_R4_TO_R3_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleR4ToObstacleR3PathFunction);

    // OR4->OR1
    void obstacleR4ToObstacleR1PathFunction() { fillPathData(&obstacleR4Location, &obstacleR1Location, OBSTACLE_R4_TO_R1_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R4_TO_R1_SPEED_FACTOR, OBSTACLE_R4_TO_R1_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleR4ToObstacleR1PathFunction);

    void obstacleR3ToObstacleR2PathFunction() { fillPathData(&obstacleR3Location, &obstacleR2Location, OBSTACLE_R3_TO_R2_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R3_TO_R2_SPEED_FACTOR, OBSTACLE_R3_TO_R2_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleR3ToObstacleR2PathFunction);

    void obstacleR2ToObstacleR1PathFunction() { fillPathData(&obstacleR2Location, &obstacleR1Location, OBSTACLE_R2_TO_R1_COST, 0x0A, 0x0A, ANGLE_NEG_90, ANGLE_NEG_90, OBSTACLE_R2_TO_R1_SPEED_FACTOR, OBSTACLE_R2_TO_R1_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleR2ToObstacleR1PathFunction);

    // OR1->OM1
    void obstacleR1ToObstacleM1PathFunction() { fillPathData(&obstacleR1Location, &obstacleM1Location, OBSTACLE_R1_TO_M1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, OBSTACLE_R1_TO_M1_SPEED_FACTOR, OBSTACLE_R1_TO_M1_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleR1ToObstacleM1PathFunction);

    // OR1->OL1
    void obstacleR1ToObstacleL1PathFunction() { fillPathData(&obstacleR1Location, &obstacleL1Location, OBSTACLE_R1_TO_L1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, OBSTACLE_R1_TO_L1_SPEED_FACTOR, OBSTACLE_R1_TO_L1_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleR1ToObstacleL1PathFunction);

    // OM1->OL1
    void obstacleM1ToObstacleL1PathFunction() { fillPathData(&obstacleM1Location, &obstacleL1Location, OBSTACLE_M1_TO_L1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, OBSTACLE_M1_TO_L1_SPEED_FACTOR, OBSTACLE_M1_TO_L1_ACCELERATION_FACTOR);}
    addNavigationPath(&obstacleM1ToObstacleL1PathFunction);

    // bottle1->OR1
    void bottle1ToObstacleR1PathFunction() { fillAsymmetricPathData(&bottle1Location, &obstacleR1Location, BOTTLE1_TO_OR1_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, BOTTLE1_TO_OR1_SPEED_FACTOR, BOTTLE1_TO_OR1_ACCELERATION_FACTOR);}
    addNavigationPath(&bottle1ToObstacleR1PathFunction);

    // bottle2->OR3
    void bottle2ToObstacleR3PathFunction() { fillAsymmetricPathData(&bottle2Location, &obstacleR3Location, BOTTLE2_TO_OR3_COST, 0x0A, 0x0A, ANGLE_180, ANGLE_180, BOTTLE2_TO_OR3_SPEED_FACTOR, BOTTLE2_TO_OR3_ACCELERATION_FACTOR);}
    addNavigationPath(&bottle2ToObstacleR3PathFunction);

    // dropZone1->OL1
    void dropZone1ToObstacleL1PathFunction() { fillPathData(&dropZone1Location, &obstacleL1Location, DROPZONE1_TO_OL1_COST, 0x19, 0x19, ANGLE_90, ANGLE_180, DROPZONE1_TO_OL1_SPEED_FACTOR, DROPZONE1_TO_OL1_ACCELERATION_FACTOR);}
    addNavigationPath(&dropZone1ToObstacleL1PathFunction);

    // dropZone1->OM1
    void dropZone1ToObstacleM1PathFunction() { fillPathData(&dropZone1Location, &obstacleM1Location, DROPZONE1_TO_OM1_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, DROPZONE1_TO_OM1_SPEED_FACTOR, DROPZONE1_TO_OM1_ACCELERATION_FACTOR);}
    addNavigationPath(&dropZone1ToObstacleM1PathFunction);

    // dropZone1->OR1
    void dropZone1ToObstacleR1PathFunction() { fillPathData(&dropZone1Location, &obstacleR1Location, DROPZONE1_TO_OR1_COST, 0x19, 0x19, ANGLE_90, 0, DROPZONE1_TO_OR1_SPEED_FACTOR, DROPZONE1_TO_OR1_ACCELERATION_FACTOR);}
    addNavigationPath(&dropZone1ToObstacleR1PathFunction);

    // bullion1->OL1
    if (index != STRATEGY_HOMOLOGATION) {
        void bullion1ToObstacleL1PathFunction() { fillPathData(&bullion1Location, &obstacleL1Location, BULLION1_TO_OL1_COST, 0x19, 0x19, ANGLE_90, ANGLE_180, BULLION1_TO_OL1_SPEED_FACTOR, BULLION1_TO_OL1_ACCELERATION_FACTOR);}
        addNavigationPath(&bullion1ToObstacleL1PathFunction);
    }

    // bullion1->OM1
    void bullion1ToObstacleM1PathFunction() { fillPathData(&bullion1Location, &obstacleM1Location, BULLION1_TO_OM1_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, BULLION1_TO_OM1_SPEED_FACTOR, BULLION1_TO_OM1_ACCELERATION_FACTOR);}
    addNavigationPath(&bullion1ToObstacleM1PathFunction);

    // bullion1->OR1
    void bullion1ToObstacleR1PathFunction() { fillPathData(&bullion1Location, &obstacleR1Location, BULLION1_TO_OR1_COST, 0x19, 0x19, ANGLE_90, 0, BULLION1_TO_OR1_SPEED_FACTOR, BULLION1_TO_OR1_ACCELERATION_FACTOR);}
    addNavigationPath(&bullion1ToObstacleR1PathFunction);

    // bottle2Front->OR4
    void bottle2FrontToObstacleR4PathFunction() { fillPathData(&bottle2FrontLocation, &obstacleR4Location, BOTTLE2FRONT_TO_CD_COST, 0x0A, 0x0A, ANGLE_90, ANGLE_90, BOTTLE2FRONT_TO_CD_SPEED_FACTOR, BOTTLE2FRONT_TO_CD_ACCELERATION_FACTOR);}
    addNavigationPath(&bottle2FrontToObstacleR4PathFunction);
    */
}

void initTargets2012() {
    clearGameTargets();

    addGameTarget(&bullion1Target, BULLION_1, BULLION_GAIN, &bullion1Location);
    addGameTarget(&bullionRight1Target, BULLION_RIGHT_1, BULLION_GAIN, &bullionRight1Location);

    addGameTarget(&bullion1Target, BULLION_1, BULLION_GAIN, &bullion1Location);
    addGameTarget(&bottle1Target, BOTTLE_1, BOTTLE_GAIN, &bottle1Location);
    addGameTarget(&bottle2Target, BOTTLE_2, BOTTLE_GAIN, &bottle2Location);
    addGameTarget(&cd4Target, CD_TAKE, CD_4_GAIN, &obstacleR1Location);

    // Bullion Left / Right
    addGameTarget(&bullionRight1Target, BULLION_RIGHT_1, BULLION_GAIN, &bullionRight1Location);
    addGameTarget(&bullionLeft1Target, BULLION_LEFT_1, BULLION_GAIN, &bullionLeft1Location);
}

// CD ActionItem

void cdTakeStep1() {
    // motionFollowPath(&bottle2ToCDPathFunction, false);
}

void cdTakeStep2() {
    // motionFollowPath(&cdToDropZone1PathFunction, false);
}

// Bullion Right 1 ActionItem

void bullionRight1Rotate() {
    rotateAbsolute(ANGLE_NEG_90);
}

void bullionRight1Step3GoToDropZone() {
    motionGoLocation(&dropZone1Location,
                     ANGLE_NEG_90, 
                    0x78, 0x40,
                    MOTION_ACCELERATION_FACTOR_LOW, MOTION_SPEED_FACTOR_LOW);
}

void R3ToBullionRight1() {
    // motionFollowPath(&obstacleR3ToBullionRight1PathFunction, false);
}

void dropZone1ToBullionRight1() {
    // motionFollowPath(&dropZone1ToBullionRight1PathFunction, false);
}

// Bullion Left 1 ActionItem

void bullionLeft1Rotate() {
    rotateAbsolute(ANGLE_NEG_90);
}

void bullionLeft1Step3GoToDropZone() {
    motionGoLocation(&dropZone1Location,
                     ANGLE_NEG_90, 
                    0x78, 0x40,
                    MOTION_ACCELERATION_FACTOR_LOW, MOTION_SPEED_FACTOR_LOW);
}

void dropZone1ToBullionLeft1() {
    // motionFollowPath(&dropZone1ToBullionLeft1PathFunction, false);
}

void L3ToBullionLeft1() {
    // motionFollowPath(&obstacleL3ToBullionLeft1PathFunction, false);
}

void initTargetActions2012() {
    clearTargetActionList(&(bullion1Target.actionList));
    clearTargetActionList(&(bottle1Target.actionList));
    clearTargetActionList(&(bottle2Target.actionList));
    clearTargetActionList(&(cd4Target.actionList));
    clearTargetActionList(&(bullionRight1Target.actionList));
    clearTargetActionList(&(bullionLeft1Target.actionList));
    //clearTargetActionList(&(opponentCDTarget.actionList));

    addTargetAction(&(bullion1Target.actionList), &bullion1TargetAction, &bullion1Location, &bullion1Location, 2, NULL, NULL);
    addTargetAction(&(bottle1Target.actionList), &bottle1TargetAction, &bottle1Location, &bottle1Location, 2, NULL, NULL);
    addTargetAction(&(bottle2Target.actionList), &bottle2TargetAction, &bottle2Location, &bottle2Location, 3, NULL, NULL);
    addTargetAction(&(cd4Target.actionList), &cdTakeTargetAction, &bottle2Location, &dropZone1Location, 4, NULL /** TODO*/,&cdTakeTargetActionItemList);

    // BULLION RIGHT 1
    addTargetAction(&(bullionRight1Target.actionList), &bullionRight1FromDropZone1TargetAction, &dropZone1Location, &dropZone1Location, 5, NULL /** TODO*/, &bullionRight1FromDropZone1ActionItemList);
    addTargetAction(&(bullionRight1Target.actionList), &bullionRight1FromR3TargetAction, &obstacleR3Location, &dropZone1Location, 7, NULL /** TODO*/, &bullionRight1FromR3ActionItemList);

    // BULLION LEFT 1
    addTargetAction(&(bullionLeft1Target.actionList), &bullionLeft1FromDropZone1TargetAction, &dropZone1Location, &dropZone1Location, 5, NULL /** TODO*/, &bullionLeft1FromDropZone1ActionItemList);
    addTargetAction(&(bullionLeft1Target.actionList), &bullionLeft1FromL3TargetAction, &obstacleL3Location, &dropZone1Location, 7, NULL /** TODO*/, &bullionLeft1FromL3ActionItemList);

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
    initNavigation();
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
