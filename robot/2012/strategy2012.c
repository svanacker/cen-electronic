#include <stdlib.h>

#include "strategy2012.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/navigation.h"


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

// Locations
static Location startAreaLocation; 
static Location bullion1Location;
static Location bottle1Location;
static Location bottle2Location;
static Location cdTakeLocation;
static Location dropZone1Location;
static Location cleanMiddle1Location;
// static Location rightBullionLocation;

// Paths
static Path startAreaToBullion1;
static Path bullion1ToBottle1;
static Path bottle1ToBottle2;
static Path bottle2ToCD;
static Path cdToDropZone1;
static Path dropZone1ToBullionMiddle1;
/*
static Path bullionMiddle1ToRightBullion1;
static Path rightBullion1ToDropZone1;
static Path bullionMiddle1ToLeftBullion1;
static Path leftBullion1ToStartAreaFrontOf;
static Path startAreaFrontOfTostartAreaDropZone1;
*/

// Targets List
static GameTarget bullion1Target;
static GameTarget bottle1Target;
static GameTarget bottle2Target;
static GameTarget cd4Target;
static GameTarget bullionRight1Target;
static GameTarget bullionLeft1Target;

/*
static GameTarget bullionRight2Target;
static GameTarget bullionLeft2Target;
*/

// Target actionList
static GameTargetAction bullion1TargetAction;
static GameTargetAction bottle1TargetAction;
static GameTargetAction bottle2TargetAction;
static GameTargetAction cdTakeTargetAction;
static GameTargetAction bullionRight1TargetAction;
static GameTargetAction bullionLeft1TargetAction;

// -> CD
static GameTargetActionItemList cdTakeTargetActionItemList;  
static GameTargetActionItem cdTakeStep1TargetActionItem;
static GameTargetActionItem cdTakeStep2TargetActionItem;

// -> BULLION RIGHT 1
static GameTargetActionItemList bullionRight1ActionItemList; 
static GameTargetActionItem bullionRight1Step1BackTargetActionItem;
static GameTargetActionItem bullionRight1Step2OpenPlierTargetActionItem;
static GameTargetActionItem bullionRight1Step3GoTargetActionItem;
static GameTargetActionItem bullionRight1Step4ClosePlierTargetActionItem;

// -> BULLION LEFT 2
static GameTargetActionItemList bullionLeft1ActionItemList; 
static GameTargetActionItem bullionLeft1Step1BackTargetActionItem;
static GameTargetActionItem bullionLeft1Step2OpenPlierTargetActionItem;
static GameTargetActionItem bullionLeft1Step3GoTargetActionItem;
static GameTargetActionItem bullionLeft1Step4ClosePlierTargetActionItem;

// strategies
static GameStrategy strategy1;

// strategies Items
static GameStrategyItem takeBullionFirstStrategyItem;
static GameStrategyItem bottle1StrategyItem;
static GameStrategyItem bottle2StrategyItem;
static GameStrategyItem cdTakeStrategyItem;
static GameStrategyItem bullionRight1StrategyItem;
static GameStrategyItem bullionLeft1StrategyItem;

void initLocations2012() {
	addNavigationLocation(&startAreaLocation, START_AREA, START_AREA_X, START_AREA_Y);
	addNavigationLocation(&bullion1Location, BULLION_1, BULLION_1_X, BULLION_1_Y);
	addNavigationLocation(&bottle1Location, BOTTLE_1, BOTTLE_1_X, BOTTLE_1_Y);
	addNavigationLocation(&bottle2Location, BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);
	addNavigationLocation(&cdTakeLocation, CD_TAKE, CD_TAKE_X, CD_TAKE_Y);
	addNavigationLocation(&dropZone1Location, DROP_ZONE_1, DROP_ZONE_1_X, DROP_ZONE_1_Y);
	addNavigationLocation(&cleanMiddle1Location, CLEAN_MIDDLE_BULLION_1, CLEAN_MIDDLE_BULLION_1_X, CLEAN_MIDDLE_BULLION_1_Y); 
}

void initPaths2012() {
	addNavigationPath(&startAreaToBullion1, &startAreaLocation, &bullion1Location, START_AREA_TO_BULLION_1_COST,  0x40, 0x40, 0x02A3, ANGLE_NEG_90, START_AREA_TO_BULLION_1_SPEED_FACTOR); 
	addNavigationPath(&bullion1ToBottle1, &bullion1Location, &bottle1Location, BULLION_1_TO_BOTTLE_1_COST, 0xEC, 0xC0, ANGLE_NEG_90, ANGLE_180, BULLION_1_TO_BOTTLE_1_SPEED_FACTOR);
	addNavigationPath(&bottle1ToBottle2, &bottle1Location, &bottle2Location, BOTTLE_1_TO_BOTTLE_2_COST, 0x57, 0x0A, ANGLE_180, 0, BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR);
	addNavigationPath(&bottle2ToCD, &bottle2Location, &cdTakeLocation, BOTTLE_2_TO_CD_COST, 0x1B, 0x30, 0, 0xFAF6, BOTTLE_2_TO_CD_SPEED_FACTOR);
	addNavigationPath(&cdToDropZone1, &cdTakeLocation, &dropZone1Location, CD_TO_DROP_ZONE_1_COST, 0x11, 0x26, 0xFAF6, ANGLE_NEG_90, CD_TO_DROP_ZONE_1_SPEED_FACTOR);
	// TODO : Check value
	addNavigationPath(&dropZone1ToBullionMiddle1, &dropZone1Location, &cleanMiddle1Location, DROP_ZONE_1_TO_MIDDLE_BULLION_1_COST, 0x01, 0x01, ANGLE_NEG_90, ANGLE_NEG_90, DROP_ZONE_1_TO_MIDDLE_BULLION_1_SPEED_FACTOR); 
}

