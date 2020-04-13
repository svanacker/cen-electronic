#include "lightHouse2020CheckRobotTouched.h"
#include "lightHouse2020Workflow.h"
#include "lightHouse2020Actions.h"

#include <stdlib.h>

#include "../../../common/error/error.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

#include "../../../drivers/tof/tofDetectionUtils.h"

void checkLightHouse2020RobotTouched(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SEARCH_TOUCH) {
        return;
    }
    TofSensor* tofSensor = lightHouse->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    lightHouse->robotNearAnalysisCount++;
    unsigned int distanceMM = 0;
    distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    tofSensor->thresholdMinDistanceMM = LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MAX;

    // TODO : Manage it in the tofSensor code !!
    if (isTofDistanceInRange(tofSensor)) {
        lightHouse->robotNearDetectionCount++;
        // Store how many Count the detect
        if (lightHouse->robotNearDetectionCount >= LIGHT_HOUSE_2020_ROBOT_TOUCH_THRESHOLD_COUNT) {
            appendStringAndDec(getAlwaysOutputStreamLogger(), "ROBOT TOUCH:", distanceMM);
            appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
            updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_TOUCHED);
        }
    } else {
        lightHouse->robotNearDetectionCount -= LIGHT_HOUSE_2020_ROBOT_TOUCH_MISSED_DECREMENT_VALUE;
        if (lightHouse->robotNearDetectionCount < 0) {
            lightHouse->robotNearDetectionCount = 0;
        }
    }
}
