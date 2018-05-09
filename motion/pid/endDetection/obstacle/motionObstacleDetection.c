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
    return false;
}