void initTargets2012() {
	addGameTarget(&bullion1Target, BULLION_1, BULLION_GAIN, &bullion1Location);
	addGameTarget(&bottle1Target, BOTTLE_1, BOTTLE_GAIN, &bottle1Location);
	addGameTarget(&bottle2Target, BOTTLE_2, BOTTLE_GAIN, &bottle2Location);
	addGameTarget(&cd4Target, CD_TAKE, CD_4_GAIN, &cdTakeLocation);
	addGameTarget(&bullionRight1Target, BULLION_RIGHT_1, BULLION_GAIN, &cleanMiddle1Location);
	addGameTarget(&bullionLeft1Target, BULLION_LEFT_1, BULLION_GAIN, &cleanMiddle1Location);
	/*
	addGameTarget(&bullionRight2Target, BULLION_RIGHT_2, BULLION_GAIN);
	addGameTarget(&bullionLeft2Target, BULLION_LEFT_2, BULLION_GAIN);
	*/
}

// ARM

void armLeftUp() {
	armDriver2012Up(ARM_LEFT);
}

void armLeftDown() {
	armDriver2012Down(ARM_LEFT);
}

void armRightUp() {
	armDriver2012Up(ARM_RIGHT);
}

void armRightDown() {
	armDriver2012Down(ARM_RIGHT);
}

// CD ActionItem

void cdTakeStep1() {
	motionFollowPath(&bottle2ToCD);
}

void cdTakeStep2() {
	motionFollowPath(&cdToDropZone1);
}

// Bullion Right 1 ActionItem

void bullionRight1Step1Back() {
	// TODO
}

void bullionRight1Step3GoToDropZone() {
	// TODO
}

// Bullion Left 1 ActionItem

void bullionLeft1Step1Back() {
	// TODO
}

void bullionLeft1Step3GoToDropZone() {
	// TODO
}


void initTargetActions2012() {
	addTargetAction(&(bullion1Target.actionList), &bullion1TargetAction, &bullion1Location, &bullion1Location, 2, NULL);
	addTargetAction(&(bottle1Target.actionList), &bottle1TargetAction, &bottle1Location, &bottle1Location, 2, NULL);
	addTargetAction(&(bottle2Target.actionList), &bottle2TargetAction, &bottle2Location, &bottle2Location, 3, NULL);
	addTargetAction(&(cd4Target.actionList), &cdTakeTargetAction, &bottle2Location, &dropZone1Location, 4, &cdTakeTargetActionItemList);
	addTargetAction(&(bullionRight1Target.actionList), &bullionRight1TargetAction, &cleanMiddle1Location, &dropZone1Location, 5, &bullionRight1ActionItemList);
	addTargetAction(&(bullionLeft1Target.actionList), &bullionLeft1TargetAction, &cleanMiddle1Location, &dropZone1Location, 6, &bullionLeft1ActionItemList);

}

void initTargetActionsItems2012() {
	// CD
	addTargetActionItem(&cdTakeTargetActionItemList, &cdTakeStep1TargetActionItem, &cdTakeStep1, "cdTakeStep1");
	addTargetActionItem(&cdTakeTargetActionItemList, &cdTakeStep2TargetActionItem, &cdTakeStep2, "cdTakeStep2");

	// RIGHT BULLION 1
	addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step1BackTargetActionItem, &bullionRight1Step1Back, "bullionRight1Step1Back");
	addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step2OpenPlierTargetActionItem, &armLeftDown, "armLeftDown");
	addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step3GoTargetActionItem, &bullionRight1Step3GoToDropZone, "bullionRight1GoToDropZone1");
	addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step4ClosePlierTargetActionItem, &armLeftUp, "armLeftUp");

	// LEFT BULLION 1
	addTargetActionItem(&bullionLeft1ActionItemList, &bullionLeft1Step1BackTargetActionItem, &bullionLeft1Step1Back, "bullionLeft1Step1Back");
	addTargetActionItem(&bullionLeft1ActionItemList, &bullionLeft1Step2OpenPlierTargetActionItem, &armRightDown, "armRightDown");
	addTargetActionItem(&bullionLeft1ActionItemList, &bullionLeft1Step3GoTargetActionItem, &bullionLeft1Step3GoToDropZone, "bullionLeft1GoToDropZone1");
	addTargetActionItem(&bullionLeft1ActionItemList, &bullionLeft1Step4ClosePlierTargetActionItem, &armRightUp, "armRightUp");
}

void initStrategies2012() {
	addGameStrategy(&strategy1, "S1");
}

void initStrategiesItems2012() {
	addGameStrategyItem(&strategy1, &takeBullionFirstStrategyItem, &bullion1Target);
	addGameStrategyItem(&strategy1, &bottle1StrategyItem, &bottle1Target);
	addGameStrategyItem(&strategy1, &bottle2StrategyItem, &bottle2Target);
	addGameStrategyItem(&strategy1, &cdTakeStrategyItem, &cd4Target);
	addGameStrategyItem(&strategy1, &bullionRight1StrategyItem, &bullionRight1Target);
	addGameStrategyItem(&strategy1, &bullionLeft1StrategyItem, &bullionLeft1Target);
}

void initStrategy2012() {
	initLocations2012();
	initPaths2012();

	initTargets2012();
	initTargetActions2012();
	initTargetActionsItems2012();

	initStrategies2012();
	initStrategiesItems2012();
}
