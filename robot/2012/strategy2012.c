#include <stdlib.h>

#include "strategy2012.h"
#include "strategy2012Utils.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

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
static Location bullion1Location;
static Location bottle1Location;
static Location bottle2FrontLocation;
static Location bottle2Location;
static Location cdTakeLocation;
static Location dropZone1Location;
static Location frontOfMapLocation;

// -> Bullion1
static Location bullionRight1Location;
static Location bullionLeft1Location;

// -> OpponentCD
static Location bullionMiddle2Location;


// ------------------------------------------------------- PATHS -----------------------------------------------------------------------

/*
static Path startAreaToBullion1Path;
static Path bullion1ToBottle1Path;
static Path bottle1ToBottle2FrontPath;
static Path bottle2FrontToBottle2Path;
static Path bottle2ToCDPath;
static Path cdToDropZone1Path;

// -> Bullion Right 1
static Path bullion1ToBullionRight1Path;
static Path dropZone1ToBullionRight1Path;

// -> Bullion Left 1
static Path dropZone1ToBullionLeft1Path;

// -> OpponentCD
static Path startAreaToFrontOfMapPath;
static Path frontOfMapToBullionMiddle2Path;
static Path bullionMiddle2ToBottle2FrontPath;
static Path bottle2FrontToDropZone1Path;
*/

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List
static GameTarget bullion1Target;
static GameTarget bottle1Target;
static GameTarget bottle2Target;
static GameTarget cd4Target;
static GameTarget bullionRight1Target;
static GameTarget bullionLeft1Target;
static GameTarget opponentCDTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// -> Base target
static GameTargetAction bullion1TargetAction;
static GameTargetAction bottle1TargetAction;
static GameTargetAction bottle2TargetAction;
static GameTargetAction cdTakeTargetAction;

// -> Bullion1
static GameTargetAction bullionRight1TargetAction;
static GameTargetAction bullionLeft1TargetAction;

static GameTargetAction opponentCDTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEMS --------------------------------------------------------

// -> CD 4
static GameTargetActionItemList cdTakeTargetActionItemList;  
static GameTargetActionItem cdTakeStep1TargetActionItem;
static GameTargetActionItem cdTakeStep2TargetActionItem;

// -> BULLION RIGHT 1
static GameTargetActionItemList bullionRight1ActionItemList; 
static GameTargetActionItem bullionRight1Step2OpenPlierTargetActionItem;
static GameTargetActionItem bullionRight1Step3GoTargetActionItem;
static GameTargetActionItem bullionRight1Step4ClosePlierTargetActionItem;

// -> BULLION LEFT 1
static GameTargetActionItemList bullionLeft1ActionItemList; 
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
static GameStrategyItem opponentCDStrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void setColor(TEAM_COLOR color) {
	getStrategyContext()->color = color;
	changeLocationsForColor();
	int angle = 675;
	if (!isViolet()) {
		angle = -angle;
	}
	appendStringAndDec(getOutputStreamLogger(INFO), "setColor:", color);
	println(getOutputStreamLogger(INFO));

	getStrategyContext()->robotAngle = angle;
}

void initLocations2012() {
	clearLocationList(getNavigationLocationList());
	// -> General locations
	addNavigationLocation(&startAreaLocation, START_AREA, START_AREA_X, START_AREA_Y);
	addNavigationLocation(&bullion1Location, BULLION_1, BULLION_1_X, BULLION_1_Y);
	addNavigationLocation(&bottle1Location, BOTTLE_1, BOTTLE_1_X, BOTTLE_1_Y);
	addNavigationLocation(&bottle2FrontLocation, BOTTLE_2_FRONT, BOTTLE_2_FRONT_X, BOTTLE_2_FRONT_Y);
	addNavigationLocation(&bottle2Location, BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);
	addNavigationLocation(&cdTakeLocation, CD_TAKE, CD_TAKE_X, CD_TAKE_Y);
	addNavigationLocation(&dropZone1Location, DROP_ZONE_1, DROP_ZONE_1_X, DROP_ZONE_1_Y);
	addNavigationLocation(&frontOfMapLocation, FRONT_OF_MAP_LOCATION, FRONT_OF_MAP_LOCATION_X, FRONT_OF_MAP_LOCATION_Y);
	// -> Bullion 1
	addNavigationLocation(&bullionRight1Location, BULLION_RIGHT_1, BULLION_RIGHT_1_X, BULLION_RIGHT_1_Y); 
	addNavigationLocation(&bullionLeft1Location, BULLION_LEFT_1, BULLION_LEFT_1_X, BULLION_LEFT_1_Y); 
	// -> Bullion 2 / Opponent CD
	addNavigationLocation(&bullionMiddle2Location, BULLION_MIDDLE_2, BULLION_MIDDLE_2_X, BULLION_MIDDLE_2_Y);
}

