#ifndef STRATEGY_2020_H
#define STRATEGY_2020_H

#include "score2020.h"

#include "../../../robot/strategy/gameStrategyContext.h"
#include "../../../robot/strategy/gameTarget.h"
#include "../../../robot/strategy/teamColor.h"

#include "../../../motion/simple/simpleMotion.h"
#include "../../../motion/extended/bsplineMotion.h"

#define STRATEGY_2020_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH        100
#define STRATEGY_2020_NAVIGATION_PATH_LIST_ARRAY_LENGTH            500

/**
 * Init all elements for 2020.
 */
void initStrategy2020(GameStrategyContext* gameStrategyContext);

Location* addLocationWithColors(enum TeamColor teamColor, Navigation* navigation, char* name, char* label, float x, float y);

// TODO : Add it into generic version
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
        float speedFactor);

#endif
