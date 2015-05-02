#include "strategy.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"
// #include "../../device/drivers/lcd.h"

/**
* The side for the match.
*/
static enum TeamColor matchSide;

char* getMatchSideAsString() {
  switch (matchSide) {
    case SIDE_YELLOW: return "SIDE YELLOW";
    case SIDE_GREEN: return "SIDE GREEN";
    default: return "SIDE ????";
  }
}

void loadMatchSide() {
    matchSide = getConfigValue() & CONFIG_COLOR_GREEN_MASK;
    if (matchSide != 0) {
        matchSide = SIDE_GREEN;
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


