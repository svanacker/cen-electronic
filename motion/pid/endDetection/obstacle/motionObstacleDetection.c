#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "motionObstacleDetection.h"

#include "../../../../common/commons.h"
#include "../../../../common/math/cenMath.h"

#include "../../../../common/io/buffer.h"
#include "../../../../common/io/outputStream.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/reader.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

/** Minimal distance that could not occured and which must not stop the robot */
#define OBSTACLE_DETECTION_DISTANCE_MM_MINIMAL           100
#define OBSTACLE_DETECTION_DISTANCE_MM_FRONT_LEFT        400
#define OBSTACLE_DETECTION_DISTANCE_MM_FRONT_CENTER      400
#define OBSTACLE_DETECTION_DISTANCE_MM_FRONT_RIGHT       400

static unsigned detectionCount;

bool detectIfRobotHasObstacle(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    // return false;
    /*
    float pidTime = pidMotion->computationValues.pidTimeInSecond;
    unsigned int pidTimeInteger = (unsigned int) pidTime;
    float minusTime = pidTime - (float) pidTimeInteger;
    if (minusTime > 0.2f) {
        return false;
    }
    */
    TofSensorList* tofSensorList = pidMotion->tofSensorList;
    if (tofSensorList == NULL) {
        return false;
    }
    
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);

        if (distanceMM > OBSTACLE_DETECTION_DISTANCE_MM_MINIMAL && distanceMM < OBSTACLE_DETECTION_DISTANCE_MM_FRONT_CENTER) {
            detectionCount += tofSensorList->size;
        }
        else {
            if (detectionCount > 0) {
                detectionCount--;
            }
        }
        if (detectionCount > (tofSensorList->size * 2)) {
            OutputStream* debugOutputStream = getDebugOutputStreamLogger();
            
            appendString(debugOutputStream, "index=");
            appendDec(debugOutputStream, index);
            appendString(debugOutputStream, ", dist=");
            appendDec(debugOutputStream, distanceMM);      
            println(debugOutputStream);
            detectionCount = 0;
            return true;
        }

    }
    
    return false;
}