void bottle2ToCDPathFunction() { fillPathData(&bottle2Location, &cdTakeLocation, BOTTLE_2_TO_CD_COST, 0x1B, 0x30, 0xF8F8, 0xFAF6, BOTTLE_2_TO_CD_SPEED_FACTOR, BOTTLE_2_TO_CD_ACCELERATION_FACTOR);}
void cdToDropZone1PathFunction() { fillPathData(&cdTakeLocation, &dropZone1Location, CD_TO_DROP_ZONE_1_COST, 0x11, 0x26, 0xFAF6, ANGLE_NEG_90, CD_TO_DROP_ZONE_1_SPEED_FACTOR, CD_TO_DROP_ZONE_1_ACCELERATION_FACTOR);}

void initPaths2012() {
	clearPathList(getNavigationPathList());

	// DIRECT PATH TO TARGETS
	void startAreaToBullion1PathFunction() { fillPathData(&startAreaLocation, &bullion1Location, START_AREA_TO_BULLION_1_COST,  0x40, 0x40, 0x02A3, ANGLE_NEG_90, START_AREA_TO_BULLION_1_SPEED_FACTOR, START_AREA_TO_BULLION_1_ACCELERATION_FACTOR); }
	addNavigationPath(&startAreaToBullion1PathFunction); 

	void bullion1ToBottle1PathFunction() { fillPathData(&bullion1Location, &bottle1Location, BULLION_1_TO_BOTTLE_1_COST, 0xEC, 0xC0, ANGLE_NEG_90, ANGLE_180, BULLION_1_TO_BOTTLE_1_SPEED_FACTOR, BULLION_1_TO_BOTTLE_1_ACCELERATION_FACTOR); }
	addNavigationPath(&bullion1ToBottle1PathFunction);

	// TODO

	void bottle1ToBottle2FrontPathFunction() { fillPathData(&bottle1Location, &bottle2FrontLocation, BOTTLE_1_TO_BOTTLE_2_FRONT_COST, 0x57, 0x0A, ANGLE_180, 0x0450, BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR, BOTTLE_1_TO_BOTTLE_2_ACCELERATION_FACTOR);}
	addNavigationPath(&bottle1ToBottle2FrontPathFunction);

	void bottle2FrontToBottle2PathFunction() { fillPathData(&bottle2FrontLocation, &bottle2Location, BOTTLE_2_FRONT_TO_BOTTLE_2_COST, 0xE0, 0xF0, 0x0450, 0xF8F8, BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR, BOTTLE_1_TO_BOTTLE_2_ACCELERATION_FACTOR);}
	addNavigationPath(&bottle2FrontToBottle2PathFunction);

	addNavigationPath(&bottle2ToCDPathFunction);

	addNavigationPath(&cdToDropZone1PathFunction);

	// TO BULLION RIGHT 1
	void bullion1ToBullionRight1PathFunction() { fillPathData(&bullion1Location, &bullionRight1Location, BULLION_1_TO_BULLION_RIGHT_1_COST, 0xB0, 0x80, ANGLE_NEG_90, ANGLE_NEG_90, BULLION_1_TO_BULLION_RIGHT_1_SPEED_FACTOR, BULLION_1_TO_BULLION_RIGHT_1_ACCELERATION_FACTOR);}
	addNavigationPath(&bullion1ToBullionRight1PathFunction); 

	void dropZone1ToBullionRight1PathFunction() { fillPathData(&dropZone1Location, &bullionRight1Location, DROP_ZONE_1_TO_BULLION_RIGHT_1_COST, 0xB0, 0x80, ANGLE_NEG_90, ANGLE_NEG_90, DROP_ZONE_1_TO_BULLION_RIGHT_1_SPEED_FACTOR, DROP_ZONE_1_TO_BULLION_RIGHT_1_ACCELERATION_FACTOR);} 
	addNavigationPath(&dropZone1ToBullionRight1PathFunction); 
	
	// TO BULLION LEFT 1
	void dropZone1ToBullionLeft1PathFunction() { fillPathData(&dropZone1Location, &bullionLeft1Location, DROP_ZONE_1_TO_BULLION_LEFT_1_COST, 0xB0, 0x80, ANGLE_NEG_90, ANGLE_NEG_90, DROP_ZONE_1_TO_BULLION_LEFT_1_SPEED_FACTOR, DROP_ZONE_1_TO_BULLION_LEFT_1_ACCELERATION_FACTOR);} 
	addNavigationPath(&dropZone1ToBullionLeft1PathFunction);

	// OPPONENT CD
	void startAreaToFrontOfMapPathFunction() { fillPathData(&startAreaLocation, &frontOfMapLocation, START_AREA_TO_FRONT_OF_MAP_COST, 0x70, 0x40, 0x02A3, 0x02A3, START_AREA_TO_FRONT_OF_MAP_SPEED_FACTOR, START_AREA_TO_FRONT_OF_MAP_ACCELERATION_FACTOR);}
	addNavigationPath(&startAreaToFrontOfMapPathFunction);

	void frontOfMapToBullionMiddle2PathFunction() { fillPathData(&frontOfMapLocation, &bullionMiddle2Location, FRONT_OF_MAP_TO_BULLION_MIDDLE_2_COST, 0x22, 0x2B, 0x02A3, 0, FRONT_OF_MAP_TO_BULLION_MIDDLE_2_SPEED_FACTOR, FRONT_OF_MAP_TO_BULLION_MIDDLE_2_ACCELERATION_FACTOR);}
	addNavigationPath(&frontOfMapToBullionMiddle2PathFunction);

	void bullionMiddle2ToBottle2FrontPathFunction() { fillPathData(&bullionMiddle2Location, &bottle2FrontLocation, BULLION_MIDDLE_2_TO_BOTTLE_2_FRONT_COST, 0x26, 0x26, ANGLE_NEG_90, ANGLE_NEG_90,BULLION_MIDDLE_2_TO_BOTTLE_2_FRONT_SPEED_FACTOR, BULLION_MIDDLE_2_TO_BOTTLE_2_FRONT_ACCELERATION_FACTOR);}
	addNavigationPath(&bullionMiddle2ToBottle2FrontPathFunction);

	void bottle2FrontToDropZone1PathFunction() { fillPathData(&bottle2FrontLocation, &dropZone1Location, BOTTLE_2_FRONT_TO_DROP_ZONE_1_COST, 0x7D, 0x05, ANGLE_NEG_90, ANGLE_NEG_90,BOTTLE_2_FRONT_TO_DROP_ZONE_1_SPEED_FACTOR, BOTTLE_2_FRONT_TO_DROP_ZONE_1_ACCELERATION_FACTOR);}
	addNavigationPath(&bottle2FrontToDropZone1PathFunction);
}

