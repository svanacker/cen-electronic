#include <stdlib.h>

#include "strategy2012Utils.h"
#include "strategy2012.h"

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

// COLOR MANAGEMENT

int isViolet() {
	return getStrategyContext()->color == COLOR_VIOLET;
}

/**
 * Change the location for color.
 */
void changeLocationsForColor() {
	if (isViolet()) {
		return;
	}
	LocationList* locationList = getNavigationLocationList();
	int i;
	unsigned char size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		location->y = GAMEBOARD_HEIGHT - location->y;
	}
}

int getAngle1Path(PathDataFunction* pathDataFunction) {
	pathDataFunction();
	int result = getTmpPathData()->angle1;
	if (isViolet()) {
		return result;
	}
	else {
		return ANGLE_180 - result;
	}	
}

int getAngle2Path(PathDataFunction* pathDataFunction) {
	pathDataFunction();
	int result = getTmpPathData()->angle1;
	if (isViolet()) {
		return result;
	}
	else {
		return ANGLE_180 - result;
	}	
}

// ARM

void armLeftUp() {
	if (isViolet()) {
		armDriver2012Up(ARM_LEFT);
	}
	else {
		armDriver2012Up(ARM_RIGHT);
	}
}

void armLeftDown() {
	if (isViolet()) {
		armDriver2012Down(ARM_LEFT);
	}
	else {
		armDriver2012Down(ARM_RIGHT);
	}
}

void armRightUp() {
	if (isViolet()) {
		armDriver2012Up(ARM_RIGHT);
	}
	else {
		armDriver2012Up(ARM_LEFT);
	}
}

void armRightDown() {
	if (isViolet()) {
		armDriver2012Down(ARM_RIGHT);
	}
	else {
		armDriver2012Down(ARM_LEFT);
	}
}
