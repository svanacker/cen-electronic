#include "lightHouse2020CheckRobotLaunched.h"
#include "lightHouse2020Workflow.h"
#include "lightHouse2020Actions.h"

#include <stdlib.h>

#include "../../../common/error/error.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

void checkLightHouse2020ToLaunch(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_TOUCHED) {
        return;
    }
    // Do the actions
    lightHouse2020Up(lightHouse);
    lightHouse2020On(lightHouse);
    lightHouse2020RotationOn(lightHouse);
    
    // Update the status
    updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_LAUNCHED);
}

