#include "lightHouse2020CheckShowRemainingTime.h"
#include "lightHouse2020Workflow.h"

#include <stdlib.h>

#include "../../../common/error/error.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

#include "../../../robot/match/endMatch.h"

void checkLightHouse2020ShowRemainingTime(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME) {
        return;
    }
    EndMatch* endMatch = lightHouse->endMatch;
    if (endMatch == NULL) {
        writeError(ROBOT_END_MATCH_NULL);
    }
    if (lightHouse->timerCount % 10 == 0) {
        showRemainingTime(endMatch, getAlwaysOutputStreamLogger());
    }
}