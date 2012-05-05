#ifndef STRATEGY_2012_H
#define STRATEGY_2012_H

#include "../../robot/strategy/GameTarget.h"

// TARGETS

#define BULLION_1				"bullion1"
#define BOTTLE_1				"bottle1"
#define BOTTLE_2				"bottle2"
#define CD_4					"cd4"
#define BULLION_RIGHT_1			"bullionRight1"
#define BULLION_RIGHT_2			"bullionRight2"
#define BULLION_LEFT_1			"bullionLeft1"
#define BULLION_LEFT_2			"bullionLeft2"

// LOCATIONS

#define START_AREA				"startArea"


// COORDINATES
#define START_AREA_X			170
#define START_AREA_Y			170

#define BULLION_1_X				0x0370
#define BULLION_1_Y				0x0156

#define BOTTLE_1_X				0x0720 
#define BOTTLE_1_Y				0x0280

#define BOTTLE_2_X				0x0730 
#define BOTTLE_2_Y				0x076C

/**
 * Get the way to have bullion1.
 */
GameTarget* getBullion1Target();

#endif
