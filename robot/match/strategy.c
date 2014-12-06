#include "strategy.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"
// #include "../../device/drivers/lcd.h"

/**
* The side for the match.
*/
static signed int matchSide;

char* getMatchSideAsString() {
  switch (matchSide) {
    case SIDE_BLUE: return "SIDE BLUE";
    case SIDE_YELLOW: return "SIDE YELLOW";
    default: return "SIDE ????";
  }
}

void loadMatchSide() {
    matchSide = getConfigValue() & CONFIG_COLOR_BLUE_MASK;
    if (matchSide != 0) {
        matchSide = SIDE_BLUE;
    }
    else {
        matchSide = SIDE_YELLOW;
    }
    // TODO : Write on LCD
    // writeStringCR(getMatchSideAsString());
}

signed int getMatchSide() {
    return matchSide;
}


