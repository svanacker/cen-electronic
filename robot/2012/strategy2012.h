#ifndef STRATEGY_2012_H
#define STRATEGY_2012_H

#include "../../robot/strategy/GameTarget.h"


#define 	ANGLE_90			0x0384
#define		ANGLE_135			0x0546
#define		ANGLE_150			0x05DC
#define		ANGLE_180			0x0708
#define		ANGLE_NEG_90		0xFC7C
#define		ANGLE_NEG_110		0xFBB4

// LOCATIONS / TARGETS

#define START_AREA				"startArea"
#define BULLION_1				"bullion1"
#define BOTTLE_1				"bottle1"
#define BOTTLE_2				"bottle2"
#define CD_TAKE					"cdTake"
#define DROP_ZONE_1				"dropZone1"
#define CLEAN_MIDDLE_BULLION_1	"cleanMiddleBullion1"
#define BULLION_RIGHT_1			"bullionRight1"
#define BULLION_RIGHT_2			"bullionRight2"
#define BULLION_LEFT_1			"bullionLeft1"
#define BULLION_LEFT_2			"bullionLeft2"

// COORDINATES
#define START_AREA_X					170
#define START_AREA_Y					170

#define BULLION_1_X						0x0370
#define BULLION_1_Y						0x0156

#define BOTTLE_1_X						0x0720 
#define BOTTLE_1_Y						0x0280

#define BOTTLE_2_X						0x0730 
#define BOTTLE_2_Y						0x076C

#define CD_TAKE_X						0x05A8
#define CD_TAKE_Y						0x02C8

#define DROP_ZONE_1_X					0x02F5
#define DROP_ZONE_1_Y					0x00D5

#define CLEAN_MIDDLE_BULLION_1_X		0x0482
#define CLEAN_MIDDLE_BULLION_1_Y		0x0320

#define BULLION_1_RIGHT_X				0x0482
#define BULLION_1_RIGHT_Y				0x0320

// GAINS

#define BULLION_GAIN			3
#define BOTTLE_GAIN				3
#define CD_4_GAIN				4
#define BULLION_GAIN			3

// COST : between 0 and 255

#define START_AREA_TO_BULLION_1_COST							100
#define BULLION_1_TO_BOTTLE_1_COST								80
#define BOTTLE_1_TO_BOTTLE_2_COST								120
#define BOTTLE_2_TO_CD_COST										50
#define CD_TO_DROP_ZONE_1_COST									100
#define DROP_ZONE_1_TO_MIDDLE_BULLION_1_COST					50
#define AFTER_BULLION_LEFT_1_TO_START_AREA_CENTER_COST			50
#define START_AREA_CENTER_TO_START_AREA_DROP_ZONE_COST			80


// SPEED FACTOR : between 0 and 255
#define START_AREA_TO_BULLION_1_SPEED_FACTOR					200
#define BULLION_1_TO_BOTTLE_1_SPEED_FACTOR						200
#define BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR						100		
#define BOTTLE_2_TO_CD_SPEED_FACTOR								50
#define CD_TO_DROP_ZONE_1_SPEED_FACTOR							50
#define DROP_ZONE_1_TO_MIDDLE_BULLION_1_SPEED_FACTOR			50

/**
 * Get the way to have bullion1.
 */
GameTarget* getBullion1Target();

/**
 * Init all elements for 2012.
 */
void initStrategy2012();

#endif