void initTargets2012() {
	clearGameTargets();

	addGameTarget(&bullion1Target, BULLION_1, BULLION_GAIN, &bullion1Location);
	addGameTarget(&bottle1Target, BOTTLE_1, BOTTLE_GAIN, &bottle1Location);
	addGameTarget(&bottle2Target, BOTTLE_2, BOTTLE_GAIN, &bottle2Location);
	addGameTarget(&cd4Target, CD_TAKE, CD_4_GAIN, &cdTakeLocation);

	// Bullion Left / Right
	addGameTarget(&bullionRight1Target, BULLION_RIGHT_1, BULLION_GAIN, &bullionRight1Location);
	addGameTarget(&bullionLeft1Target, BULLION_LEFT_1, BULLION_GAIN, &bullionLeft1Location);

	// OpponentCD
	//addGameTarget(&opponentCDTarget, OPPONENT_CD, OPPONENT_CD_GAIN, &dropZone1Location);
	/*
	addGameTarget(&bullionRight2Target, BULLION_RIGHT_2, BULLION_GAIN);
	addGameTarget(&bullionLeft2Target, BULLION_LEFT_2, BULLION_GAIN);
	*/
}

// CD ActionItem

void cdTakeStep1() {
	motionFollowPath(&bottle2ToCDPathFunction);
}

void cdTakeStep2() {
	motionFollowPath(&cdToDropZone1PathFunction);
}

// Bullion Right 1 ActionItem

void bullionRight1Step3GoToDropZone() {
	motionGoLocation(&dropZone1Location,
					 ANGLE_NEG_90, 
					0x78, 0x40,
					MOTION_ACCELERATION_FACTOR_LOW, MOTION_SPEED_FACTOR_LOW);
}

// Bullion Left 1 ActionItem

void bullionLeft1Step3GoToDropZone() {
	motionGoLocation(&dropZone1Location,
					 ANGLE_NEG_90, 
					0x78, 0x40,
					MOTION_ACCELERATION_FACTOR_LOW, MOTION_SPEED_FACTOR_LOW);
}

