#include "tofPc.h"

#include "../tof.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/log/logger.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

bool tofSensorStartPc(TofSensor* tofSensor, bool restart, bool debug) {
    if (restart) {
        appendStringLN(getDebugOutputStreamLogger(), "TOF SENSOR RESTART");
    }
    else {
        tofSensor->startResult = TOF_SENSOR_START_RESULT_OK;
    }
    return true;
}

/**
* Tof POO Implementation for PC
* @private
*/
unsigned int tofSensorGetDistanceMMPc(TofSensor* TofSensor) {
    return 100;
}

void initTofSensorPc(TofSensor* tofSensor) {
    tofSensor->type = TOF_SENSOR_TYPE_PC;
    initTofSensor(tofSensor, 
                 &tofSensorStartPc,
                 &tofSensorGetDistanceMMPc,
                 NULL);
}
