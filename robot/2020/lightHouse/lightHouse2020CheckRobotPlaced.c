#include "lightHouse2020CheckRobotPlaced.h"

#include "lightHouse2020Workflow.h"

#include <stdlib.h>

#include "../../../common/error/error.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

#include "../../../drivers/tof/tofDetectionUtils.h"


void checkLightHouse2020RobotPlaced(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SEARCH_IF_PLACED) {
        return;
    }
    TofSensor* tofSensor = lightHouse->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    lightHouse->robotPlacedAnalysisCount++;
    tofSensor->thresholdMinDistanceMM = LIGHT_HOUSE_2020_ROBOT_PLACED_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = LIGHT_HOUSE_2020_ROBOT_PLACED_DISTANCE_MAX;

    unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    if (isTofDistanceInRange(tofSensor)) {
        // We only notify one time
        appendStringAndDec(getAlwaysOutputStreamLogger(), "PLACED:", distanceMM);
        appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_PLACED);
    }
}
