#include "tof.h"

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

void initTofSensor(TofSensor* tofSensor, 
                    tofSensorInitFunction* tofSensorInit,
                    tofSensorGetDistanceMMFunction* tofGetDistanceMM,
                    unsigned int thresholdDistanceMM,
                    int* object) {
    tofSensor->tofSensorInit = tofSensorInit;
    tofSensor->tofGetDistanceMM = tofGetDistanceMM;
    tofSensor->lastDistanceMM = 0;
    tofSensor->thresholdDistanceMM = thresholdDistanceMM;
    tofSensor->object = object;
    
    tofSensor->tofSensorInit(tofSensor);
}
