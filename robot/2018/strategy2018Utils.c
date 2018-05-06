#include <stdlib.h>

#include "strategy2018Utils.h"
#include "strategy2018.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"


#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameTargetActionItem.h"
#include "../../robot/strategy/gameTargetActionList.h"

// COLOR MANAGEMENT

bool isGreen(GameStrategyContext* gameStrategyContext) {
    return gameStrategyContext->color == TEAM_COLOR_GREEN;
}

/**
 * Change the location for color.
 */
void changeLocationsForColor(GameStrategyContext* gameStrategyContext) {
    if (isGreen(gameStrategyContext)) {
        return;
    }
    Navigation* navigation = gameStrategyContext->navigation;
    LocationList* locationList = getNavigationLocationList(navigation);
    unsigned int i;
    unsigned int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        location->y = (float) (GAMEBOARD_HEIGHT - location->y);
    }
}

float changeAngleForColor(GameStrategyContext* gameStrategyContext, float angle) {
    if (isGreen(gameStrategyContext)) {
        return angle;
    } else {
        return -angle;
    }
}