void initTargetActions2012() {
	addTargetAction(&(bullion1Target.actionList), &bullion1TargetAction, &bullion1Location, &bullion1Location, 2, NULL);
	addTargetAction(&(bottle1Target.actionList), &bottle1TargetAction, &bottle1Location, &bottle1Location, 2, NULL);
	addTargetAction(&(bottle2Target.actionList), &bottle2TargetAction, &bottle2Location, &bottle2Location, 3, NULL);
	addTargetAction(&(cd4Target.actionList), &cdTakeTargetAction, &bottle2Location, &dropZone1Location, 4, &cdTakeTargetActionItemList);

	// BULLION 1
	addTargetAction(&(bullionRight1Target.actionList), &bullionRight1TargetAction, &bullionRight1Location, &dropZone1Location, 5, &bullionRight1ActionItemList);
	addTargetAction(&(bullionLeft1Target.actionList), &bullionLeft1TargetAction, &bullionLeft1Location, &dropZone1Location, 5, &bullionLeft1ActionItemList);

	// OPPONENT CD
	addTargetAction(&(opponentCDTarget.actionList), &opponentCDTargetAction, &dropZone1Location, &dropZone1Location, 5, NULL);
}

void initTargetActionsItems2012() {
	// CD
	addTargetActionItem(&cdTakeTargetActionItemList, &cdTakeStep1TargetActionItem, &cdTakeStep1, "cdTakeStep1");
	addTargetActionItem(&cdTakeTargetActionItemList, &cdTakeStep2TargetActionItem, &cdTakeStep2, "cdTakeStep2");

	// RIGHT BULLION 1
	// addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step1BackTargetActionItem, &bullionRight1Step1Back, "bullionRight1Step1Back");
	addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step2OpenPlierTargetActionItem, &armRightDown, "armRightDown");
	addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step3GoTargetActionItem, &bullionRight1Step3GoToDropZone, "bullionRight1GoToDropZone1");
	addTargetActionItem(&bullionRight1ActionItemList, &bullionRight1Step4ClosePlierTargetActionItem, &armRightUp, "armRightUp");

	// LEFT BULLION 1
	addTargetActionItem(&bullionLeft1ActionItemList, &bullionLeft1Step2OpenPlierTargetActionItem, &armLeftDown, "armLeftDown");
	addTargetActionItem(&bullionLeft1ActionItemList, &bullionLeft1Step3GoTargetActionItem, &bullionLeft1Step3GoToDropZone, "bullionLeft1GoToDropZone1");
	addTargetActionItem(&bullionLeft1ActionItemList, &bullionLeft1Step4ClosePlierTargetActionItem, &armLeftUp, "armLeftUp");
}

/**
 * @private.
 */
void initStrategies2012() {
	clearGameStrategies();
	addGameStrategy(&strategy1, "S1");
}

void initStrategiesItems2012() {
	addGameStrategyItem(&strategy1, &takeBullionFirstStrategyItem, &bullion1Target);
	addGameStrategyItem(&strategy1, &bottle1StrategyItem, &bottle1Target);
	addGameStrategyItem(&strategy1, &bottle2StrategyItem, &bottle2Target);
	addGameStrategyItem(&strategy1, &cdTakeStrategyItem, &cd4Target);
	addGameStrategyItem(&strategy1, &bullionRight1StrategyItem, &bullionRight1Target);
	addGameStrategyItem(&strategy1, &bullionLeft1StrategyItem, &bullionLeft1Target);
	addGameStrategyItem(&strategy1, &opponentCDStrategyItem, &opponentCDTarget);
}

void initStrategy2012(int strategyIndex) {
	initNavigation();
	initLocations2012();
	initPaths2012();

	initTargets2012();
	initTargetActions2012();
	initTargetActionsItems2012();

	initStrategies2012();
	initStrategiesItems2012();

	GameStrategy* strategy = getGameStrategy(strategyIndex);
	GameStrategyContext* strategyContext = getStrategyContext();
	strategyContext->gameStrategy = strategy;

	//OutputStream* debugOutputStream = getOutputStreamLogger(INFO);
	//printStrategyAllDatas(debugOutputStream);

	// test opponent
	Point* p = &(getStrategyContext()->opponentRobotPosition);
	p->x = 1500;
	p->y = 1500;
	
	//strategyContext->opponentRobotMoved = TRUE;
	strategyContext->hasMoreNextSteps = TRUE;

	// reinitialize the game board to change elements / targets ...
}

void printStrategyAllDatas(OutputStream* outputStream) {
	printLocationList(outputStream, "navigationLocationList:", getNavigationLocationList());
	printPathList(outputStream, "navigationPathList:", getNavigationPathList());
	printGameTargetList(outputStream);
	printGameStrategyList(outputStream);
	printGameStrategyContext(outputStream, getStrategyContext());
}
