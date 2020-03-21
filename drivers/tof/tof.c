#include "tof.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/2d/2d.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

void initTofSensor(TofSensor* tofSensor,
        tofSensorStartFunction* tofSensorStart,
        tofSensorGetDistanceMMFunction* tofGetDistanceMM,
        int* object) {
    // Important Call back & Properties
    tofSensor->tofSensorStart = tofSensorStart;
    tofSensor->tofGetDistanceMM = tofGetDistanceMM;
    tofSensor->lastDistanceMM = 0;
    tofSensor->object = object;
}

bool tofStart(TofSensor* tofSensor) {
    return tofSensor->tofSensorStart(tofSensor, false, true);
}

bool tofRestart(TofSensor* tofSensor) {
    return tofSensor->tofSensorStart(tofSensor, true, true);
}
