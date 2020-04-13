#include "lightHouse2020CheckRobotBottom.h"

#include "lightHouse2020Workflow.h"
#include "lightHouse2020Actions.h"

#include <stdlib.h>

#include "../../../client/io/clientIO.h"

#include "../../../common/error/error.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"
#include "../../../common/io/pin.h"

#include "../../../common/log/logger.h"


void checkLightHouse2020RobotBottom(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_INIT_POSITION_BOTTOM) {
        return;
    }
    // Ask to go back
    bool pinValue;
    bool ok = clientIORead(PIN_INDEX_RB12, &pinValue);
    if (ok) {
        // Check if we are already back
        if (pinValue) {
            // PinValue to down means that the contactor is off --> we need 
            // to ask to go to bottom
            // The robot is init to the bottom
            updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SEARCH_IF_PLACED);
        }
        else {
            // Ask to go to the bottom
            lightHouse2020Bottom(lightHouse);
            updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_INIT_GOING_DOWN);
        }
    }
}
